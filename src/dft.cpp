#include "conversion.h"
#include "cvdft.h"
using namespace cv;
using namespace Rcpp;


int optimatDFTSize(int vecSize)
{
    return (cv::getOptimalDFTSize(vecSize));
}

Rcpp::NumericMatrix DFT(Rcpp::NumericMatrix imgMat, int flags, int nonzerorows)
{
    cv::Mat M = convertMat_RCPP2CV(imgMat, 5);
    cv::Mat outImg, fImage;
    M.convertTo(fImage, CV_32F);
    cv::dft(fImage, outImg, flags, nonzerorows);
    // Rprintf("%d,%d,%d,%d,%d",DFT_INVERSE,DFT_SCALE,DFT_ROWS,DFT_COMPLEX_OUTPUT,DFT_REAL_OUTPUT);
    // The values are 1, 2, 4, 16, 32
    return convertMat_CV2RCPP(outImg);
}

Rcpp::NumericMatrix mulspec(Rcpp::NumericMatrix imgMat1, 
			    Rcpp::NumericMatrix imgMat2, bool conj)
{
    cv::Mat M1 = convertMat_RCPP2CV(imgMat1, 5);
    cv::Mat M2 = convertMat_RCPP2CV(imgMat2, 5);
    cv::Mat outImg;
    cv::mulSpectrums(M1, M2, outImg, 0, conj);
    return convertMat_CV2RCPP(outImg);
}


Rcpp::List dftsep(Rcpp::NumericMatrix imgMat, int flag)
{
    cv::Mat M = convertMat_RCPP2CV(imgMat, 5);
    cv::Mat cI = getDFT(M, flag);
    cv::Mat pl[2];
    cv::split(cI, pl);
    return (Rcpp::List::create(Rcpp::Named("Real") = convertMat_CV2RCPP(pl[0]),
			       Rcpp::Named("Imaginary") = convertMat_CV2RCPP(pl[1])));
}


Rcpp::NumericMatrix wienerR(Rcpp::NumericMatrix blurred,
			    Rcpp::NumericMatrix sample,
			    int wnSD)
{
    cv::Mat I = convertMat_RCPP2CV(blurred, 5);
    cv::Mat sam = convertMat_RCPP2CV(sample, 5);
    cv::Mat padded = padding(I);
    cv::Mat sampleIm(padded.rows, padded.cols, CV_8U);
    cv::resize(sam, sampleIm, sampleIm.size());
    cv::Mat dftIm = getDFT(sampleIm, 0);
    cv::Mat spectrum = getSpectrum(dftIm);
    cv::Mat enhanced = wiener(I, spectrum, wnSD);
    return (convertMat_CV2RCPP(enhanced));
}

cv::Mat wiener(cv::Mat I, cv::Mat image_spectrum, int noise_stddev)
{
    cv::Mat padded = padding(I);
    cv::Mat noise = randNoise(padded, noise_stddev);
    cv::Mat dftNoise = getDFT(noise, 0);
    cv::Mat noise_spectrum = getSpectrum(dftNoise);

    Scalar padded_mean = mean(padded);

    cv::Mat planes[2];
    cv::Mat complexI = getDFT(padded, 0);
    cv::split(complexI, planes);	

    cv::Mat factor = image_spectrum / (image_spectrum + noise_spectrum);
    cv::multiply(planes[0], factor, planes[0]);
    cv::multiply(planes[1], factor, planes[1]);


    cv::merge(planes, 2, complexI);
    cv::idft(complexI, complexI);
    cv::split(complexI, planes);
    Scalar enhanced_mean = mean(planes[0]);
    double norm_factor =  padded_mean.val[0] / enhanced_mean.val[0];
    cv::multiply(planes[0], norm_factor, planes[0]);
    cv::Mat normalized;
    planes[0].convertTo(normalized, CV_8UC1);
    return normalized;
}

// Rcpp::NumericMatrix 

Rcpp::NumericMatrix spectrum(Rcpp::NumericMatrix imgMat, int flag)
{
    cv::Mat M = convertMat_RCPP2CV(imgMat, 5);
    cv::Mat cI = getDFT(M, flag);
    cv::Mat spec = getSpectrum(cI);
    return convertMat_CV2RCPP(spec);
}


cv::Mat getSpectrum(cv::Mat comI)
{
    cv::Mat p[2];
    cv::split(comI, p);
    cv::magnitude(p[0], p[1], p[0]);
    cv::Mat mag = p[0];
    cv::multiply(mag, mag, mag);
    return mag;
}


cv::Mat getDFT(cv::Mat Im, int flag)
{
    cv::Mat image;
    Im.convertTo(image, CV_32F);
    cv::Mat planes[] = {Mat_<float>(image), Mat::zeros(image.size(), CV_32F)};
    cv::Mat cI;
    cv::merge(planes, 2, cI);
    cv::dft(cI, cI, flag);
    return cI;
}


cv::Mat padding(cv::Mat Im)
{
    int m, n;
    cv::Mat padIm;
    m = cv::getOptimalDFTSize(Im.rows);
    n = cv::getOptimalDFTSize(Im.cols);
    copyMakeBorder(Im, padIm, 0, m - Im.rows, 0, n - Im.cols, BORDER_CONSTANT, Scalar::all(0));
    return padIm;
}

cv::Mat randNoise(cv::Mat I, int stddev)
{
    Mat noise = Mat::zeros(I.rows, I.cols, CV_32F);
    randn(noise,Scalar::all(0), Scalar::all(stddev));
    return noise;
}

Rcpp::NumericMatrix IDFT(Rcpp::NumericMatrix imgMat, int flags, int nonzerorows)
{
    cv::Mat M = convertMat_RCPP2CV(imgMat, 5);
    cv::Mat outImg;
    idft(M, outImg, flags, nonzerorows);
    Rprintf("%d,%d,%d,%d,%d",DFT_INVERSE,DFT_SCALE,DFT_ROWS,DFT_COMPLEX_OUTPUT,DFT_REAL_OUTPUT);
    return (convertMat_CV2RCPP(outImg));
}

Rcpp::NumericMatrix convolveDFT(Rcpp::NumericMatrix imgMat1, Rcpp::NumericMatrix imgMat2)
{
    cv::Mat A = convertMat_RCPP2CV(imgMat1, 5);
    cv::Mat B = convertMat_RCPP2CV(imgMat2, 5);
    cv::Mat C;
    C.create(abs(A.rows - B.rows) + 1, abs(A.cols - B.cols) + 1, A.type());
    Size dftSize;
    dftSize.width = getOptimalDFTSize(A.cols + B.cols - 1);
    dftSize.height = getOptimalDFTSize(A.rows + B.rows - 1);

    Mat tempA(dftSize, A.type(), Scalar::all(0));
    Mat tempB(dftSize, B.type(), Scalar::all(0));

    Mat roiA(tempA, Rect(0,0,A.cols,A.rows));
    A.copyTo(roiA);
    Mat roiB(tempB, Rect(0,0,B.cols,B.rows));
    B.copyTo(roiB);

    dft(tempA, tempA, 0, A.rows);
    dft(tempB, tempB, 0, B.rows);

    mulSpectrums(tempA, tempB, tempA, 0);

    dft(tempA, tempA, DFT_INVERSE + DFT_SCALE, C.rows);

    tempA(Rect(0, 0, C.cols, C.rows)).copyTo(C);
    return convertMat_CV2RCPP(C);
}

RCPP_MODULE(Dft) 
{
    function("DFT", &DFT, "Discrete Fourier Transformation");
    function("IDFT", &IDFT, "Discrete Fourier Transformation");
    function("convolveDFT", &convolveDFT, "Discrete Fourier Transformation");
    function("dftsep", &dftsep, "Discrete Fourier Transformation");
    function("spectrum", &spectrum, "Spectrum");
    function("wienerR", &wienerR, "Wiener Filter");
    function("mulspec", &mulspec, "Spectrum Multiplication");
    function("optimatDFTSize", &optimatDFTSize, "get optimal DFT size for Fourier Transformation");
}


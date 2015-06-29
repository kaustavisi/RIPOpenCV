#include "conversion.h"

using namespace cv;
using namespace Rcpp;

Rcpp::NumericMatrix DFT(Rcpp::NumericMatrix imgMat, int flags, int nonzerorows)
{
    cv::Mat M = convertMat_RCPP2CV(imgMat);
    cv::Mat outImg;
    dft(M, outImg, flags, nonzerorows);
    // Rprintf("%d,%d,%d,%d,%d",DFT_INVERSE,DFT_SCALE,DFT_ROWS,DFT_COMPLEX_OUTPUT,DFT_REAL_OUTPUT);
    return convertMat_CV2RCPP(outImg);
}

Rcpp::NumericMatrix IDFT(Rcpp::NumericMatrix imgMat, int flags, int nonzerorows)
{
    cv::Mat M = convertMat_RCPP2CV(imgMat);
    cv::Mat outImg;
    idft(M, outImg, flags, nonzerorows);
    Rprintf("%d,%d,%d,%d,%d",DFT_INVERSE,DFT_SCALE,DFT_ROWS,DFT_COMPLEX_OUTPUT,DFT_REAL_OUTPUT);
    return (convertMat_CV2RCPP(outImg));
}

Rcpp::NumericMatrix convolveDFT(Rcpp::NumericMatrix imgMat1, Rcpp::NumericMatrix imgMat2)
{
    cv::Mat A = convertMat_RCPP2CV(imgMat1);
    cv::Mat B = convertMat_RCPP2CV(imgMat2);
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
}


#include "conversion.h"

using namespace cv;
using namespace Rcpp;

/* Bilateral filter of an image */
Rcpp::NumericMatrix bilatFilter(Rcpp::NumericMatrix imgMat, int d,
                                double sigmaCol, double sigmaSpace, int borderType)
{
    cv::Mat M = convertMat_RCPP2CV(imgMat, 5);
    cv::Mat outImg;
    bilateralFilter(M, outImg, d, sigmaCol, sigmaSpace, borderType);
    return (convertMat_CV2RCPP(outImg));
}

Rcpp::NumericMatrix normBoxBlur(Rcpp::NumericMatrix imgMat, Rcpp::NumericVector size_,
                                Rcpp::NumericVector anchor_, int borderType) 
{
    cv::Mat M = convertMat_RCPP2CV(imgMat, 5);
    cv::Mat outImg;
    std::vector<int> size = as< std::vector<int> >(size_);
    std::vector<int> anchor = as< std::vector<int> >(anchor_);
    blur(M, outImg, Size(size.at(0), size.at(1)),
         Point(anchor.at(0), anchor.at(1)), borderType);
    return (convertMat_CV2RCPP(outImg));
}

Rcpp::NumericMatrix gaussianBlur(Rcpp::NumericMatrix imgMat,
				 Rcpp::NumericVector size_, 
				 double sigmaX, double sigmaY, int borderType) 
{
    std::vector<int> size = as< std::vector<int> >(size_);
    cv::Mat M, outImg;
    M = convertMat_RCPP2CV(imgMat, 5);
    GaussianBlur(M, outImg, Size(size.at(0), size.at(1)), sigmaX, sigmaY, borderType);
    return (convertMat_CV2RCPP(outImg));
}

Rcpp::NumericMatrix boxBlur(Rcpp::NumericMatrix imgMat,
			    Rcpp::NumericVector size_, Rcpp::NumericVector anchor_,
                            bool normalize, int borderType) 
{
    std::vector<int> size = as< std::vector<int> >(size_);
    std::vector<int> anchor = as< std::vector<int> >(anchor_);
    cv::Mat M, outImg;
    M = convertMat_RCPP2CV(imgMat, 5);
    boxFilter(M, outImg, -1, Size(size.at(0), size.at(1)),
              Point(anchor.at(0), anchor.at(1)), normalize, borderType);
    return (convertMat_CV2RCPP(outImg));
}


/* Apply 2d filter to an image given a kerel */
Rcpp::NumericMatrix filter2d(Rcpp::NumericMatrix imgMat,
			     Rcpp::NumericMatrix kernel_,
			     IntegerVector anchor_, double delta, int borderType)
{
    cv::Mat outImg, M, kernel;
    M = convertMat_RCPP2CV(imgMat, 5);
    kernel = convertMat_RCPP2CV(kernel_, 5);
    std::vector<int> anchor = as< std::vector<int> >(anchor_);
    filter2D(M, outImg, -1, kernel, cvPoint(anchor[0], anchor[1]), delta, borderType);
    return (convertMat_CV2RCPP(outImg));
}

/* 2 dimensional convolution. Similar to conv2 function of matlab */
/* Modified from the code of Timm Linder. It can be found in http://blog.timmlinder.com/2011/07/opencv-equivalent-to-matlabs-conv2-function/ */

Rcpp::NumericMatrix conv2(Rcpp::NumericMatrix imgMat, Rcpp::NumericMatrix kernel_, int type = 0)
{
    cv::Mat outImg, M, kernel, fkern;
    M = convertMat_RCPP2CV(imgMat, 5);
    kernel = convertMat_RCPP2CV(kernel_, 5);
    Mat source = M;
    if(type == -1) {
	source = Mat();
	const int additionalRows = kernel.rows-1, additionalCols = kernel.cols-1;
	copyMakeBorder(M, source, (additionalRows+1)/2, additionalRows/2, (additionalCols+1)/2, additionalCols/2, BORDER_CONSTANT, Scalar(0));
    }

    flip(kernel, fkern, -1);
    Point anchor(kernel.cols - kernel.cols/2 - 1, kernel.rows - kernel.rows/2 - 1);
    filter2D(source, outImg, -1, fkern, anchor, 0, BORDER_CONSTANT);

    if(type == 1) {
	outImg = outImg.colRange((kernel.cols-1)/2, outImg.cols - kernel.cols/2)
	    .rowRange((kernel.rows-1)/2, outImg.rows - kernel.rows/2);
    }
    return (convertMat_CV2RCPP(outImg));
}

/* Get derivative kernel */

Rcpp::List derivKernel(int dx, int dy, int ksize, bool normalize, int ktype)
{
    cv::Mat kx, ky;
    getDerivKernels(kx, ky, dx, dy, ksize, normalize, ktype);
    return Rcpp::List::create(Rcpp::Named("kernel.x") = convertMat_CV2RCPP(kx), 
			      Rcpp::Named("kernel.y") = convertMat_CV2RCPP(ky));   
}

/* Get Gaussian Kernel */

Rcpp::NumericMatrix getGaussKern(int ksize, double sigma, int ktype)
{
    cv::Mat outImg;
    outImg = getGaussianKernel(ksize, sigma, ktype);
    return convertMat_CV2RCPP(outImg);
}


Rcpp::NumericMatrix getGaborKern(Rcpp::NumericVector ksize_, double sigma, double theta,
                                 double lambd, double gamma, double psi, int ktype)
{
    cv::Mat outImg;
    std::vector<int> ksize = as< std::vector<int> >(ksize_);
    outImg = getGaborKernel(Size(ksize.at(0), ksize.at(1)), sigma, theta, lambd, gamma, psi, ktype); 
    return convertMat_CV2RCPP(outImg);
}

Rcpp::NumericMatrix mediBlur(Rcpp::NumericMatrix imgMat, int ksize)
{
    cv::Mat outImg, M;
    M = convertMat_RCPP2CV(imgMat, 5);
    medianBlur(M, outImg, ksize);
    return (convertMat_CV2RCPP(outImg));
}


// Does not work in OpenCV 2.4

// Rcpp::NumericMatrix sqBoxFilter(Rcpp::NumericMatrix imgMat, int ddepth, 
// 		       Rcpp::NumericVector ksize_, Rcpp::NumericVector anchor_, 
// 		       bool normalize)
// {
//     cv::Mat outImg, M;
//     M = convertMat_RCPP2CV(imgMat, 5);
//     std::vector<int> ksize = as< std::vector<int> >(ksize_);
//     std::vector<int> anchor = as< std::vector<int> >(anchor_);
//     cv::sqrBoxFilter(M, outImg, ddepth, Size(ksize.at(0), ksize.at(1)), Point(anchor.at(0), anchor.at(1)), normalize);
//     return (convertMat_CV2RCPP(outImg));
// }

RCPP_MODULE(Blur) 
{
    function("bilatFilter", &bilatFilter, "Bilateral Filtering to an image");
    function("normBoxBlur", &normBoxBlur, "Normalized Box Blurring");
    function("gaussianBlur", &gaussianBlur, "Gaussian Blurring");
    function("boxBlur", &boxBlur, "Box Blurring");
    function("filter2d", &filter2d, "2d filtering");
    function("derivKernel", &derivKernel, "Derivative Kernel");
    function("getGaussKern", &getGaussKern, "Gaussian Kernel");
    function("getGaborKern", &getGaborKern, "Gabor Kernel");
    function("mediBlur", &mediBlur, "Median blur");
    function("conv2", &conv2, "2d Convolution");
    // function("sqBoxFilter", &sqBoxFilter, "Square Box Filter");
}

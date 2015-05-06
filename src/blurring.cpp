#include "conversion.h"

using namespace cv;
using namespace Rcpp;

/* Bilateral filter of an image */
Rcpp::List bilatFilter(Rcpp::List imgList, int d, double sigmaCol, double sigmaSpace)
{
    cv::Mat M = convertList_RCPP2CV(imgList);
    cv::Mat outImg;
    bilateralFilter(M, outImg, d, sigmaCol, sigmaSpace);
    return (convertMat_CV2RCPP(outImg));
}

Rcpp::List normBoxBlur(Rcpp::List imgList, Rcpp::NumericVector size_) 
{
    cv::Mat M = convertList_RCPP2CV(imgList);
    cv::Mat outImg;
    std::vector<int> size = as< std::vector<int> >(size_);
    blur(M, outImg, Size(size.at(0), size.at(1)));
    return (convertMat_CV2RCPP(outImg));
}

Rcpp::List gaussianBlur(Rcpp::List imgList,
			Rcpp::NumericVector size_, 
			double sigmaX = 0, double sigmaY = 0) 
{
    std::vector<int> size = as< std::vector<int> >(size_);
    cv::Mat M, outImg;
    M = convertList_RCPP2CV(imgList);
    GaussianBlur(M, outImg, Size(size.at(0), size.at(1)), sigmaX, sigmaY);
    return (convertMat_CV2RCPP(outImg));
}

Rcpp::List boxBlur(Rcpp::List imgMat, 
		   Rcpp::NumericVector size_) 
{
    std::vector<int> size = as< std::vector<int> >(size_);
    cv::Mat M, outImg;
    M = convertList_RCPP2CV(imgMat);
    boxFilter(M, outImg, -1, Size(size.at(0), size.at(1)));
    return (convertMat_CV2RCPP(outImg));
}


/* Apply 2d filter to an image given a kerel */
Rcpp::List filter2d(Rcpp::List imgMat, int ddepth, 
		    Rcpp::List kernel_, IntegerVector anchor_, double delta)
{
    cv::Mat outImg, M, kernel;
    M = convertList_RCPP2CV(imgMat);
    kernel = convertList_RCPP2CV(kernel_);
    std::vector<int> anchor = as< std::vector<int> >(anchor_);
    filter2D(M, outImg, ddepth, kernel, cvPoint(anchor[0], anchor[1]), delta);
    return (convertMat_CV2RCPP(outImg));
}

/* 2 dimensional convolution. Similar to conv2 function of matlab */
/* Modified from the code of Timm Linder. It can be found in http://blog.timmlinder.com/2011/07/opencv-equivalent-to-matlabs-conv2-function/ */

Rcpp::List conv2(Rcpp::List imgMat, Rcpp::List kernel_, int type = 0)
{
    cv::Mat outImg, M, kernel, fkern;
    M = convertList_RCPP2CV(imgMat);
    kernel = convertList_RCPP2CV(kernel_);
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
    return Rcpp::List::create(Rcpp::Named("kernel.x")=convertMat_CV2RCPP(kx), 
			      Rcpp::Named("kernel.y")=convertMat_CV2RCPP(ky));   
}

/* Get Gaussian Kernel */

Rcpp::List getGaussKern(int ksize, double sigma, int ktype)
{
    cv::Mat outImg;
    outImg = getGaussianKernel(ksize, sigma, ktype);
    return convertMat_CV2RCPP(outImg);
}


Rcpp::List getGaborKern(Rcpp::NumericVector ksize_, double sigma, double theta, double lambd, double gamma, double psi, int ktype)
{
    cv::Mat outImg;
    std::vector<int> ksize = as< std::vector<int> >(ksize_);
    outImg = getGaborKernel(Size(ksize.at(0), ksize.at(1)), sigma, theta, lambd, gamma, psi, ktype); 
    return convertMat_CV2RCPP(outImg);
}

Rcpp::List mediBlur(Rcpp::List imgList, int ksize)
{
    cv::Mat outImg, M;
    M = convertList_RCPP2CV(imgList);
    medianBlur(M, outImg, ksize);
    return (convertMat_CV2RCPP(outImg));
}


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
}

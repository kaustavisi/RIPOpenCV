#include "conversion.h"

using namespace cv;
using namespace Rcpp;

Rcpp::NumericMatrix scharr(Rcpp::NumericMatrix imgMat,
			   int dx, int dy, double scale, double delta, int bordertype)
{
    cv::Mat M = convertMat_RCPP2CV(imgMat, 5);
    cv::Mat outImg;
    cv::Scharr(M, outImg, -1, dx, dy, scale, delta);
    return (convertMat_CV2RCPP(outImg));
}



Rcpp::NumericMatrix sepFilter(Rcpp::NumericMatrix imgMat, 
			      Rcpp::NumericMatrix kernelX_, Rcpp::NumericMatrix kernelY_, 
			      Rcpp::NumericVector anchor_, double delta, int bordertype)
{
    cv::Mat M = convertMat_RCPP2CV(imgMat, 5);
    cv::Mat outImg;
    cv::Mat kernelX = convertMat_RCPP2CV(kernelX_, 5);
    cv::Mat kernelY = convertMat_RCPP2CV(kernelY_, 5);
    std::vector<int> anchor = as< std::vector<int> >(anchor_);
    cv::sepFilter2D(M, outImg, -1, kernelX, kernelY, 
		    Point(anchor.at(0), anchor.at(1)), delta);
    return (convertMat_CV2RCPP(outImg));
}


Rcpp::NumericMatrix sobel(Rcpp::NumericMatrix imgMat, int dx, int dy, 
			  int ksize, double scale, double delta, int bordertype)
{
    cv::Mat M = convertMat_RCPP2CV(imgMat, 5);
    cv::Mat outImg;
    cv::Sobel(M, outImg, -1, dx, dy, ksize, scale, delta);
    return (convertMat_CV2RCPP(outImg));
}

RCPP_MODULE(derivative) 
{
    function("scharr", &scharr, "Scharr derivative");
    function("sepFilter", &sepFilter, "Separate Filter to each direction");
    function("sobel", &sobel, "Sobel derivative");
}

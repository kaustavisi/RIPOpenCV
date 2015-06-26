#include "conversion.h"

using namespace cv;
using namespace Rcpp;

Rcpp::List scharr(Rcpp::List imgList, int ddepth, int dx, int dy, double scale, double delta)
{
    cv::Mat M = convertList_RCPP2CV(imgList);
    cv::Mat outImg;
    cv::Scharr(M, outImg, ddepth, dx, dy, scale, delta);
    return (convertMat_CV2RCPP(outImg));
}



Rcpp::List sepFilter(Rcpp::List imgList, int ddepth, 
		     Rcpp::List kernelX_, Rcpp::List kernelY_, 
		     Rcpp::NumericVector anchor_, double delta)
{
    cv::Mat M = convertList_RCPP2CV(imgList);
    cv::Mat outImg;
    cv::Mat kernelX = convertList_RCPP2CV(kernelX_);
    cv::Mat kernelY = convertList_RCPP2CV(kernelY_);
    std::vector<int> anchor = as< std::vector<int> >(anchor_);
    cv::sepFilter2D(M, outImg, ddepth, kernelX, kernelY, 
		    Point(anchor.at(0), anchor.at(1)), delta);
    return (convertMat_CV2RCPP(outImg));
}


Rcpp::List sobel(Rcpp::List imgList, int ddepth, int dx, int dy, 
		 int ksize, double scale, double delta)
{
    cv::Mat M = convertList_RCPP2CV(imgList);
    cv::Mat outImg;
    cv::Sobel(M, outImg, ddepth, dx, dy, ksize, scale, delta);
    return (convertMat_CV2RCPP(outImg));
}

RCPP_MODULE(derivative) 
{
    function("scharr", &scharr, "Scharr derivative");
    function("sepFilter", &sepFilter, "Separate Filter to each direction");
    function("sobel", &sobel, "Sobel derivative");
}

#include "conversion.h"

using namespace Rcpp;
using namespace cv;

Rcpp::List imageErode(Rcpp::List imgMat, Rcpp::List kern, 
		      Rcpp::IntegerVector anchor_, int iteration)
{
    cv::Mat M = convertList_RCPP2CV(imgMat);
    cv::Mat K = convertList_RCPP2CV(kern);
    std::vector<int> anchor = as< std::vector<int> >(anchor_);
    cv::Mat outImg;
    cv::erode(M, outImg, K, Point(anchor[0], anchor[1]));
    return (convertMat_CV2RCPP(outImg));
}

Rcpp::List imageDilate(Rcpp::List imgMat, Rcpp::List kern, 
		       Rcpp::IntegerVector anchor_, int iteration)
{
    cv::Mat M = convertList_RCPP2CV(imgMat);
    cv::Mat K = convertList_RCPP2CV(kern);
    std::vector<int> anchor = as< std::vector<int> >(anchor_);
    cv::Mat outImg;
    cv::dilate(M, outImg, K, Point(anchor[0], anchor[1]));
    return (convertMat_CV2RCPP(outImg));
}
RCPP_MODULE(Morph) 
{
    function("imageErode", &imageErode, "Erodes an image");
    function("imageDilate", &imageDilate, "Erodes an image");
}

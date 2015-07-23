#include "conversion.h"

using namespace cv;
using namespace Rcpp;

Rcpp::NumericMatrix unsharp(Rcpp::NumericMatrix imgMat, Rcpp::NumericVector size_, 
			    double sigmaX = 0, double sigmaY = 0) 
{
    cv::Mat M = convertMat_RCPP2CV(imgMat);
    std::vector<int> size = as< std::vector<int> >(size_);
    cv::Mat outImg;
    GaussianBlur(M, outImg, Size(size.at(0), size.at(1)), sigmaX, sigmaY);
    addWeighted(M, 1.5, outImg, -0.5, 0, outImg);
    return (convertMat_CV2RCPP(outImg));
}


RCPP_MODULE(unsharpMask) 
{
    function("unsharp", &unsharp, "Apply unsharp mask to an image");
}

#include "conversion.h"

using namespace cv;
using namespace Rcpp;

Rcpp::NumericMatrix tempMatch(Rcpp::NumericMatrix imgMat,
                              Rcpp::NumericMatrix temp, int method)
{
    cv::Mat M = convertMat_RCPP2CV(imgMat, 5);
    cv::Mat outImg;
    cv::Mat T = convertMat_RCPP2CV(temp, 5);
    matchTemplate(M, T, outImg, method);
    return (convertMat_CV2RCPP(outImg));
}


RCPP_MODULE(template) 
{
    function("tempMatch", &tempMatch, "Template matching");
}

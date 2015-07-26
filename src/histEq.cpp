#include "conversion.h"

using namespace Rcpp;
using namespace cv;


Rcpp::NumericMatrix histEq(Rcpp::NumericMatrix imgMat)
{
    cv::Mat M = convertMat_RCPP2CV(imgMat, 5);
    cv::Mat outImg;
    equalizeHist(M, outImg);
    return(convertMat_CV2RCPP(outImg));
}


RCPP_MODULE(hist) 
{
    function("histEq", &histEq, "Histogram Equalization");
}

#include "conversion.h"

using namespace cv;
using namespace Rcpp;

/* Border Padding */
// FIXME: BORDER_COSTANT will not work. Change value = Scalar(borderValue)
Rcpp::NumericMatrix copymakeborder(Rcpp::NumericMatrix imgMat, 
				   int top, int bottom, 
				   int left, int right, int borderType)
{
    cv::Mat M = convertMat_RCPP2CV(imgMat, 5);
    cv::Mat outImg;
    if (borderType == 0)
        cv::copyMakeBorder(M, outImg, top, bottom, left, right, borderType, Scalar(0));
    else
        cv::copyMakeBorder(M, outImg, top, bottom, left, right, borderType);
    return (convertMat_CV2RCPP(outImg));
}


RCPP_MODULE(border) 
{
    function("copymakeborder", &copymakeborder, "create padding");
}

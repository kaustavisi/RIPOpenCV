#include "conversion.h"

using namespace Rcpp;
using namespace cv;


Rcpp::List histEq(Rcpp::List imgList)
{
    cv::Mat M = convertList_RCPP2CV(imgList);
    cv::Mat outImg;
    equalizeHist(M, outImg);
    return(convertMat_CV2RCPP(outImg));
}


RCPP_MODULE(hist) 
{
    function("histEq", &histEq, "Histogram Equalization");
}

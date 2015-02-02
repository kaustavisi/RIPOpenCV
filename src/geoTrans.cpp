#include "conversion.h"

using namespace Rcpp;
using namespace cv;
/* Resizing generic geometrical transformation to an image */
/****** INTER_NEAREST == 0 ******/
/****** INTER_LINEAR == 1 ******/
/****** INTER_CUBIC == 2 ******/
/****** INTER_AREA == 3 ******/
/****** INTER_LANCZOS4 == 4  ******/
/*******************************************************/
Rcpp::List imresize(Rcpp::List imgList, Rcpp::NumericVector dsize_, 
		    double fx, double fy, int interpolation)
{
    cv::Mat M = convertList_RCPP2CV(imgList);
    std::vector<int> dsize = as< std::vector<int> >(dsize_);
    cv::Mat outImg;
    resize(M, outImg, Size(dsize.at(0), dsize.at(1)), fx, fy, interpolation);
    return(convertMat_CV2RCPP(outImg));
}


RCPP_MODULE(geoTrans) 
{
    function("imresize", &imresize, "Image resizing");
}

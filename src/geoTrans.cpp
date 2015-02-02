#include "conversion.h"

using namespace Rcpp;
using namespace cv;
/* Resizing generic geometrical transformation to an image */

Rcpp::List imresize(Rcpp::List imgList, Rcpp::NumericVector dsize_, 
		    double fx, double fy, int interpolation)
{
    cv::Mat M = convertList_RCPP2CV(imgList);
    std::vector<int> dsize = as< std::vector<int> >(dsize_);
    cv::Mat outImg;
    printf("%d,%d,%d,%d,%d",INTER_NEAREST,INTER_LINEAR,INTER_AREA,INTER_CUBIC,INTER_LANCZOS4);
    resize(M, outImg, Size(dsize.at(0), dsize.at(1)), fx, fy, INTER_NEAREST);// interpolation);
    return(convertMat_CV2RCPP(outImg));
}


RCPP_MODULE(geoTrans) 
{
    function("imresize", &imresize, "Image resizing");
}

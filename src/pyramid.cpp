#include "conversion.h"

using namespace cv;
using namespace Rcpp;

/* Upsampling an image */
Rcpp::NumericMatrix pyramidUp(Rcpp::NumericMatrix imgMat,
                              Rcpp::NumericVector size_, int borderType)
{
    cv::Mat M = convertMat_RCPP2CV(imgMat, 5);
    cv::Mat outImg;
    std::vector<int> size = as< std::vector<int> >(size_);
    cv::pyrUp(M, outImg, Size(size.at(0), size.at(1)), borderType);
    return (convertMat_CV2RCPP(outImg));
}


/* Downsampling an image */
Rcpp::NumericMatrix pyramidDown(Rcpp::NumericMatrix imgMat,
                                Rcpp::NumericVector size_, int borderType)
{
    cv::Mat M = convertMat_RCPP2CV(imgMat, 5);
    cv::Mat outImg;
    std::vector<int> size = as< std::vector<int> >(size_);
    cv::pyrDown(M, outImg, Size(size.at(0), size.at(1)), borderType);
    return (convertMat_CV2RCPP(outImg));
}


Rcpp::NumericMatrix pyrMeanShtFlt(Rcpp::NumericMatrix imgMat, double sp, double sr, int maxlevel)
{
    cv::Mat M = convertMat_RCPP2CV(imgMat, 0);
    cv::Mat outImg;
    cv::pyrMeanShiftFiltering(M, outImg, sp, sr, maxlevel,
                              TermCriteria(TermCriteria::MAX_ITER+TermCriteria::EPS,5,1));
    return (convertMat_CV2RCPP(outImg));
}


RCPP_MODULE(pyramid)
{
    function("pyramidUp", &pyramidUp, "Pyramid upsample");
    function("pyramidDown", &pyramidDown, "Pyramid downsample");
    function("pyrMeanShtFlt", &pyrMeanShtFlt, "Pyramid mean shift filtering");
}

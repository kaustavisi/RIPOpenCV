#include "conversion.h"

using namespace cv;
using namespace Rcpp;

Rcpp::NumericMatrix nlmeansDenoising(Rcpp::NumericMatrix imgMat, float h, 
				     int templeteWindowSize, int searchWindowSize)
{
    cv::Mat M = convertMat_RCPP2CV(imgMat, 0);
    cv::Mat outImg;
    cv::fastNlMeansDenoising(M, outImg, h, templeteWindowSize, searchWindowSize);
    return (convertMat_CV2RCPP(outImg));
}


Rcpp::NumericMatrix nlmeansDenoisingCol(Rcpp::NumericMatrix imgMat, float h, 
					int templeteWindowSize, int searchWindowSize)
{
    cv::Mat M = convertMat_RCPP2CV(imgMat, 0);
    cv::Mat outImg;
    cv::fastNlMeansDenoisingColored(M, outImg, h, templeteWindowSize, searchWindowSize);
    return (convertMat_CV2RCPP(outImg));
}

RCPP_MODULE(denoise) 
{
    function("nlmeansDenoising", &nlmeansDenoising, "NL means denoising");
    function("nlmeansDenoisingCol", &nlmeansDenoisingCol, "NL means denoising");
}

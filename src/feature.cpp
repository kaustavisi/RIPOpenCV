#include "conversion.h"

using namespace Rcpp;
using namespace cv;

/* Canny Edge Detector */
Rcpp::NumericMatrix cannyEdgeDetector(Rcpp::NumericMatrix imgMat, 
			     double threshold1, double threshold2,
			     int appertureSize, bool L2Gradient) 
{
    cv::Mat M = convertMat_RCPP2CV(imgMat, 0);
    cv::Mat outImg;
    cv::Canny(M, outImg, threshold1, threshold2, appertureSize, L2Gradient);
    return (convertMat_CV2RCPP(outImg));
}

/* Corner Eigen Values and Vectors */
/* imgMat has to be single channel 8-bit or floating-point image */
Rcpp::NumericMatrix cornerEValsAndEVecs(Rcpp::NumericMatrix imgMat,
			       int blockSize, int kSize)
{
    cv::Mat M = convertMat_RCPP2CV(imgMat, 0);
    cv::Mat outImg;
    cv::cornerEigenValsAndVecs(M, outImg, blockSize, kSize, BORDER_DEFAULT);
    return (convertMat_CV2RCPP(outImg));
}

/* Harris Corner Detection */
Rcpp::NumericMatrix harrisCorner(Rcpp::NumericMatrix imgMat,
			int blockSize, int kSize, double k)
{
    cv::Mat M = convertMat_RCPP2CV(imgMat, 0);
    cv::Mat outImg;
    cv::cornerHarris(M, outImg, blockSize, kSize, k);
    return (convertMat_CV2RCPP(outImg));
}


/* Minimum eigen values of gradient matrix for corner detection*/
Rcpp::NumericMatrix cornerMinEVal(Rcpp::NumericMatrix imgMat, int blockSize, int ksize)
{
    cv::Mat M = convertMat_RCPP2CV(imgMat, 0);
    cv::Mat outImg(M.rows, M.cols, CV_32FC1);
    cv::cornerMinEigenVal(M, outImg, blockSize, ksize);
    return (convertMat_CV2RCPP(outImg));
}


/* Refines the corner location */

RCPP_MODULE(Feature) 
{
    function("cannyEdgeDetector", &cannyEdgeDetector, "Canny Edge Detection");
    function("cornerEValsAndEVecs", &cornerEValsAndEVecs, "Calculate eigenvalues and eigenvectors of image blocks for corner detection");
    function("harrisCorner", &harrisCorner, "Harris Corner Detection");
    function("cornerMinEVal", &cornerMinEVal, "Minimum eigen values of gradient matrices");
}

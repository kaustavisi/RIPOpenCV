#include "conversion.h"

using namespace cv;
using namespace Rcpp;

/* Bilateral filter of an image */
Rcpp::List bilatFilter(Rcpp::List imgList, int d, double sigmaCol, double sigmaSpace)
{
    cv::Mat M = convertList_RCPP2CV(imgList);
    cv::Mat outImg;
    bilateralFilter(M, outImg, d, sigmaCol, sigmaSpace);
    return (convertMat_CV2RCPP(outImg));
}

Rcpp::List normBoxBlur(Rcpp::List imgList, Rcpp::NumericVector size_) 
{
    cv::Mat M = convertList_RCPP2CV(imgList);
    cv::Mat outImg;
    std::vector<int> size = as< std::vector<int> >(size_);
    blur(M, outImg, Size(size.at(0), size.at(1)));
    return (convertMat_CV2RCPP(outImg));
}

Rcpp::List gaussianBlur(Rcpp::List imgList,
			Rcpp::NumericVector size_, 
			double sigmaX = 0, double sigmaY = 0) 
{
    std::vector<int> size = as< std::vector<int> >(size_);
    cv::Mat M, outImg;
    M = convertList_RCPP2CV(imgList);
    GaussianBlur(M, outImg, Size(size.at(0), size.at(1)), sigmaX, sigmaY);
    return (convertMat_CV2RCPP(outImg));
}

Rcpp::List boxBlur(Rcpp::List imgMat, 
		   Rcpp::NumericVector size_) 
{
    std::vector<int> size = as< std::vector<int> >(size_);
    cv::Mat M, outImg;
    M = convertList_RCPP2CV(imgMat);
    boxFilter(M, outImg, -1, Size(size.at(0), size.at(1)));
    return (convertMat_CV2RCPP(outImg));
}

/* Pyramid building is a problem due to conversion issues. Need to write a conversion code to convert arrays of arrays to NumericVector */
// Rcpp::List pyramid(Rcpp::List imgMat, int maxLevel)


/* Apply 2d filter to an image given a kerel */
Rcpp::List filter2d(Rcpp::List imgMat, int ddepth, 
		    Rcpp::List kernel_, IntegerVector anchor_, double delta)
{
    cv::Mat outImg, M, kernel;
    M = convertList_RCPP2CV(imgMat);
    kernel = convertList_RCPP2CV(kernel_);
    std::vector<int> anchor = as< std::vector<int> >(anchor_);
    filter2D(M, outImg, ddepth, kernel, cvPoint(anchor[0], anchor[1]), delta);
    return (convertMat_CV2RCPP(outImg));
}
/****************************************/


/*******************************/

RCPP_MODULE(Blur) 
{
    function("bilatFilter", &bilatFilter, "Bilateral Filtering to an image");
    function("normBoxBlur", &normBoxBlur, "Normalized Box Blurring");
    function("gaussianBlur", &gaussianBlur, "Gaussian Blurring");
    function("boxBlur", &boxBlur, "Box Blurring");
    function("filter2d", &filter2d, "2d filtering");
    // function("transfer", &transfer, "transfer");
}

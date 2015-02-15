#include "conversion.h"

using namespace Rcpp;
using namespace cv;

/* Resizing generic geometrical transformation to an image */
/* Interpolation methods are given by the following constants */
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


Rcpp::List affineWarp(Rcpp::List imgList, Rcpp::List tmat_, Rcpp::NumericVector dsize_, 
		      int flags)
{
    cv::Mat M = convertList_RCPP2CV(imgList);
    cv::Mat tmat = convertList_RCPP2CV(tmat_);
    std::vector<int> dsize = as< std::vector<int> >(dsize_);
    cv::Mat outImg;
    warpAffine(M, outImg, tmat, Size(dsize.at(0), dsize.at(1)));
    return(convertMat_CV2RCPP(outImg));
}


Rcpp::List affineTransInvert(Rcpp::List tmat_)
{
    cv::Mat tmat = convertList_RCPP2CV(tmat_);
    cv::Mat itmat;
    invertAffineTransform(tmat, itmat);
    return(convertMat_CV2RCPP(itmat));
}

Rcpp::List perspectiveWarp(Rcpp::List imgList, Rcpp::List tmat_, 
			   Rcpp::NumericVector size_)
{
    cv::Mat M = convertList_RCPP2CV(imgList);
    cv::Mat tmat = convertList_RCPP2CV(tmat_);
    std::vector<int> size = as< std::vector<int> >(size_);
    cv::Mat outImg;
    warpPerspective(M, outImg, tmat, Size(size.at(0), size.at(1)));
    return(convertMat_CV2RCPP(outImg));
}


Rcpp::List rectSubPix(Rcpp::List imgList, Rcpp::NumericVector patchsize_, 
		      Rcpp::NumericVector center_, int patchtype)
{
    cv::Mat M = convertList_RCPP2CV(imgList);
    std::vector<int> patchsize = as< std::vector<int> >(patchsize_);
    std::vector<int> center = as< std::vector<int> >(center_);
    cv::Mat outImg;
    Point2f centerP(center.at(0), center.at(1));
    getRectSubPix(M, Size(patchsize.at(0), patchsize.at(1)), centerP, outImg, patchtype);
    return(convertMat_CV2RCPP(outImg));
}

Rcpp::List getRotMat(Rcpp::NumericVector center_, double angle, double scale)
{
    std::vector<int> center = as< std::vector<int> >(center_);
    Point2f centerP(center.at(0), center.at(1));
    cv::Mat outMat = getRotationMatrix2D(centerP, angle, scale);
    return(convertMat_CV2RCPP(outMat));
}

RCPP_MODULE(geoTrans) 
{
    function("imresize", &imresize, "Image resizing");
    function("affineWarp", &affineWarp, "Affine warpping");
    function("affineTransInvert", &affineTransInvert, "inverts an affine transformation");
    function("perspectiveWarp", &perspectiveWarp, "Perspective Warpping");
    function("rectSubPix", &rectSubPix, "Retrives a pixel rectangle");
    function("getRotMat", &getRotMat, "get rotation matrix");
}

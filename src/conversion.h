#ifndef CONVERSION_H
#define CONVERSION_H


#include <Rcpp.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <iostream>

Rcpp::List convertUCMat_CV2RCPP(cv::Mat);
Rcpp::List convertFMat_CV2RCPP(cv::Mat);
Rcpp::List convertDMat_CV2RCPP(cv::Mat);
Rcpp::List convertMat_CV2RCPP(cv::Mat);
cv::Mat convertMat_RCPP2CV(Rcpp::NumericMatrix);
cv::Mat convertUCList_RCPP2CV(Rcpp::List);

#endif

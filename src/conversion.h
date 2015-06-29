#ifndef CONVERSION_H
#define CONVERSION_H


#include <Rcpp.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <iostream>

/* main interface */
Rcpp::NumericMatrix convertMat_CV2RCPP(cv::Mat);
cv::Mat convertMat_RCPP2CV(Rcpp::NumericMatrix);

/* helper functions */
Rcpp::NumericMatrix convertUCMat_CV2RCPP(cv::Mat);
Rcpp::NumericMatrix convertCMat_CV2RCPP(cv::Mat);
Rcpp::NumericMatrix convertUSMat_CV2RCPP(cv::Mat);
Rcpp::NumericMatrix convertSMat_CV2RCPP(cv::Mat);
Rcpp::NumericMatrix convertIMat_CV2RCPP(cv::Mat);
Rcpp::NumericMatrix convertFMat_CV2RCPP(cv::Mat);
Rcpp::NumericMatrix convertDMat_CV2RCPP(cv::Mat);

void convertUCMat_RCPP2CV(Rcpp::NumericMatrix, cv::Mat, int, int);
void convertFMat_RCPP2CV(Rcpp::NumericMatrix, cv::Mat, int, int);
void convertDMat_RCPP2CV(Rcpp::NumericMatrix, cv::Mat, int, int);

#endif

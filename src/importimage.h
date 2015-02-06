#ifndef IMPORTIMAGE_H
#define IMPORTIMAGE_H

#include <Rcpp.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <iostream>

cv::Mat readImage(std::string imfile, int typ = 0);
/* Rcpp::NumericMatrix importAsGrayscale(std::vector<std::string> infile); */
Rcpp::NumericMatrix importAsGrayscale(std::vector<std::string> infile);
Rcpp::NumericMatrix importRGB(std::vector<std::string> infile);

#endif

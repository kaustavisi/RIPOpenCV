#ifndef CVDFT_H
#define CVDFT_H

cv::Mat getSpectrum(cv::Mat);
cv::Mat getDFT(cv::Mat, int);
cv::Mat wiener(cv::Mat, cv::Mat, int);
cv::Mat padding(cv::Mat);
cv::Mat randNoise(cv::Mat, int);
#endif

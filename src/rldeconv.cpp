#include "conversion.h"

using namespace cv;
using namespace Rcpp;

cv::Mat rlUpdate(cv::Mat oimg, cv::Mat cimg, cv::Mat mask);
cv::Mat rlUpdate2(cv::Mat oimg, cv::Mat cimg, cv::Mat mask);
cv::Mat rlUpdate3(cv::Mat oimg, cv::Mat cimg, cv::Mat mask);

Rcpp::List RLA(Rcpp::List imgList, Rcpp::List initImg, Rcpp::List kernel, int iter, int ind)
{
    cv::Mat Y = convertList_RCPP2CV(imgList);
    cv::Mat L = convertList_RCPP2CV(initImg);
    cv::Mat K = convertList_RCPP2CV(kernel);

    int i;

    cv::Mat outImg;

    for(i = 0; i < iter; i++) {
	outImg = rlUpdate(Y, L, K);
	outImg.copyTo(L);
    }
    return convertMat_CV2RCPP(outImg);
}



cv::Mat rlUpdate(cv::Mat oimg, cv::Mat cimg, cv::Mat mask)
{
    int i1, i2, j1, j2, k1, k2, a, b;
    double temp, tmp;
    int nrow, ncol, mrow, mcol, mr2, mc2;
    nrow = oimg.rows;
    ncol = oimg.cols;
    mrow = mask.rows;
    mcol = mask.cols;
    mr2 = mrow/2;
    mc2 = mcol/2;

    cv::Mat outimg;
    oimg.copyTo(outimg);
    for(i1 = 0; i1 < nrow; i1++) {
    	for(i2 = 0; i2 < ncol; i2++) {
    	    tmp = 0;
    	    for(j1 = i1 - mr2; j1 < i1 + mr2; j1++) {
    		for(j2 = i2 - mc2; j2 < i2 + mc2; j2++) {
    		    temp = 0;
    		    for(k1 = 0; k1 < mrow; k1++) {
    			for(k2 = 0; k2 < mcol; k2++) {
    			    a = (j1 - mr2 + k1);
    			    b = (j2 - mc2 + k2);	      
    			    if(a >= 0 && b >= 0 && a < nrow && b < ncol) {
    				temp = temp + cimg.at<float>(a, b) * mask.at<float>(k1, k2);
			    }
    			}
    		    }
		    if(j1 < nrow && j2 < ncol && j1 > 0 && j2 > 0) 
			tmp = tmp + oimg.at<float>(j1, j2) * mask.at<float>(j1 - i1 + mr2, j2 - i2 + mc2) / temp;
    		}
    	    }
    	    outimg.at<float>(i1, i2) = min(max(cimg.at<float>(i1, i2) * tmp, 0.0), 255.0);
    	}
    }
    return outimg;
}



RCPP_MODULE(rla) 
{
    function("RLA", &RLA, "Richardson Lucy Deconvolution");
}

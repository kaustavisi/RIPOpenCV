#include "conversion.h"

using namespace cv;
using namespace Rcpp;

cv::Mat rlUpdate(cv::Mat oimg, cv::Mat cimg, cv::Mat mask);
Rcpp::List RLA(Rcpp::List imgList, Rcpp::List initImg, Rcpp::List kernel, int iter)
{
    cv::Mat Y = convertList_RCPP2CV(imgList);
    cv::Mat L = convertList_RCPP2CV(initImg);
    cv::Mat K = convertList_RCPP2CV(kernel);
    
    int i, nrow, ncol, mcol, mrow,
	mr2, mc2;

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
    for(i1 = mr2; i1 < nrow - mr2; i1++) {
    	for(i2 = mc2; i2 < ncol - mc2; i2++) {
    	    tmp = 0;

    	    for(j1 = i1 - mr2; j1 < i1 + mr2; j1++) {
    		for(j2 = i2 - mc2; j2 < i2 + mc2; j2++) {
    		    temp = 0;
    		    for(k1 = 0; k1 < mrow; k1++) {
    			for(k2 = 0; k2 < mcol; k2++) {
    			    a = (j1 - mr2 + k1);
    			    b = (j2 - mc2 + k2);
	      
    			    if(a >= 0 && b >= 0 && a < nrow && b < ncol) {
    				temp = temp + cimg.at<uchar>(a, b) * mask.at<float>(k1, k2);
			    }
    			}
    		    }
    		    tmp = tmp + oimg.at<uchar>(j1, j2) * mask.at<float>(j1 - i1 + mr2, j2 - i2 + mc2) / temp;
    		}
    	    }
    	    outimg.at<uchar>(i1, i2) = (uchar) round(cimg.at<uchar>(i1, i2) * tmp);
    	}
    }
    return outimg;
}

RCPP_MODULE(rla) 
{
    function("RLA", &RLA, "Richardson Lucy Deconvolution");
}

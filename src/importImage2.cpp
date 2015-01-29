#include "importimage.h"
#include "conversion.h"

using namespace cv;
using namespace Rcpp;


/* Reading image using cv::imread given a filepath */
cv::Mat readImage(std::string imfile, int typ) {
    cv::Mat image;
    image = imread(imfile, typ);
    if (!image.data) {
	throw std::range_error("Could not open the file");
    }
    Rprintf("channels=%d, type=%d, dims=%d, depth=%d",image.channels(), image.type(), image.dims, image.depth());
    return image;
}


/* Import image as grayscale */
Rcpp::List importImage(std::vector<std::string> infile, int type = 0)
{
    std::string f = infile[0];

    if(type == 0) 
	return convertUCMat_CV2RCPP(readImage(f, 0));
    else if (type == 1)
	return convertUCMat_CV2RCPP(readImage(f, 1));
    else {
	Rprintf("Unknown image type. Gray image imported");
	return convertUCMat_CV2RCPP(readImage(f, 0));
    }
	
}


void writeImage(Rcpp::List imgList, Rcpp::CharacterVector outFile) 
{
    cv::Mat outImg = convertUCList_RCPP2CV(imgList);
    std::string outfile = as<std::string>(outFile);
    cv::imwrite(outfile, outImg);
    return;
}

Rcpp::List r2r(Rcpp::List imgList)
{
    cv::Mat outImg;
    outImg = convertUCList_RCPP2CV(imgList);
    return convertUCMat_CV2RCPP(outImg);
}

RCPP_MODULE(R2R) {
    function("importImage", &importImage, "Transfer");
    function("writeImage", &writeImage, "Transfer");
    function("r2r", &r2r, "check");
}



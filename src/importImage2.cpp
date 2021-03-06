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
    // Rprintf("channels=%d, type=%d, dims=%d, depth=%d",
    // 	    image.channels(), image.type(), image.dims, image.depth());
    return image;
}


/* Import image as grayscale */
Rcpp::NumericMatrix importImage(std::vector<std::string> infile, int type = 0)
{
    std::string f = infile[0];
    if (type != 0 && type != 1) {
	Rprintf("Unknown image type. Importing as grayscale.");
	type = 0;
    }
    return convertMat_CV2RCPP(readImage(f, type));
}


void writeImage(Rcpp::NumericMatrix imgMat, Rcpp::CharacterVector outFile) 
{
    cv::Mat outImg = convertMat_RCPP2CV(imgMat, 5);
    std::string outfile = as<std::string>(outFile);
    cv::imwrite(outfile, outImg);
    return;
}

RCPP_MODULE(R2R) {
    function("importImage", &importImage, "Import Image");
    function("writeImage", &writeImage, "Save image in a file");
}



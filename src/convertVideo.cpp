#include "convertVideo.h"
#include "conversion.h"

using namespace Rcpp;
using namespace cv;

/* Read a video from a .avi file */
Rcpp::NumericMatrix readVideo(std::string imfile, int ind)
{
    cv::VideoCapture cap(imfile);
    int i = 0;
    if(!cap.isOpened())
        ::Rf_error("Could not open the file");
    else {
        for( ; ; ) {
            Mat frame;
            cap >> frame;
            i++;
            if(i == ind)
                return (convertMat_CV2RCPP(frame));
        }
    }
}


RCPP_MODULE(video)
{
    function("readVideo", &readVideo, "Read a video");
}

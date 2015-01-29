#include "conversion.h"

using namespace Rcpp;
using namespace cv;

Rcpp::List convertMat_CV2RCPP(cv::Mat M)
{
    if (M.depth() == 0)
	return convertUCMat_CV2RCPP(M);
    else if (M.depth() == 5)
	return convertFMat_CV2RCPP(M);
    else if (M.depth() == 6)
	return convertDMat_CV2RCPP(M);
    else 
	::Rf_error("Cannot convert");

}


/* Converting OpenCV uchar Mat to NumericMatrix */
Rcpp::List convertUCMat_CV2RCPP(cv::Mat M)
{
    NumericMatrix x(M.rows, M.cols * M.channels());
    for (int i = 0; i < M.rows; i++)
	for (int j = 0; j < M.cols * M.channels(); j++) {
	    x(i, j) = M.at<uchar>(i,j);
	}
    return Rcpp::List::create(Rcpp::Named("Data") = x, 
			      Rcpp::Named("Dimension") = NumericVector::create(M.rows, M.cols, M.channels(), M.type(), M.depth()));
}

/* Converting OpenCV float Mat to NumericMatrix */
Rcpp::List convertFMat_CV2RCPP(cv::Mat M)
{
    NumericMatrix x(M.rows, M.cols * M.channels());
    for (int i = 0; i < M.rows; i++)
	for (int j = 0; j < M.cols * M.channels(); j++) {
	    x(i, j) = M.at<float>(i,j);
	}
    return Rcpp::List::create(Rcpp::Named("Data") = x, 
			      Rcpp::Named("Dimension") = NumericVector::create(M.rows, M.cols, M.channels(), M.type(), M.depth()));
}


/* Converting OpenCV double Mat to NumericMatrix */
Rcpp::List convertDMat_CV2RCPP(cv::Mat M)
{
    NumericMatrix x(M.rows, M.cols * M.channels());
    for (int i = 0; i < M.rows; i++)
	for (int j = 0; j < M.cols * M.channels(); j++) {
	    x(i, j) = M.at<double>(i,j);
	}
    return Rcpp::List::create(Rcpp::Named("Data") = x, 
			      Rcpp::Named("Dimension") = NumericVector::create(M.rows, M.cols, M.channels(), M.type(), M.depth()));
}

/* Converting NumericMatrix of type to OpenCV Mat*/


cv::Mat convertUCList_RCPP2CV(Rcpp::List x)
{
    int i, j;

    std::vector<int> dims = as< std::vector<int> >((x["Dimension"]));
    int nRow = dims[0];
    int nCol = dims[1];
    int nChannel = dims[2];
    int effCol = nCol * nChannel;

    cv::Mat M(nRow, nCol, dims[3]); 
    NumericMatrix lx = as<NumericMatrix>(x["Data"]);

    for(i = 0; i < nRow; i++) {
	for(j = 0; j < effCol; j++) {
	    M.at<uchar>(i, j) = lx(i, j);
	}
    }
    return M;
}

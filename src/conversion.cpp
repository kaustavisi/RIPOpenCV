#include "conversion.h"

using namespace Rcpp;
using namespace cv;
/* Conversion of OpenCV matrix to RCPP NumericMatrix and return as a list */
Rcpp::List convertMat_CV2RCPP(cv::Mat M)
{
    if (M.depth() == 0)
	return convertUCMat_CV2RCPP(M);
    else if (M.depth() == 5)
	return convertFMat_CV2RCPP(M);
    else if (M.depth() == 6)
	return convertDMat_CV2RCPP(M);
    else if (M.depth() == 1)
	return convertCMat_CV2RCPP(M);
    else if (M.depth() == 2)
	return convertUSMat_CV2RCPP(M);
    else if (M.depth() == 3)
	return convertSMat_CV2RCPP(M);
    else if (M.depth() == 4)
	return convertIMat_CV2RCPP(M);
    else 
	::Rf_error("Cannot convert");
}

/*********************************************/
/**** This part includes separate functions that  
      convert OpenCV matrix of different type to NumericMatrix ****/
/********************************************/

/* Converting OpenCV uchar Mat to NumericMatrix */
/* image depth == 0 */
/***********************************/

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


/* Converting OpenCV signed char Mat to NumericMatrix */
/* image depth == 1 */
/***********************************/

Rcpp::List convertCMat_CV2RCPP(cv::Mat M)
{
    NumericMatrix x(M.rows, M.cols * M.channels());
    for (int i = 0; i < M.rows; i++)
	for (int j = 0; j < M.cols * M.channels(); j++) {
	    x(i, j) = M.at<char>(i,j);
	}
    return Rcpp::List::create(Rcpp::Named("Data") = x, 
			      Rcpp::Named("Dimension") = NumericVector::create(M.rows, M.cols, M.channels(), M.type(), M.depth()));
}



/* Converting OpenCV unsigned int Mat to NumericMatrix */
/******** image depth == 2 *********/
/***********************************/

Rcpp::List convertUSMat_CV2RCPP(cv::Mat M)
{
    NumericMatrix x(M.rows, M.cols * M.channels());
    for (int i = 0; i < M.rows; i++)
	for (int j = 0; j < M.cols * M.channels(); j++) {
	    x(i, j) = M.at<ushort>(i,j);
	}
    return Rcpp::List::create(Rcpp::Named("Data") = x, 
			      Rcpp::Named("Dimension") = NumericVector::create(M.rows, M.cols, M.channels(), M.type(), M.depth()));
}

/* Converting OpenCV signed short int Mat to NumericMatrix */
/******** image depth == 3 *********/
/***********************************/

Rcpp::List convertSMat_CV2RCPP(cv::Mat M)
{
    NumericMatrix x(M.rows, M.cols * M.channels());
    for (int i = 0; i < M.rows; i++)
	for (int j = 0; j < M.cols * M.channels(); j++) {
	    x(i, j) = M.at<short>(i,j);
	}
    return Rcpp::List::create(Rcpp::Named("Data") = x, 
			      Rcpp::Named("Dimension") = NumericVector::create(M.rows, M.cols, M.channels(), M.type(), M.depth()));
}


/* Converting OpenCV signed int Mat to NumericMatrix */
/******** image depth == 4 *********/
/***********************************/

Rcpp::List convertIMat_CV2RCPP(cv::Mat M)
{
    NumericMatrix x(M.rows, M.cols * M.channels());
    for (int i = 0; i < M.rows; i++)
	for (int j = 0; j < M.cols * M.channels(); j++) {
	    x(i, j) = M.at<int>(i,j);
	}
    return Rcpp::List::create(Rcpp::Named("Data") = x, 
			      Rcpp::Named("Dimension") = NumericVector::create(M.rows, M.cols, M.channels(), M.type(), M.depth()));
}


/* Converting OpenCV float Mat to NumericMatrix */
/******** image depth == 5 *********/
/***********************************/

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
/******** image depth == 6 *********/
/***********************************/
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



/***********************************************************************************/
/***********************************************************************************/
/* Conversion of RCPP NumericMatrix containing allowed type of data to OpenCV matrix */
/***********************************************************************************/
/***********************************************************************************/
cv::Mat convertList_RCPP2CV(Rcpp::List x)
{
    std::vector<int> dims = as< std::vector<int> >((x["Dimension"]));
    if (dims[4] == 0)
	return convertUCList_RCPP2CV(x);
    else if (dims[4] == 5)
	return convertFList_RCPP2CV(x);
    else if (dims[4] == 6)
	return convertDList_RCPP2CV(x);
    else 
	::Rf_error("Cannot convert");
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


/* Converting NumericMatrix of type float to OpenCV Mat*/


cv::Mat convertFList_RCPP2CV(Rcpp::List x)
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
	    M.at<float>(i, j) = lx(i, j);
	}
    }
    return M;
}

/* Converting NumericMatrix of type double to OpenCV Mat*/


cv::Mat convertDList_RCPP2CV(Rcpp::List x)
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
	    M.at<double>(i, j) = lx(i, j);
	}
    }
    return M;
}


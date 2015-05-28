#include "conversion.h"

using namespace cv;
using namespace Rcpp;


Rcpp::NumericMatrix isoDenoiseEdge(Rcpp::List imgList, 
				   Rcpp::List kernList,
				   Rcpp::LogicalMatrix indEdge, 
				   Rcpp::LogicalMatrix indInterest)
{
    int i, j, imrow, imcol, krow, kcol, kcenterX, kcenterY, ii, jj, k1, k2;
    double tmp;
    if(!imgList.inherits("rip") || !kernList.inherits("rip")) stop("Image must be a rip object");
    Rcpp::NumericMatrix im = as<NumericMatrix>(imgList["Data"]);
    Rcpp::NumericMatrix kern = as<NumericMatrix>(kernList["Data"]);
    imcol = indEdge.ncol();
    imrow = indEdge.nrow();
    krow = kern.nrow();
    kcol = kern.ncol();
    kcenterX = kcol / 2;
    kcenterY = krow / 2;
    NumericMatrix out(imrow, imcol);

    for(i = 0; i < imrow; i++) {
	for(j = 0; j < imcol; j++) {
	    if(indInterest(i,j) == true && indEdge(i,j) == false) {
		tmp = 0;
		for(k1 = 0; k1 < krow; k1++) {
		    for(k2 = 0; k2 < kcol; k2++) {
			ii = i + (k1 - kcenterY);
			jj = j + (k2 - kcenterX);
			if(indEdge(ii,jj) == false, 
			   ii >= 0 && ii < imrow 
			   && jj >= 0 && jj < imcol) {
			    tmp += kern(krow - 1 - k1, kcol - 1 - k2);
			    out(i, j) += im(ii, jj) 
				* kern(krow - 1 - k1, kcol - 1 - k2);
			}
		    }
		}
		out(i, j) = out(i, j) / tmp;
	    }
	    else {
		out(i,j) = im(i, j);
	    }
	}
    }
    return out;
}


RCPP_MODULE(denoiseEdge) 
{
    function("isoDenoiseEdge", &isoDenoiseEdge, "...some function");
}

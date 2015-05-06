#include "conversion.h"

using namespace Rcpp;

Rcpp::NumericMatrix conv2Direct(NumericMatrix x, NumericMatrix k)
{
    int nrow, ncol, krow, kcol, kcenterX, kcenterY,
	i, j, ii, jj, m, n, mm, nn;
    nrow = x.nrow();
    ncol = x.ncol();
    krow = k.nrow();
    kcol = k.ncol();
    kcenterX = kcol / 2;
    kcenterY = krow / 2;
    NumericMatrix out(nrow, ncol);
    for(i = 0; i < nrow; i++) {
	for(j = 0; j < ncol; j++) {
	    for(m = 0; m < krow; m++) {
		mm = krow - 1 - m;
		for(n = 0; n < kcol; n++) {
		    nn = kcol - 1 - n;
		    ii = i + (m - kcenterY);
		    jj = j + (n - kcenterX);
		    if(ii >= 0 && ii < nrow && jj >= 0 && jj < ncol)
			out(i, j) += x(ii, jj) * k(mm, nn);
		}
	    }
	}
    }
    return out;
}

Rcpp::NumericMatrix conv2Direct2(NumericMatrix x, NumericMatrix k)
{
    int nrow, ncol, krow, kcol, kcenterX, kcenterY,
	i, j, ii, jj, m, n, mm, nn;
    nrow = x.nrow();
    ncol = x.ncol();
    krow = k.nrow();
    kcol = k.ncol();
    kcenterX = kcol / 2;
    kcenterY = krow / 2;
    NumericMatrix out(nrow, ncol);
    for(i = 0; i < nrow; i++) {
	for(j = 0; j < ncol; j++) {
	    for(m = -kcenterY; m <= kcenterY; m++) {
		for(n = -kcenterX; n <= kcenterX; n++) {
		    ii = i - m;
		    jj = j - n;
		    if(ii >= 0 && ii < nrow && jj >= 0 && jj < ncol)
			out(i, j) += x(ii, jj) * k(m + kcenterY, n + kcenterX);
		}
	    }
	}
    }
    return out;
}


RCPP_MODULE(conv2direct) 
{
    function("conv2Direct", &conv2Direct, "Inefficient implementation of convolution");
    function("conv2Direct2", &conv2Direct2, "Inefficient implementation of convolution (easier method)");
}

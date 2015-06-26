##' .. content for \description{} (no empty lines) ..
##'
##' .. content for \details{} ..
##' @title Find edges using the canny edge detection algorithm
##' @param img rip object of 1 one channel. 
##' @param threshold1 first threshold for the hysteresis procedure
##' @param threshold2 second threshold for the hysteresis procedure
##' @param appertureSize aperture size of the Sobel operator
##' @param L2Gradient a flag, indicating whether a more accurate L2 norm to be used to calculate the image gradient or a L1 gradient is good enough.
##' @return rip object of same size as \code{img} with values 0 and 255. Value 255 marks the edges.(FIXME: check this, whether this is 0 or 255)
##' @author Kaustav Nandy
Canny.EdgeDectector <- function(img, threshold1, threshold2,
                                appertureSize, L2Gradient)
{
    mfeature <- Module("Feature", PACKAGE = "RIPOpenCV")
    mfeature$cannyEdgeDetector(img, threshold1, threshold2,
                               appertureSize, L2Gradient)
}

##' .. content for \description{} (no empty lines) ..
##'
##' .. content for \details{} ..
##' @title Calculates eigenvalues and eigenvectors of image blocks for corner detection.
##' @param img rip object of 1 one channel. 
##' @param blocksize Neighbourhood size
##' @param ksize aperture size of the Sobel operator
##' @return gives a rip object consisting of eigen values and vectors. (FIXME: write full description)
##' @author Kaustav Nandy
cornerEigenValsVecs <- function(img, blocksize, ksize)
{
    mfeature <- Module("Feature", PACKAGE = "RIPOpenCV")
    mfeature$cornerEValsAndEVecs(img, blocksize, ksize)
}

##' .. content for \description{} (no empty lines) ..
##'
##' .. content for \details{} ..
##' @title Harris edge detector.
##' @param img rip object of 1 one channel. 
##' @param blocksize Neighbourhood size.
##' @param ksize aperture size of the Sobel operator
##' @param k Harris detector free parameter.
##' @return rip object with Harris corner detector responses.
##' @author Kaustav Nandy
corner.Harris <- function(img, blocksize, ksize, k)
{
    mfeature <- Module("Feature", PACKAGE = "RIPOpenCV")
    mfeature$harrisCorner(img, blocksize, ksize, k)
}

##' .. content for \description{} (no empty lines) ..
##'
##' .. content for \details{} ..
##' @title 
##' @param img rip object of 1 one channel. 
##' @param blocksize Neighbourhood size.
##' @param ksize aperture size of the Sobel operator
##' @return Returns the minimum eigen value of the covariance matrix of derivatives.
##' @author Kaustav Nandy
corner.MinEigenVal <- function(img, blocksize, ksize)
{
    mfeature <- Module("Feature", PACKAGE = "RIPOpenCV")
    mfeature$cornerMinEVal(img, blocksize, ksize)
}

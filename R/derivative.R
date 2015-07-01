##' .. content for \description{} (no empty lines) ..
##'
##' .. content for \details{} ..
##' @title compute ordinary image gradient. 
##' @param img rip object of one channel
##' @return list of two. ... FIXME
##' @author Kaustav Nandy
image.gradient <- function(img)
{
    dat <- img
    dimg <- dim(dat)
    x.dir <- dat[,-1] - dat[,-dimg[2]]
    y.dir <- dat[-1,] - dat[-dimg[1],]
    list("x.direction" = x.dir, "y.direction" = y.dir)
}

##' .. content for \description{} (no empty lines) ..
##'
##' .. content for \details{} ..
##' @title Scharr image derivative
##' @param img rip object
##' @param ddepth output image depth
##' @param dx order of the derivative in x direction.
##' @param dy order of the derivative n y direction.
##' @param scale optional scale factor for the computed derivative values. By default no scale is being applied.
##' @param delta optional delta value that is added to the results prior to output.
##' @return rip object of the same size and same number of channels as \code{img}.
##' @author Kaustav Nandy
Scharr <- function(img, ddepth, dx, dy, scale=1, delta=0)
{
    mderiv <- Module("derivative", PACKAGE = "RIPOpenCV")
    mderiv$scharr(img, ddepth, dx, dy, scale, delta)
}


##' .. content for \description{} (no empty lines) ..
##'
##' .. content for \details{} ..
##' @title Derivative using Sobel operator
##' @param img rip object.
##' @param ddepth output image depth.
##' @param dx order of the derivative in x direction
##' @param dy order of the derivative in y direction
##' @param ksize size of the extended sobel kernel, it must be 1, 3, 5 or 7
##' @param scale optional scale factor for the computed derivative values. By default no scale is being applied.
##' @param delta optional delta value that is added to the results prior to output.
##' @return rip object of the same size and same number of channels as \code{img}.
##' @author Kaustav Nandy
Sobel <- function(img, ddepth, dx, dy, ksize, scale=1, delta=0)
{
    mderiv <- Module("derivative", PACKAGE = "RIPOpenCV")
    mderiv$sobel(img, ddepth, dx, dy, ksize, scale, delta)
}

##' .. content for \description{} (no empty lines) ..
##'
##' .. content for \details{} ..
##' @title Applies seperable filter to an image
##' @param img rip object
##' @param ddepth depth of the output image
##' @param kernelX Coefficients for filtering each row.
##' @param kernelY Coefficients for filtering each column.
##' @param anchor Anchor position within the kernel. The default value (|1,|1) means that the anchor is at the kernel center.
##' @param delta Value added to the filtered results before returning them.
##' @return rip object of same size and number of channel as \code{img}.
##' @author Kaustav Nandy
sepFilter2D <- function(img, ddepth, kernelX, kernelY, anchor, delta)
{
    mderiv <- Module("derivative", PACKAGE = "RIPOpenCV")
    mderiv$sepFilter(img, ddepth, kernelX, kernelY, anchor, delta)
}

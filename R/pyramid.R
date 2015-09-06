##' .. content for \description{} (no empty lines) ..
##'
##' .. content for \details{} ..
##' @title Pyramid upsample
##' @param img rip object with 1 or 3 channels
##' @param size size of the output image
##' @param borderType border method. Border type 0, i.e. border constant is not supported.
##' @return Downsampled image
##' @author kaustav nandy
pyrUp <- function(img, size, borderType = 4)
{
    mpyramid <- Module("pyramid", PACKAGE = "RIPOpenCV")
    mpyramid$pyramidUp(img, size, borderType)
}

pyrDown <- function(img, size, borderType = 4)
{
    mpyramid <- Module("pyramid", PACKAGE = "RIPOpenCV")
    mpyramid$pyramidDown(img, size, borderType)
}

pyrMeanShiftFiltering <- function(img, sp, sr, maxlevel)
{
    cvdim <- attr(img, 'cvdim')
    if (cvdim[3] != 3)
        error("Only 3-channel images are supported")
    mpyramid <- Module("pyramid", PACKAGE = "RIPOpenCV")
    mpyramid$pyrMeanShtFlt(img, sp, sr, maxlevel)
}

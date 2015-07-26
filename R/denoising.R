##' .. content for \description{} (no empty lines) ..
##'
##' .. content for \details{} ..
##' @title Image denoising by NLM Algorithm
##' @param img rip object of 1, 2 or 3 channels
##' @param h  Parameter regulating filter strength. 
##' @param templeteWindowSize Size in pixels of the template patch that is used to compute weights. Should be odd
##' @param searchWindowSize Size in pixels of the window that is used to compute weighted average for given pixel. Should be odd.
##' @return Denoised rip object with the same size as \code{img}
##' @author Kaustav Nandy
fastNlMeansDenoising <- function(img, h, templeteWindowSize, searchWindowSize)
{
    mdenoise <- Module("denoise", PACKAGE = "RIPOpenCV")
    mdenoise$nlmeansDenoising(img,  h, templeteWindowSize, searchWindowSize)
}
##' .. content for \description{} (no empty lines) ..
##'
##' .. content for \details{} ..
##' @title Image denoising by NLM Algorithm for colored image
##' @param img rip object of 3 channels
##' @param h Parameter regulating filter strength. 
##' @param templeteWindowSize Size in pixels of the template patch that is used to compute weights. Should be odd
##' @param searchWindowSizeSize in pixels of the window that is used to compute weighted average for given pixel. Should be odd. 
##' @return Denoised rip object with the same size as \code{img}
##' @author Kaustav Nandy
fastNlMeansDenoisingColored <- function(img, h, templeteWindowSize, searchWindowSize)
{
    mdenoise <- Module("denoise", PACKAGE = "RIPOpenCV")
    mdenoise$nlmeansDenoisingCol(img,  h, templeteWindowSize, searchWindowSize)
}

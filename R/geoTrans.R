##' Resize a rip object
##'
##' .. content for \details{} ..
##' @title Resize a rip object using mentioned method
##' @param img rip object with one or three channels
##' @param dsize two elements vector of output image size; if it equals 0, it is computed from \code{fx} and \code{fy}, and they have to be non-zero
##' @param fx scale factor in the horizontal axis
##' @param fy scale factor in the vertical axis
##' @param interp interpolation methods. Possible values are 
##' \itemize {
##'     \item{0}{for nearest neighbor interpolation}
##'     \item{1}{for linear interpolation}
##'     \item{2}{for bicubic interpolation over 4x4 pixel neighborhood}
##'     \item{3}{resampling using pixel area relation}
##'     \item{4}{a Lanczos interpolation over 8x8 pixel neighborhood}
##' }
##' @return resized rip object
##' @author Kaustav Nandy
imResize <- function(img, dsize, fx, fy, interp)
{
    mgeo <- Module("geoTrans", PACKAGE = "RIPOpenCV")
    mgeo$imresize(img, dsize, fx, fy, interp)
}

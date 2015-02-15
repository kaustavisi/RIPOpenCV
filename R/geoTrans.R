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

##' Applies affine warp to an image
##'
##' .. content for \details{} ..
##' @title Applies affine warp to an image
##' @param img rip object with one or three channels
##' @param tmat 2x3 transformation matrix (rip object)
##' @param size dimension of the output image
##' @param flags Interpolation method 
##' @return rip object after affine warpping
##' @author Kaustav Nandy
wrap.affine <- function(img, tmat, size, flags)
{
    mgeo <- Module("geoTrans", PACKAGE = "RIPOpenCV")
    mgeo$affineWarp(img, tmat, size, flags)
}

##' Invert an affine transformation
##'
##' .. content for \details{} ..
##' @title Invert an affine transformation
##' @param tmat affine transformation matrix (rip object)
##' @return Inverse affine transformation matrix as a rip object 
##' @author Kaustav Nandy
invertAffineTrans <- function(tmat)
{
    mgeo <- Module("geoTrans", PACKAGE = "RIPOpenCV")
    mgeo$affineTransInvert(tmat)
}

##' Apples perspective transformation to an image
##'
##' .. content for \details{} ..
##' @title Perspective Transformation
##' @param img rip object of one or three channels
##' @param tmat 3x3 transformation matrix
##' @param size dimension of the output rip object
##' @return transformed rip object of same type as img
##' @author Kaustav Nandy
warp.perspective <- function(img, tmat, size)
{
    mgeo <- Module("geoTrans", PACKAGE = "RIPOpenCV")
    mgeo$perspectiveWarp(img, tmat, size)
}

##' Retrieves a pixel rectangle from an image with sub-pixel accuracy.
##'
##' .. content for \details{} ..
##' @title Retrives pixel rectangle
##' @param img rip object
##' @param patchSize dimension of the output retcangle rip object patch
##' @param center coordinates of the center of the extracted rectangle within the source image
##' @param patchType depth of the extracted pixels. Negative value means the same depth as \code{img}
##' @return 
##' @author Kaustav Nandy
getRectSubPix <- function(img, patchSize, center, patchType=-1)
{
    mgeo <- Module("geoTrans", PACKAGE = "RIPOpenCV")
    mgeo$rectSubPix(img, patchSize, center, patchType)
}


##' Calculates an affine matrix of 2D rotation
##'
##' .. content for \details{} ..
##' @title Affine matrix of 2D rotation
##' @param center center of the rotation in source image
##' @param angle Rotation angle in degrees. Positive values mean counter-clockwise rotation (the coordinate origin is assumed to be the top-left corner)
##' @param scale Isotropic scale factor
##' @return 2x3 rip object of affine transformation
##' @author Kaustav Nandy
getRotationMat <- function(center, angle, scale)
{
    mgeo <- Module("geoTrans", PACKAGE = "RIPOpenCV")
    mgeo$getRotMat(center, angle, scale)
}

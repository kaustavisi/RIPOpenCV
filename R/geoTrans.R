##' Resize a rip object
##'
##' .. content for \details{} ..
##' @title Resize a rip object using mentioned method
##' @param img rip object with one or three channels
##' @param dsize two elements vector of output image size; if it equals 0, it is computed from \code{fx} and \code{fy}, and they have to be non-zero
##' @param fx scale factor in the horizontal axis
##' @param fy scale factor in the vertical axis
##' @param interpolation interpolation methods. Possible values are 
##' \itemize {
##'     \item{0}{for nearest neighbor interpolation}
##'     \item{1}{for linear interpolation}
##'     \item{2}{for bicubic interpolation over 4x4 pixel neighborhood}
##'     \item{3}{resampling using pixel area relation}
##'     \item{4}{a Lanczos interpolation over 8x8 pixel neighborhood}
##' }
##' @return resized rip object
##' @author Kaustav Nandy
resize <- function(img, dsize, fx, fy, interpolation=1)
{
    mgeo <- Module("geoTrans", PACKAGE = "RIPOpenCV")
    mgeo$imresize(img, dsize, fx, fy, interpolation)
}

##' Applies affine warp to an image
##'
##' .. content for \details{} ..
##' @title Applies affine warp to an image
##' @param img rip object with one or three channels
##' @param tmat 2x3 transformation matrix (rip object)
##' @param size dimension of the output image
##' @param flags Interpolation method 
##' @param borderMode pixel extrapolation method.
##' @return rip object after affine warpping
##' @author Kaustav Nandy
wrapAffine <- function(img, tmat, size, flags=1, borderMode=4)
{
    mgeo <- Module("geoTrans", PACKAGE = "RIPOpenCV")
    mgeo$affineWarp(img, tmat, size, flags, borderMode)
    ## FIXME: borderMode == 0 will not work. Need to see how we can incorporate
    ## borderValue = something in case of constant border
}

##' Invert an affine transformation
##'
##' .. content for \details{} ..
##' @title Invert an affine transformation
##' @param tmat affine transformation matrix (rip object)
##' @return Inverse affine transformation matrix as a rip object 
##' @author Kaustav Nandy
invertAffineTransform <- function(tmat)
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
warpPerspective <- function(img, tmat, size)
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
##' @return rectangular subset of the rip object
##' @author Kaustav Nandy
getRectSubPix <- function(img, patchSize, center)
{
    mgeo <- Module("geoTrans", PACKAGE = "RIPOpenCV")
    mgeo$rectSubPix(img, patchSize, center)
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
getRotationMat2D <- function(center, angle, scale)
{
    mgeo <- Module("geoTrans", PACKAGE = "RIPOpenCV")
    mgeo$getRotMat(center, angle, scale)
}

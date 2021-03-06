##' Bilateral Filter
##'
##' .. content for \details{} ..
##' @title Apply bilateral filter to an image
##' @param img rip object with 1 or 3 channels
##' @param d diameter of each pixel neighborhood that is used during filtering. If it is non-positive, it is computed \code{sigmaSpace}
##' @param sigmaCol Filter sigma in the color space. A larger value of the parameter means that farther colors within the pixel neighborhood (see \code{sigmaSpace} ) will be mixed together, resulting in larger areas of semi-equal color.
##' @param sigmaSpace Filter sigma in the coordinate space. A larger value of the parameter means that farther pixels will influence each other as long as their colors are close enough (see \code{sigmaCol} ). When \code{d}>0 , it specifies the neighborhood size regardless of sigmaSpace . Otherwise, d is proportional to sigmaSpace
##' @return Filtered rip object
##' @author Kaustav Nandy
bilateralFilter <- function(img, d, sigmaCol, sigmaSpace, borderType = 4)
{
    mblur <- Module("Blur", PACKAGE = "RIPOpenCV")
    mblur$bilatFilter(img, d, sigmaCol, sigmaSpace)
}

##' Normalized Boxed Blur
##'
##' .. content for \details{} ..
##' @title Normalized Boxed Blur
##' @param img rip object with 1 or 3 channels
##' @param size a vector with two elements consisting of dimension of the blur kernel
##' @return blurred rip object
##' @author Kaustav Nandy
blur <- function(img, size, anchor=c(-1, -1), borderType = 4)
{
    mblur <- Module("Blur", PACKAGE = "RIPOpenCV")
    mblur$normBoxBlur(img, size, anchor, borderType)
}

##' .. content for \description{} (no empty lines) ..
##'
##' .. content for \details{} ..
##' @title Blurs an image using the box filter
##' @param img rip object with 1 or 3 channels
##' @param ksize Size of the kernel
##' @param anchor anchor point; default value c(-1,-1) means that the anchor is at the kernel center.
##' @param normalize flag, specifying whether the kernel is normalized by its area or not. Default value is TRUE.
##' @param borderType border mode used to extrapolate pixels outside of the image.
##' @return output rip object of the same size as \code{img}
##' @author kaustav nandy
boxFilter <- function(img, ksize, anchor=c(-1, -1),
                      normalize=TRUE, borderType=4)
{
    mblur <- Module("Blur", PACKAGE = "RIPOpenCV")
    mblur$boxBlur(img, ksize, anchor, normalize, borderType)
}


##' Apply Gaussian filter to an image
##'
##' .. content for \details{} ..
##' @title Gaussian filter 
##' @param img rip object of 1 or 3 channels
##' @param size vector with two elements consisting of the dimension of the blur kernel. Each element of should be odd or 0. If they are zero, then they are computed from \code{sigmaX} and \code{sigmaY}
##' @param sigamX Gaussian kernel standard deviation in X direction
##' @param sigmaY Gaussian kernel standard deviation in Y direction. If \code{sigmaY} is 0 it is set to be equal to \code{sigmaX}. If both sigmas are zero, they are computed from \code{size}
##' @return 
##' @author Kaustav Nandy
GaussianBlur <- function(img, size, sigmaX = 0, sigmaY = 0, borderType = 4)
{
    mblur <- Module("Blur", PACKAGE = "RIPOpenCV")
    mblur$gaussianBlur(img, size, sigmaX, sigmaY, borderType)
}


##' Convolves an image with the kernel
##'
##' .. content for \details{} ..
##' @title 
##' @param img rip object of 1 or 3 channels
##' @param kern Convolution kernel. A rip object with 1 channel.
##' @param anchor  anchor of the kernel that indicates the relative position of a filtered point within the kernel; the anchor should lie within the kernel. Value (-1,-1) means the anchor is an the kernel center.
##' @param delta optional value added to the filtered pixels. Default value is 0.
##' @param borderType FIXME: Write details of border type
##' @return convolved rip object
##' @author Kaustav Nandy
filter2D <- function(img, kern, anchor=c(-1,-1), delta=0, borderType=4)
{
    mblur <- Module("Blur", PACKAGE = "RIPOpenCV")
    mblur$filter2d(img, kern, anchor, delta, borderType)
}

##' .. content for \description{} (no empty lines) ..
##'
##' .. content for \details{} ..
##' @title Performs 2-D convolution
##' @param img rip object to be convoluted
##' @param kern convolution kernel
##' @param type It can be one of the three values:
##' \item{full}{full two dimensional convolution}
##' \item{valid}{convolution without using the zero-padded edges}
##' \item{same}{central part of the convolution, same as the dimension of img$Data}
##' @return Convolved image as rip object
##' @author Kaustav Nandy
conv2D <- function(img, kern, type=c("full","valid","same"))
{
    itype <- switch(type, full=-1, same=0, valid=1, 0) 
    mblur <- Module("Blur", PACKAGE = "RIPOpenCV")
    mblur$conv2(img, kern, itype)
}

##' Returns filter coefficients for computing spatial image derivatives
##'
##' .. content for \details{} ..
##' @title Get derivative kernel 
##' @param dx deivative order with respect to x
##' @param dy derivative order with respect to y
##' @param ksize Apperture size. It can be 1, 3, 5 or 7.
##' @param normalize Flag indicating whether to normalize (scale down) the filter coefficients or not. 
##' @param ktype  Type of filter coefficients, should be 5 (32 bit float) or 6 (64 bit float i.e. double).
##' @return List of two:
##' \itemize{
##' \item{kernel.x}{rip object of row filter coefficients}
##' \item{kernel.y}{rip object of column filter coefficients}
##' }
##' @author Kaustav Nandy
getDerivKernels <- function(dx, dy, ksize,
                           normalize, ktype)
{
    mblur <- Module("Blur", PACKAGE = "RIPOpenCV")
    mblur$derivKernel(dx, dy, ksize, normalize, ktype)
}

##' Calculate Gaussian filter coefficients
##'
##' .. content for \details{} ..
##' @title Returns Gaussian filter coefficients
##' @param ksize Aperture size. It should be odd and positive.
##' @param sigma Gaussian standard deviation. If it is non-positive, it is computed from ksize as sigma = 0.3*((ksize-1)*0.5 - 1) + 0.8 .
##' @param ktype Type of filter coefficients. It can be 5 or 6.
##' @return ksize x 1 matrix of Gaussian filter coefficients.
##' @author Kaustav Nandy
getGaussianKernel <- function(ksize, sigma, ktype)
{
    mblur <- Module("Blur", PACKAGE = "RIPOpenCV")
    mblur$getGaussKern(ksize, sigma, ktype);
}

##' Calculate Gabon Filter Coefficients
##'
##' .. content for \details{} ..
##' @title Gabon filter coefficients
##' @param ksize size of filter returned
##' @param sigma Standard deviation of the gaussian envelope
##' @param theta Orientation of the normal to the parallel stripes of a Gabor function
##' @param lambd Wavelength of the sinusoidal factor
##' @param gamma Spatial aspect ratio
##' @param psi Phase offset
##' @param ktype Type of filter coefficients. It can be 5 or 6
##' @return 
##' @author Kaustav Nandy
getGaborKernel <- function(ksize, sigma, theta, lambd, gamma,
                           psi=pi * .5, ktype=6)
{
    mblur <- Module("Blur", PACKAGE = "RIPOpenCV")
    mblur$getGaborKern(ksize, sigma, theta, lambd, gamma,
                           psi, ktype)
}


##' .. content for \description{} (no empty lines) ..
##'
##' .. content for \details{} ..
##' @title Median Blur
##' @param img rip object fo 1, 3 or 4 channels
##' @param ksize apperture linear size, it must be odd and greater that 1.
##' @return rip object blurred using median blur.
##' @author Kaustav Nandy
medianBlur <- function(img, ksize=3)
{
    mblur <- Module("Blur", PACKAGE = "RIPOpenCV")
    mblur$mediBlur(img, ksize)
}

##' .. content for \description{} (no empty lines) ..
##'
##' .. content for \details{} ..
##' @title Square box filter
##' @param img rip object
##' @param ddepth the output image depth. -1 is used if the depth is the same as depth of \code{img}
##' @param ksize kernel size. A vector with two elements with the size in each direction
##' @param anchor kernel anchor point. The value (-1, 1) indicates that the anchor is at kernel center.
##' @param normalize 
##' @return rip object of same size as \code{img}
##' @author Kaustav Nandy
## sqrBoxFilter <- function(img, ddepth, ksize, anchor, normalize=TRUE)
## {
##     mblur <- Module("Blur", PACKAGE = "RIPOpenCV")
##     mblur$sqBoxFilter(img, ddpeth, ksize, anchor, normalize)
## }

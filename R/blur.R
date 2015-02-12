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

filter.bilat <- function(img, d, sigmaCol, sigmaSpace)
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

filter.normBox <- function(img, size)
{
    mblur <- Module("Blur", PACKAGE = "RIPOpenCV")
    mblur$normBoxBlur(img, size)
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

filter.gaussian <- function(img, size, sigmaX, sigmaY)
{
    mblur <- Module("Blur", PACKAGE = "RIPOpenCV")
    mblur$gaussianBlur(img, size, sigmaX, sigmaY)
}


##' Convolves an image with the kernel
##'
##' .. content for \details{} ..
##' @title 
##' @param img rip object of 1 or 3 channels
##' @param depth desired depth of the output image
##' @param kern Convolution kernel. A rip object with 1 channel.
##' @param anchor  anchor of the kernel that indicates the relative position of a filtered point within the kernel; the anchor should lie within the kernel. Value (-1,-1) means the anchor is an the kernel center.
##' @param delta optional value added to the filtered pixels. Default value is 0.
##' @return convolved rip object
##' @author Kaustav Nandy

filter2D <- function(img, depth, kern, anchor=c(-1,-1), delta=0)
{
    mblur <- Module("Blur", PACKAGE = "RIPOpenCV")
    mblur$filter2d(img, depth, kern, anchor, delta)
}

##' .. content for \description{} (no empty lines) ..
##'
##' .. content for \details{} ..
##' @title Erodes an image using a specific structuring element
##' @param img rip object of 1 or 3 channels. 
##' @param kern structuring element
##' @param anchor position of anchor. Anchor value (-1, 1) means that the anchor is at the element center.
##' @param iter Number of times erosion to be applied
##' @return Eroded rip object of same channel and depth as img.
##' @author Kaustav Nandy
erode <- function(img, kern, anchor, iter)
{
    mmorph <- Module("Morph", PACKAGE = "RIPOpenCV")
    mmorph$imageErode(img, kern, anchor, iter)
}

##' .. content for \description{} (no empty lines) ..
##'
##' .. content for \details{} ..
##' @title Dilate an image using a specific structuring element.
##' @param img rip object of 1 or 3 channels. 
##' @param kern structuring element.
##' @param anchor position of anchor. Anchor value (-1, 1) means that the anchor is at the element center.
##' @param iter Number of times erosion to be applied
##' @return Dilated rip object of same channel and depth as img.
##' @author Kaustav Nandy
dilate <- function(img, kern, anchor, iter)
{
    mmorph <- Module("Morph", PACKAGE = "RIPOpenCV")
    mmorph$imageDilate(img, kern, anchor, iter)
}

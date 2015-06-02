##' .. content for \description{} (no empty lines) ..
##'
##' .. content for \details{} ..
##' @title Reading an image
##' @param file path of the image file
##' @param type One of 0, -1, +1. 0 means the image will be imported as greyscale, 1 means it will be imported as 3 channel images, -1 means it will be imported in the format the file actually is. 
##' @return image as a rip object.
##' @author Kaustav Nandy
readImage <- function(file, type)
{
    mi <- Module("R2R", PACKAGE = "RIPOpenCV")
    mi$importImage(file, type)
}

##' .. content for \description{} (no empty lines) ..
##'
##' .. content for \details{} ..
##' @title Writing an image
##' @param outFile output file name.
##' @param img rip object of 1 or 3 channels
##' @return 
##' @author Kaustav Nandy
writeImage <- function(outFile, img)
{
    mi <- Module("R2R", PACKAGE = "RIPOpenCV")
    mi$writeImage(img, outFile)
}

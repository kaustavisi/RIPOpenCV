
##' Richadson Lucy Algorithm for image deconvolution
##'
##' .. content for \details{} ..
##' @title Richardson Lucy algorithm
##' @param origImage Original rip image 
##' @param intiImage Initial guess
##' @param kernel blur kernel
##' @param iter number of iteration
##' @param ind Method to be use. FIXME: Detele it upon checking
##' @return Deblurred rip image.
##' @author Kaustav Nandy

rlalgo <- function(origImage, initImage, kernel, iter, ind)
{
    mrla <- Module("rla", PACKAGE = "RIPOpenCV")
    if(sum(dim(origImage$Data) != dim(initImage$data)) != 0)
        stop("initImage should be of same size as origImage")
    if((origImage$Dimension)[3] != 1)
        stop("Only single channel images are allowed")
    mrla$RLA(origImage, initImage, kernel, iter, ind)
}

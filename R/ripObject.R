##' Convert data matrix to rip object
##'
##' .. content for \details{} ..
##' @title Convert to rip object
##' @param x Matrix containing data of rip object. If there are more than one channels in the rip object, they should be put in succsessive columns
##' @param channel number of channels in the rip object
##' @param type type of the rip object
##' @param depth depth of the rip object
##' @return converted rip object
##' @author Kaustav Nandy
as.rip <- function(x, channel, type, depth)
{
    if(length(dim(x)) != 2)
        stop("x should be a matrix")
    else {
        a <- (list("Data"=x, "Dimension"=c(dim(x), channel, type, depth)))
        class(a) <- "rip"
        return (a)
    }
}

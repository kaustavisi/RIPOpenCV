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
as.rip <- function(x, channel = 1, type = 5, depth = 5)
{
    d <- dim(x)
    if (length(d) != 2) stop("x must be a matrix")
    attr(x, "cvdim") <- c(nrow = d[1], ncol = d[2]/channel,
                          nchannel = channel,
                          type = type, depth = depth)
    class(x) <- "rip"
    x
}

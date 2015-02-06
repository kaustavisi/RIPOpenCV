
##' Print method for rip objects
##'
##' .. content for \details{} ..
##' @title 
##' @param x An object of class 'rip'
##' @param ... 
##' @return 
##' @author Deepayan Sarkar
print.rip <- function(x, ...)
{
    d <- x$Dimension
    cat(sprintf("[%g x %g] image with %g channel(s)\n", d[1], d[2], d[3]))
}



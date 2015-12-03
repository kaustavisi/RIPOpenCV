
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
    d <- attr(x, "cvdim")
    cat(sprintf("[%g x %g] image with %g channel(s)\n", d[1], d[2], d[3]))
}


image.rip <- function(x, ..., rescale = TRUE)
{
    cvdim <- attr(x, "cvdim")
    if (cvdim[3] != 1)
    {
        dim(x) <- cvdim[c("nrow", "nchannel", "ncol")]
        x <- aperm(x, c(1, 3, 2))
        x <- x[,,3:1]
    }
    if (rescale) x[] <- 255 * (x - min(x)) / (max(x) - min(x))
    x <- as.raster(unclass(x), max = 255)
    opar <- par(mar = c(3, 3, 1, 1) + 0.1)
    on.exit(par(opar))
    plot(c(0, ncol(x) + 1), c(0, nrow(x) + 1),
         type = "n", xaxs = "i", yaxs = "i",
         xlab = "", ylab = "")
    rasterImage(x, 1, 1, ncol(x), nrow(x), interpolate = FALSE)
}



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


image.rip <- function(x, ..., rescale = FALSE)
{
    if (x$Dimension[3] == 1)
        m <- x$Data
    else
    {
        m <- x$Data
        dim(m) <- x$Dimension[c(1, 3, 2)]
        m <- aperm(m, c(1, 3, 2))
        m <- m[,,3:1]
    }
    if (rescale) m[] <- 255 * (m - min(m)) / (max(m) - min(m))
    m <- as.raster(m, max = 255)
    opar <- par(mar = c(3, 3, 1, 1) + 0.1)
    on.exit(par(opar))
    plot(c(0, ncol(m) + 1), c(0, nrow(m) + 1),
         type = "n", xaxs = "i", yaxs = "i",
         xlab = "", ylab = "")
    rasterImage(m, 1, 1, ncol(m), nrow(m), interpolate = FALSE)
}


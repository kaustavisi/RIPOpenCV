##' .. content for \description{} (no empty lines) ..
##'
##' .. content for \details{} ..
##' @title compute ordinary image gradient. 
##' @param img 
##' @return 
##' @author Kaustav Nandy

image.gradient <- function(img)
{
    dat <- img$Data
    dimg <- dim(dat)
    x.dir <- dat[,-1] - dat[,-dimg[2]]
    y.dir <- dat[-1,] - dat[-dimg[1],]
    list("x.direction" = x.dir, "y.direction" = y.dir)
}

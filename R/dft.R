dft <- function(img, flags, nonZeroRows)
{
    mdft <- Module("Dft", PACKAGE = "RIPOpenCV")
    mdft$DFT(img, flags, nonZeroRows)
}

idft <- function(img, flags, nonZeroRows)
{
    mdft <- Module("Dft", PACKAGE = "RIPOpenCV")
    mdft$IDFT(img, flags, nonZeroRows)
}

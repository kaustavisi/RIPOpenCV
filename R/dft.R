dft <- function(img, flags, nonZeroRows)
{
    mdft <- Module("Dft", PACKAGE = "RIPOpenCV")
    mdft$dft(img, flags, nonZeroRows)
}

idft <- function(img, flags, nonZeroRows)
{
    mdft <- Module("Dft", PACKAGE = "RIPOpenCV")
    mdft$idft(img, flags, nonZeroRows)
}

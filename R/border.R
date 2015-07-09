copyMakeBorder <- function(img, top, bottom, left, right, borderType)
{
    mborder <- Module("border", PACKAGE = "RIPOpenCV")
    mborder$copymakeborder(img, top, bottom, left, right, borderType)
}

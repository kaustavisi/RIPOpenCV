copyMakeBorder <- function(img, top, bottom, left, right, borderType = 4)
{
    mborder <- Module("border", PACKAGE = "RIPOpenCV")
    mborder$copymakeborder(img, top, bottom, left, right, borderType)
}

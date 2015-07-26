**Installing RIPOpenCV**

1. Install OpenCV 3.0. Instructions can be found [here](http://docs.opencv.org/3.0-beta/doc/tutorials/introduction/linux_install/linux_install.html)
2. Clone the RIPOpenCV package from https://github.com/kaustavisi/RIPOpenCV.git
3. In the terminal run R CMD build RIPOpenCV on the same directory.
4. Run `R CMD INSTALL RIPOpenCV_<version>.tar.gz`. Substitute <version> with appropriate version of the package.


**Troubleshoothing**

- There is a common problem that the installation fails with an error similar to the following:

```
libopencv_shape.so.3.0: cannot open shared object file: No such file or directory
```

This means the loader is failing to find the library location. A possible method of tackling this error is mentioned [here](http://www.eyrie.org/~eagle/notes/rpath.html).

- All the functions of this package may not work with older versions of OpenCV. 
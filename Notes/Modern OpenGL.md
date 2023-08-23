Windows and various platforms have their own version of graphic APIs native to their platform. To use modern OpenGL functions, which are declared within the graphics card, by the graphic card manufacturers we need to do something.

To use any kind of functionality that is newer than OpenGL 1.1, we need to actually get into those drivers, get the function declarations and then link against the functions as well. We need to access the driver dll files and just retrieve function pointers to the functions inside those libraries.

Manually doing this has the following issues:
- The code will not be cross-platform as calling various functions would be platform dependant as they would use functions defined within the API provided by that particular platform (for example- win32 API on windows).
- Sometimes need may arise to call thousands of functions and doing so manually is very time consuming, meticulous and not practical.

Hence we are going to be using another library to achieve this.

What the library actually does is:
1. It provides the OpenGL API specification, function declarations and symbol declarations, etc. in a header file.
2. The actual implementation of the library identifies what graphics drivers you are using, find the appropriate dll files and then loads all the function pointers.

The library we are going to use is called [GLEW](https://glew.sourceforge.net/).


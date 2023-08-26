OpenGL functions are implemented in gpu drivers.
Get the functions declarations and link against the functions as well.
So we need to access the driver DLL files and retrieve function pointers to the function inside those libraries.

openGL has lot of functions... few problems regarding that
1. It would be not a cross-platform (like we need win32 api calls for windows that wont work on other platforms).
2. For lot of functions we need to go through all of them manually and write code (too hectic).

Hence, we use another library.
 What does library do?
 Provides OpenGL API specifications like function and symbol declarations, constants etc in a header file. The actual implementation of the library goes into the EDI, it identifies what graphics drivers are used and finds the appropriate DLL file and then loads all the function pointers.
 They just access the functions that are already on the computer in binary form.

Library we gonna use is GLEW or the OpenGL Extension Wrangler Library.


 

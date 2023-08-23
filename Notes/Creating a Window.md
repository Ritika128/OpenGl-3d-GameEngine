Creating a window is very platform specific. We will use pre-built [GLFW](https://www.glfw.org/) library to avoid the hassle of making platform specific code to make a window and make our code multi-platform/platform independent.

Steps to create a window:

1. Download the pre-built binaries from the GLFW website linked above and make a new C++ project in Visual Studio.
2. In the solution file of the OpenGL project, make a new folder (dependencies) and copy the include and libvc-(version of visual studio being used) from the downloaded GLFW binaries inside the dependencies/OpenGL folder.
3. Open a new project in Visual Studio and use the sample code provided on the GLFW website to make a window after resolving the OpenGL and win32 API dependencies.

Code to make a window using GLFW:
```c++
#include <GLFW/glfw3.h>

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
```



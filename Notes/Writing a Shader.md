To define the shaders we shall define a separate static int function which shall accept the source code of the vertex and fragment shaders as strings in the form of parameters.

Code Snippet for the implementation of Shaders:

```C++

#include <GLFW/glfw3.h>

  

int main(void)

{

GLFWwindow *window;

  

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

  

float positions[6] = {

-0.5f, -0.5f,

0.0f, 0.5f,

0.5f, -0.5f

};

  

unsigned int buffer;

glGenBuffers(1, &buffer); // This function is generating a buffer and giving us back an id

glBindBuffer(GL_ARRAY_BUFFER, buffer); // THis function is used to select(bind) a buffer

glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW); // This function is used to provide data to the buffer

  

glEnableVertexAttribArray(0);

glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,sizeof(float)*2,0);

glBindBuffer(GL_ARRAY_BUFFER,0);

/* Loop until the user closes the window */

while (!glfwWindowShouldClose(window))

{

/* Render here */

glClear(GL_COLOR_BUFFER_BIT);

glDrawArrays(GL_TRIANGLES,0,3);

  
  

/* Swap front and back buffers */

glfwSwapBuffers(window);

  

/* Poll for and process events */

glfwPollEvents();

}

  

glfwTerminate();

return 0;

}
```

There are multiple ways to compile a shader. Some of the ways are:
- Define them as strings
- Read them from a file
- Download shaders off the internet 

The purpose of the static function is to accept the shader code as parameters, compile them, link the two together as one shader and output a unique identifier.

Functions used:
1. [glShaderSource](https://docs.gl/gl4/glShaderSource): Specifies the source of our shader

	The first parameter to be passed is the id of the shader.

	The second parameter is the amount of source codes we are specifying.

	The third parameter is the address of the pointer of the shader. (double pointer)

	The fourth parameter is the length of the string.

2. glCompileShader: Accepts the id of the shader to be compiled.
3. glAttachShader: Accepts the program and the files to be attached to that program.
4. glLinkProgram: Links the files attached together into one program.
5. glGetShaderiv
6. glGetShaderInfoLog

alloca is a function that c provides you which lets you allocate on the stack dynamically.
 




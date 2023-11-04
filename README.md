
# OpenGL 3D Game Engine

## Aim of the project:
The aim of the project is to make a 3D chess game using C++ and OpenGL Shading Language GLSL.


## Clone and build the programs in the repository

Clone the repo:

```bash
  git clone https://github.com/Ritika128/OpenGl-3d-GameEngine.git
```

To run a specific program:

```bash
  g++ -o executable_name file_name.cpp -lGL -lglfw -DGL_GLEXT_PROTOTYPES -I./glm-master
  ./executable_name
```
Alternatively you may edit the CMakeLists.txt to change the executable and then run the cmake command, followed by the make command.

## Programming Languages Used
* C++
* GLSL



## Libraries Used
* GLES 2.0
* GLFW- Graphics Library Framework (GLFW) allows users to create and manage OpenGL windows, while handling keyboard, mouse and joystick inputs. GLFW and FreeGLUT are alternatives to the same functions.
* GLEW- GLEW (OpenGL Extension Wrangler Library) is a cross-platform C/C++ extension loading library that provides an effcient mechanism to determine which extensions are supported on the platform.
* GLAD- GLAD allows the user to include only those extensions which they wish to, leading to faster compile times. GLEW can detect which dependencies are available at compile time, leading to better adaptability.
* GLM- GLM is a C++ mathematics library for graphics software based on the OpenGL Shading Library(GLSL) specification. We used the GLM library to provide animations to the shapes we rendered using Modern OpenGL. GLM library provides us with matrices and vectors which can be passed to the draw call, and refresh the indices of the shapes rendered, resulting in motion.

## Contributors

* [Anish Mahadevan](https://github.com/Faulty404)
* [Ritika Nankar](https://github.com/Ritika128)


## Acknowledgements

 - [SRA VJTI ](https://sravjti.in/)Eklavya 2023.
 - [Documention for OpenGL functions](https://docs.gl/).
 - [Referred this to implement OpenGL functions and use GLM](https://learnopengl.com/).
 - Special thanks to our mentors [Pratham Deshmukh](https://github.com/Pratham-Bot) and [Komal Sambhus](https://github.com/Komal0103) for guiding us through the Eklavya program.


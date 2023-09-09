**SHADERS**
-**INTRODUCTION**-

What is a shader?
A shader is basically just a program that runs on your GPU, it's a block of code that runs on our GPU on our graphics card and not on our CPU like this C++ program.

two types of shaders we are going to use 
- vertex shaders and
- fragment shaders/ pixel shaders 


How do we go from having data to actually having a result on our screen?

Rendering pipeline -
draw call >> vertex shader >> fragment shader >> result on the screen

**Vertex shader** 
It gets called for each vertex that we're trying to render.
In this case, we have a triangle with three vertices which means that the vertex shader will get called three times. All the vertex shader does is it specifies the way you want the positions to be. It tells OpenGL where you want that vertex to be in your screen space.


**Fragment Shader/ Pixel Shader**
Fragment shader or the pixel shader 
fragments as pixels because the fragment shader is going to run once
for each pixel that needs to get rasterized meaning actually drawn on our screen so our window is made up of pixels and it's like a pixel array.


**Vertex vs Fragment**
The difference between the two first vertex shader gets called three times, fragment shader might get called tens of thousands of times, depending on how much room our actual triangle occupies on our screen. 


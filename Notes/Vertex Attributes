**How does the OpenGL pipeline work?**
- Vertex Buffer - We basically supply our graphics card with data, we store some kind of memory on the GPU which contains all the data of what we want to draw.
- Shaders - Then we use the shader, a program that executes on the GPU to read and display that data on the screen. 

*Vertex* - a point that is on your geometry, it is not a position. It is the whole blob of data, which includes different attributes like  position, texture coordinates, normals, colors, tangents etc.

glVertexAttribPointer specification:
```c++
void glVertexAttribPointer
						(GLuint index,
						Glint size,
						GLenum type,
						GLboolean normalised,
						GLstride,
						const GLvoid* pointer);
```

example:
``` c++
float positions[6]={
     -0.5f, -0.5f,
      0.0f,  0.5f,
      0.5f, -0.5f
};
```

- *index* - specifies the index of generic vertex attribute. 
- *size* - for giving dimensions, must be 1,2,3,4
- *type* - type of data we are providing (here its float)
- *normalised* - if we are specifying a byte that is between 0 and 255 (color value) that needs to be normalised between 0 and 1. 
- *stride* - the amount of bytes between each vertex. (size of type x *size*). This is the amount that we need to go forward to get to the second vertex.
- *pointer* -  as the attributes are added pointer is changed. If only one attribute then the pointer is 0. Here only the positions attribute is given so it will be 0, if we add the texture attribute the pointer will be 8 (in bytes) [syntax - (const void*)8]

glVertexAttribPointer specification of the example:
```c++
glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float)*2, 0);
```

Lastly, we need to **enable** that vertex attribute or else we are just going to get black screen.
[glEnableVertexAttriArray(index);]

for enabling the example:
```c++
glEnableVertexAttriArray(0);
```






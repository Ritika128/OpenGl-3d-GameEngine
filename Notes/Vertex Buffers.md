Drawing a triangle in OpenGL
Vertex Buffers and Shaders to be created. 
Buffer is array of bytes of memory. 
The difference between a normal memory buffer and a vertex buffer is that a vertex buffer is in OpenGL i.e in our GPU and VRAM.

- Define bunch of data which represents a triangle 
- then put it into GPU's VRAM
- issue a draw call (its a draw command which reads the data from VRAM and draw it on a screen)
How to read and interpret the data and put it on screen?
- Using Shaders which allow us to write code on the GPU instead of CPU. 

OpenGL operates as a state machine. 
Based on what buffer and shader is selected determines what and where triangle gets drawn.


Code snippet
``` c++
//vertex positions
float positions[6]={
     -0.5f, -0.5f,
      0.0f,  0.5f,
      0.5f, -0.5f
};
defining vertex buffer
unsigned int buffer;
g1GenBuffers(1, &buffer); //generates a buffer and gives back id
glBindBuffer(GL_ARRAY_BUFFER, buffer); //selecting that buffer
glBufferData(GL_ARRAY_BUFFER, 6*sizeof(float), positions, GL_STATIC_DRAW); //provides data to the buffer

```
 Documentation resource for OpenGL
 [http://docs.gl](https://www.youtube.com/redirect?event=video_description&redir_token=QUFFLUhqa00yX3ItTUJweDE1azFaN0FLbGgyaUFBOVB4UXxBQ3Jtc0trRmJpMGhxRGxqTVpUazRWZG5CaTljZ2VmT0l1N3NscUtMMVJjWFFQU05COUh4cVlhSXJBTmtjLW5XaF9wRC1SZ2wtM0lWbmRlMGhjRWFFMVdDRm1HbWZfUlJzTXlzLWVFYWZId2VKc1JQMWNuSWNxaw&q=http%3A%2F%2Fdocs.gl%2F&v=0p9VxImr7Y0)

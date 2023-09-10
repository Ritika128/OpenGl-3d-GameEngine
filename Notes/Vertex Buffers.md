To make a triangle using Modern OpenGL we need to create a **vertex buffer** and we need to also be able to create a **shader**.

A vertex buffer is an array of bytes of memory or a memory buffer. The difference between a normal memory buffer and a vertex buffer is that a vertex buffer is in OpenGL, i.e in out GPU. So the memory is not allocated in the RAM, but rather allocated in the VRAM (Video Random Access Memory).

A shader is a program or a block of code that actually runs on the GPU, instead of the CPU.

OpenGL basically acts like a state machine. Almost all of the OpenGL functions set or retrieve some state in OpenGL. OpenGL assigns a unique id to every function/buffer/shader/array which can be used later to call/operate on said function/buffer/shader/array.

Code snippet to define a buffer:

```c++
float positions[6]={
     -0.5f, -0.5f,
      0.0f,  0.5f,
      0.5f, -0.5f
};

unsigned int buffer;
glGenBuffers(1, &buffer); //This function is generating a buffer and giving us back an id
glBindBuffer(GL_ARRAY_BUFFER, buffer );//THis function is used to select(bind) a buffer
glBufferData(GL_ARRAY_BUFFER, 6*sizeof(float), positions, GL_STATIC_DRAW);//This function is used to provide data to the buffer
```

Detailed information on the functions used:
[glGenBuffers](https://docs.gl/gl4/glGenBuffers)
[glBindBuffers](https://docs.gl/gl4/glBindBuffer)
[glBufferData](https://docs.gl/gl4/glBufferData)

Since OpenGL is a state machine , the buffer that is bounded will be the one that will be executed.

## glGenBuffers:

This function takes two parameters. 

The first parameter accepts an integer to specify how many buffers you would like to generate. 

The second parameter accepts a pointer to an unsigned int. This unsigned int's memory is written on by the buffer.

This function is generating a buffer and giving us back an id.

## glBindBuffer:

This function is used to select/bind a defined buffer using its id. 

The first parameter is the target to which the buffer object is bound. Detailed information is given in the link provided above.

The second parameter is the name of the buffer object to be selected/bound. (The name of the unsigned int)
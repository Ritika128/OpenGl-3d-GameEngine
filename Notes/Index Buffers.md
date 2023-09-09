**INDEX BUFFER**
Anything we draw is made of triangles in the GPU
For example square and a rectangle are two triangles

Vertices for triangle
```c++
float positions [6] = 
		{
		-0.5f, -0.5f, 
		0.0f, 0.5f, 
		0.5f, -0.5f
		}
```

Vertices for the right land left side of a square i.e. right angled triangles
```c++
float positions [] = 
		{
		-0.5f, -0.5f, 
		0.5f, -0.5f, 
		0.5f, 0.5f

		0.5f, 0.5f, 
		-0.5f, 0.5f, 
		-0.5f, -0.5f
		}
```

Vertices for square using index buffer
```c++
float positions [] = {
		-0.5f, -0.5f,  //0
		 0.5f, -0.5f,  //1
		 0.5f,  0.5f,  //2
		-0.5f,  0.5f   //3
};
//index buffer
unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
};
```

An index buffer is a way to tell a computer how to connect points to create shapes in 3D graphics, making it more efficient and saving memory.

*Any buffers have to be made of **unsigned integers.***


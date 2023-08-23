To actually perform a task with the data provided in the vertex buffer, we need to tell OpenGL , what each byte of data represents and how it should be interpreted. Vertex attributes and shaders are used to achieve this.

[Information on glVertexAttribPointer](https://docs.gl/gl4/glVertexAttribPointer)

Code snipper for assigning vertex attributes:

```C++
glEnableVertexAttribArray(0);
glVertexAttribPointer(0, 2, GL_GLOAT , GL_FALSE , sizeof(float) * 2 , 0 );
```

To enable and disable a generic vertex attribute array, call [glEnableVertexAttribArray](https://docs.gl/gl4/glEnableVertexAttribArray) and [glDisableVertexAttribArray](https://docs.gl/gl4/glDisableVertexAttribArray) with _`index`_. If enabled, the generic vertex attribute array is used when [glDrawArrays](https://docs.gl/gl4/glDrawArrays), [glMultiDrawArrays](https://docs.gl/gl4/glMultiDrawArrays), [glDrawElements](https://docs.gl/gl4/glDrawElements), [glMultiDrawElements](https://docs.gl/gl4/glMultiDrawElements), or [glDrawRangeElements](https://docs.gl/gl4/glDrawRangeElements) is called.
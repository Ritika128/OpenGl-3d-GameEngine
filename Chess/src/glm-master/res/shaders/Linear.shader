#shader vertex
#version 330 core
 
layout(location=0) in vec4 position;
uniform mat4 transform;

void main()
{
    gl_Position = transform*position;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

void main()
{
    color = vec4(1.0,0.0,0.0,1.0);
}
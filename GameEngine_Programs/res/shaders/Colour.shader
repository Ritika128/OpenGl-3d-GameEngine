#shader vertex
#version 330 core
 
layout(location=0) in vec4 position;

out vec4 vertexColor;
uniform mat4 transform;

void main()
{
    gl_Position = transform*position;
    vertexColor = vec4(position);
};

#shader fragment
#version 330 core

in vec4 vertexColor;
layout(location = 0) out vec4 color;

void main()
{
    color = vertexColor;
}
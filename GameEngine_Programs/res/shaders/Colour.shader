#shader vertex
#version 330 core
 
layout(location=0) in vec4 position;
layout(location=1) in vec3 facecolor;

out vec4 vertexColor;
uniform mat4 transform;

void main()
{
    gl_Position = transform*position;
    vertexColor = vec4(facecolor,1.0);
};

#shader fragment
#version 330 core

in vec4 vertexColor;
layout(location = 0) out vec4 color;

void main()
{
    color = vertexColor;
}
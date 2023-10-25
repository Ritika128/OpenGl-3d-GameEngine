#shader vertex
#version 330 core
 
layout(location=0) in vec4 position;
layout(location=1) in vec3 Colour;
out vec4 FragColour;
uniform mat4 transform;

void main()
{
    gl_Position = transform*position;
    FragColour = vec4(Colour,0.0);
};

#shader fragment
#version 330 core

in vec3 FragColour;
out vec4 color;

void main()
{
    color = vec4(FragColour,0.0);
}
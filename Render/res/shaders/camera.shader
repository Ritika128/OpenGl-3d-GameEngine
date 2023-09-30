#shader vertex
#version 120

uniform mat4 view;
varying vec4 vertexColor;
void main()
{
    gl_Position = gl_ModelViewMatrix * gl_Vertex;
    gl_Position = gl_Position * view;
    vertexColor =  vec4(gl_Position);
}

#shader fragment
#version 120
varying vec4 vertexColor;
void main()
{
    gl_FragColor = vertexColor;
}

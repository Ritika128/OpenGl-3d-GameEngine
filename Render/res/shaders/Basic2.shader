#shader vertex
#version 120        
attribute vec4 position;     
void main()
{
 gl_Position = position;
}

#shader fragment
#version 120

uniform vec4 u_color;

void main()
{
 gl_FragColor = u_color;
}


#shader vertex
#version 120
attribute vec4 position;
uniform mat4 transform;
varying vec4 vertexColor;
void main()
{
    gl_Position = transform * position;
    vertexColor =  vec4(position);
}

#shader fragment
#version 120 
varying vec4 vertexColor;
void main()
{
    //gl_FragColor = vec4(0.5, 0.0, 0.0, 1.0);
    gl_FragColor = vec4(0.6, 0.8, 1.0, 1.0); //pastel blue
    
}

#shader vertex
#version 120
attribute vec4 position;
varying vec2 texCoord;
void main()
{
    gl_Position = position;
    texCoord = (position + vec2(1.0)/vec2(2.0));
      
}

#shader fragment
#version 120
uniform vec4 color;
void main()
{
        gl_FragColor = color; 
}

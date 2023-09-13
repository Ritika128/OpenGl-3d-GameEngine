#shader vertex

#version 120
uniform mat4 translation; 
attribute vec4 position;     
void main()
{
    vec4 translatedPosition = translation * position;
    gl_Position = translatedPosition;
}

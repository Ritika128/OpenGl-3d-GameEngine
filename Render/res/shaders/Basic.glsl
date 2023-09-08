
#version 120        
attribute vec4 position;     
void main()
{
 gl_Position = position;
}

#version 120       
void main()
{
 gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}

#shader vertex
#version 330
attribute vec4 position;
varying vec2 texCoord;
void main()
{
    gl_Position = position;
    texCoord = (vec2(gl_Position.x,gl_Position.y));
      
}

#shader fragment
#version 330
in vec2 texCoord;

vec3 checker(in float u, in float v)
{
  float checkSize = 4;
  float fmodResult = mod(floor(checkSize * u) + floor(checkSize * v), 2.0);
  float fin = max(sign(fmodResult), 0.0);
  return vec3(fin, fin, fin);
}
void main(void)
{
  
    vec3 check = checker(texCoord.x, texCoord.y);
    gl_FragColor = vec4(check,1.0);
}
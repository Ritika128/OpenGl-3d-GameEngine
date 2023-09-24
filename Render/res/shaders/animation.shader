#shader vertex
#version 120

attribute vec4 position;
varying vec4 vertexColor;
uniform mat4 transform;

void main()
{
    gl_Position = transform * position;
    vertexColor = vec4(position);
}

#shader fragment
#version 120
varying vec4 vertexColor;

void main()
{
    //face based on the vertex position
    int face = int(vertexColor.x + vertexColor.y + vertexColor.z);

    // color for each face
    vec3 color;
    if (face == 0) // Front
        color = vec3(1.0f, 0.0f, 0.0f); // red
    else if (face == 1) // Back
        color = vec3(1.0f, 1.0f, 0.0f); // yellow
    else if (face == 2) // Left
        color = vec3(0.0f, 1.0f, 0.0f); // green
    else if (face == 3) // Right
        color = vec3(1.0f, 0.75f, 0.8f); // Pink
    else if (face == 4) // Top
        color = vec3(0.0f, 0.0f, 1.0f); // Blue
    else // Bottom
        color = vec3(0.5f, 0.0f, 0.5f); // Purple

    gl_FragColor = vec4(color, 1.0);
}


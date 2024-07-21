#version 460

uniform float xOffset;
uniform float yOffset;

void main()
{
    if(gl_VertexID == 0)
        gl_Position = vec4(0.25 + xOffset, -0.25 + yOffset, 0.0, 1.0);
    else if(gl_VertexID == 1)
        gl_Position = vec4(-0.25 + xOffset, -0.25 + yOffset, 0.0, 1.0);
    else if(gl_VertexID == 2)
        gl_Position = vec4(0.25 + xOffset, 0.25 + yOffset, 0.0, 1.0);
}
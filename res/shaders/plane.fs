#version 330 core

out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D ground;

void main()
{
    FragColor = texture(ground, TexCoord);
}
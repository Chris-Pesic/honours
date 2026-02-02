#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D planetTexture;

void main()
{
    FragColor = texture(planetTexture, TexCoord);
}
#version 330 core

in vec2 f_textureCoordinate;
out vec4 FragColor;

uniform sampler2D texture1;

void main()
{
    FragColor = texture(texture1,f_textureCoordinate);
} 
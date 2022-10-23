#version 330 core
in vec3 ourColor;
in vec2 textureCoord;
uniform sampler2D texturePic;
out vec4 FragColor;
void main()
{
   FragColor =mix(vec4(ourColor,1.0),texture(texturePic,textureCoord),0.2);
}
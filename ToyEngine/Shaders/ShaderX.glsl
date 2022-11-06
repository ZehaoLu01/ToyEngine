
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 textureCoordinate;

out vec2 f_textureCoordinate;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
	f_textureCoordinate = textureCoordinate; 
	gl_Position = projection * view * model * vec4(aPos.x,aPos.y,aPos.z,1.0f);
}
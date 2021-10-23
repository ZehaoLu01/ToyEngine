#pragma once
#include<string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Shader
{
private:
	unsigned int programID=0;

public:
	Shader(const std::string& vertexShaderAddress, const std::string& fragmentShaderAddress);
	void setUniformM4f(const char* name, glm::mat4 mat);
	void useProgram();
};


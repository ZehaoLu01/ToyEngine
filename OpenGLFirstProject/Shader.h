#pragma once
#include<string>



class Shader
{
private:
	unsigned int programID=0;

public:
	Shader(const std::string& vertexShaderAddress, const std::string& fragmentShaderAddress);
	void useProgram();
};


#include "Shader.h"
#include"glad/glad.h"
#include<fstream>
#include<iostream>
#include<sstream>
using namespace std;
Shader::Shader(const std::string& vertexShaderAddress, const std::string& fragmentShaderAddress)
{
	//Read shader files.
	ifstream iV, iF;
	iV.open(vertexShaderAddress);
	iF.open(fragmentShaderAddress);
	if (!iV || !iF) {
		cout << "one of the shaders not loaded correctly!" << endl;
		return;
	}
	stringstream iVS, iFS;
	iVS << iV.rdbuf();
	iFS << iF.rdbuf();

	iV.close();
	iF.close();

	string iVSString = iVS.str();
	string iFSString = iFS.str();
	const char* vSourceCode = iVSString.c_str();
	const char* fSourceCode = iFSString.c_str();

	//Compile vertex shader and fragment shader.
	unsigned int vs, fs;
	int result;
	vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vSourceCode, NULL);
	glCompileShader(vs);
	glGetShaderiv(vs, GL_COMPILE_STATUS, &result);
	if (!result) {
		cout << "VERTEX SHADER COMPILE ERROR!" << endl;
		return;
	}
	fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fSourceCode, NULL);
	glCompileShader(fs);
	glGetShaderiv(fs, GL_COMPILE_STATUS, &result);
	if (!result) {
		cout << "FRAGMENT SHADER COMPILE ERROR!" << endl;
		return;
	}
	
	//Create program that link vertex shader and fragment shader
	programID = glCreateProgram();
	glAttachShader(programID, vs);
	glAttachShader(programID, fs);
	glLinkProgram(programID);
	glGetProgramiv(programID, GL_LINK_STATUS, &result);
	if (!result) {
		cout << "PROGRAM LINK ERROR!" << endl;
		return;
	}
	glDeleteShader(vs);
	glDeleteShader(fs);
}

//Add a 4*4 matrix uniform variable to this shader program.
void Shader::setUniformM4f(const char* name, glm::mat4 mat)
{
	GLint myUniformLocation = glGetUniformLocation(programID, name);
	glUniformMatrix4fv(myUniformLocation, 1,GL_FALSE , glm::value_ptr(mat));
}

//Enable this shader program.
void Shader::useProgram()
{	
	glUseProgram(programID);
}

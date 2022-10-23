#pragma once
#include "glad/glad.h"
class EBO
{
public:
	EBO();

	void bind();
	void unbind();

	// Input data to the EBO.
	void inputData(GLsizeiptr size, const void* data, GLenum usage);
private:

	unsigned int BufferID;
};


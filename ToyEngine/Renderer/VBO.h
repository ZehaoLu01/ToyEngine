#pragma once
#include "glad/glad.h"
class VBO
{
public:
	VBO();
	void bind();
	void unbind();
	void inputData(GLsizeiptr size, const void *data, GLenum usage);
	void linkAttrPtr(GLuint index, GLint size, GLenum type, GLboolean isNormalized, GLsizei stide, void* offset);
private:
	unsigned int BufferID;
};


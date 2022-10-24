#include "VBO.h"
#include<glad/glad.h>
#include <GLFW/glfw3.h>

VBO::VBO()
{
	glGenBuffers(1, &BufferID);
}

void VBO::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, BufferID);
}

void VBO::unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::inputData(GLsizeiptr size, const void* data, GLenum usage)
{
	bind();
	glBufferData(GL_ARRAY_BUFFER, size, data, usage);
	unbind();
}

void VBO::linkAttrPtr(GLuint index, GLint size, GLenum type, GLboolean isNormalized, GLsizei stide, void* offset)
{
	bind();
	glVertexAttribPointer(index, size, type, isNormalized, stide, offset);
	glEnableVertexAttribArray(index);
	unbind();
}

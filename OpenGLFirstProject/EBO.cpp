#include "EBO.h"

EBO::EBO() {
	glGenBuffers(1, &BufferID);
}

void EBO::bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferID);
}

void EBO::unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::inputData(GLsizeiptr size, const void* data, GLenum usage)
{
	bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage);
	// Dont use unbind before unbinding VAO because VAO will record this unbind. If you bind this VAO when you are rendering, EBO will also be unbound. As a result, no EBO will be configured.
}

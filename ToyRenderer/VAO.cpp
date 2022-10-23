#include "VAO.h"

VAO::VAO()
{
	glGenVertexArrays(1, &BufferArrayID);
}

void VAO::bind()
{
	glBindVertexArray(BufferArrayID);
}

void VAO::unbind()
{
	glBindVertexArray(BufferArrayID);
}

#pragma once
#include "glad/glad.h"
class VAO
{
public:
	VAO();
	void bind();
	void unbind();
private:
	unsigned int BufferArrayID;
};


#pragma once
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Shader.h"
class Food
{
public:
	Food();
	Food(unsigned int row, unsigned int col);
	unsigned int row;
	unsigned int col;
	void regenerate();
	void render(Shader shaderProgram, VAO foodVAO);
};


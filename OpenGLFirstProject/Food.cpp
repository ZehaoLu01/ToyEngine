#include "Food.h"
#include<cstdlib>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
extern int MAX_ROW;
extern int MAX_COL;

glm::vec3 rowColConversion(unsigned int row, unsigned int col);

Food::Food() {
	regenerate();
}

Food::Food(unsigned int row, unsigned int col)
{
	this->row = row;
	this->col = col;
}

void Food::regenerate()
{
	row = rand() % MAX_ROW;
	col = rand() % MAX_COL;
}

void Food::render(Shader shaderProgram, VAO foodVAO)
{
	glm::mat4 rotation = glm::mat4(1.0f);
	shaderProgram.setUniformM4f("rotation", rotation);

	glm::vec3 translation = rowColConversion(row, col);
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, translation);

	shaderProgram.setUniformM4f("model", model);
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::rotate(view, glm::radians(70.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 view_t(1);
	view_t = glm::translate(view_t, glm::vec3(0.0f, -5.0f, -15.0f));
	view = view_t * view;
	shaderProgram.setUniformM4f("view", view);
	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.001f, 1000.0f);
	shaderProgram.setUniformM4f("projection", projection);

	foodVAO.bind(); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}


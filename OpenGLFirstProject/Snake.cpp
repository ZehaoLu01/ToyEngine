#include "Snake.h"
#include<algorithm>
#include<iostream>

extern int MAX_ROW;
extern int MAX_COL;

void Snake::popBack()
{
	Node* dNode = tail;
	tail = dNode->prev;
	tail->next = NULL;
	delete dNode;
}

void Snake::pushFront(unsigned int row, unsigned int col)
{
	Node* aNode = new Node(row, col);
	aNode->next = head;
	head->prev = aNode;
	head = aNode;
}

Snake::Snake()
{
	energy = 100;
	curr_dir = DIRECTION::UP;
	head = new Node(0, 0);
	head->next = NULL;
	head->prev = NULL;
	tail = head;
}

bool Snake::checkHeadOutBound()
{
	if (head->row > MAX_ROW - 1 || head->row < 0) {
		return false;
	}
	if (head->col > MAX_COL - 1 || head->col < 0) {
		return false;
	}
	return true;
}

void Snake::move()
{
	switch (curr_dir)
	{
	case Snake::UP:
		pushFront(head->row + 1, head->col);
		break;
	case Snake::LEFT:
		pushFront(head->row, head->col - 1);
		break;
	case Snake::RIGHT:
		pushFront(head->row, head->col + 1);
		break;
	case Snake::DOWN:
		pushFront(head->row - 1, head->col);
		break;
	}

	popBack();
	//check
	bool result = checkHeadOutBound();
	if (!result)return;
}

bool Snake::find(unsigned int row, unsigned col)
{
	for (Node* p= head; p != NULL; p = p->next) {
		if (p->row == row && p->col == col)return true;
	}
	return false;
}

Snake::~Snake()
{
	Node* p = head;
	while (p)
	{
		Node* temp = p;
		p = p->next;
		delete temp;
		temp = NULL;
	}
}

void Snake::checkEating(unsigned int row, unsigned int col)
{
	if (head->row == row && head->col == col) eat();
}

void Snake::changeDirection(DIRECTION direction)
{
	curr_dir = direction;
}

void Snake::render(VAO bodyVAO, Shader shaderProgram)
{
	Node* p = head;
	while (p!=NULL) {
		p->render(bodyVAO, shaderProgram);
		p = p->next;
	}
}
void Snake::eat()
{
	energy += 10;
	switch (curr_dir)
	{
	case Snake::UP:
		pushFront(head->row + 1, head->col);
		break;
	case Snake::LEFT:
		pushFront(head->row, head->col - 1);
		break;
	case Snake::RIGHT:
		pushFront(head->row, head->col + 1);
		break;
	case Snake::DOWN:
		pushFront(head->row - 1, head->col);
		break;
	}
}

	/// <summary>
	/// Convert (row col) to the coordinate of bottom left corner of the square in the world frame.
	/// </summary>
	/// <param name="row"></param>
	/// <param name="col"></param>
	/// <returns></returns>
	glm::vec3 rowColConversion(unsigned int row, unsigned int col)
	{
		if (row > MAX_ROW - 1 || col > MAX_COL - 1)std::cout << "WARNING: row/col is out of bound!";
		//fixed 100 rows and coloums
		float singleRowOffset = -10.5f / (float)(MAX_ROW - 1);
		float singleColOffset = 10.5 / (float)(MAX_COL - 1);
		
		return glm::vec3(-5.5 + (float)col * singleColOffset, 1.0f, -0.5 + (float)row * singleRowOffset);
	}

	Snake::Node::Node(int row, int col)
	{
		this->row = row;
		this->col = col;
		next = NULL;
		prev = NULL;
	}

	void Snake::Node::render(VAO bodyVAO, Shader shaderProgram)
	{
		glm::mat4 rotation = glm::mat4(1.0f);
		//rotation = glm::rotate(rotation, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		shaderProgram.setUniformM4f("rotation", rotation);

		glm::vec3 translation = rowColConversion(this->row, this->col);
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, translation);

		shaderProgram.setUniformM4f("model", model);
		glm::mat4 view = glm::mat4(1.0f);
		view = glm::rotate(view, glm::radians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		glm::mat4 view_t(1);
		view_t = glm::translate(view_t, glm::vec3(0.0f, -5.0f, -15.0f));
		view = view_t * view;
		shaderProgram.setUniformM4f("view", view);
		glm::mat4 projection = glm::mat4(1.0f);
		projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.001f, 1000.0f);
		shaderProgram.setUniformM4f("projection", projection);

		bodyVAO.bind(); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}

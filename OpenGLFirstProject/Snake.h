#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include"VAO.h"
#include<glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "VBO.h"
#include "EBO.h"
#include "VAO.h"
class Snake
{
public:
	enum DIRECTION
	{
		UP = 1,
		LEFT = 2,
		RIGHT = 3,
		DOWN = 4,
	};
private:
	struct Node
	{
		Node(int row, int col);
		// From 0 to maxRow-1.
		unsigned int row;
		// From 0 to maxCol-1
		unsigned int col;
		
		Node* next;
		Node* prev;
		void render(VAO bodyVAO, Shader shaderProgram);
	};
	//Add a node to the head
	void pushFront(unsigned int row, unsigned int col);
	//Delete a node from the tail
	void popBack();
	//Head node of the snake
	Node* head;
	//Tail node of the snake
	Node* tail;
	//If energy=0, the snake will die. It can also be used to change the size of the snake.-1~100
	int energy;

	//The direction the snake will move at the next frame.
	DIRECTION curr_dir;
	//Check if the snake head is out of the game spot.
	bool checkHeadOutBound();
public:
	Snake();
	~Snake();

	//Move the snake according to current direction.
	void move();
	//Check if (row,col) is the position of a specific node in the snake
	bool find(unsigned int row, unsigned col);
	//When the snake eat something, this function will be called.
	void eat();

	void checkEating(unsigned int row, unsigned int col);

	void render(VAO bodyVAO,Shader shaderProgram);

	void changeDirection(DIRECTION direction);
};

glm::vec3 rowColConversion(unsigned int row, unsigned int col);


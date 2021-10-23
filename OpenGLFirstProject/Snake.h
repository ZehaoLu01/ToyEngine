#pragma once
class Snake
{
private:
	struct Node
	{
		// From 0 to maxRow-1.
		unsigned int row;
		// From 0 to maxCol-1
		unsigned int col;
		
		Node* next;
		Node* prev;
		float* render();
	};
	//Add a node to the head
	void pushFront();
	//Delete a node from the tail
	void popBack();
	//Head node of the snake
	Node* head;
	//Tail node of the snake
	Node* tail;
	//If energy=0, the snake will die. It can also be used to change the size of the snake.-1~100
	int Energy;
public:
	//Move the snake to (row,col).
	void move(unsigned int row, unsigned col);
	//Check if (row,col) is the position of a specific node in the snake
	bool find(unsigned int row, unsigned col);
	//When the snake eat something, this function will be called.
	void eat();

};


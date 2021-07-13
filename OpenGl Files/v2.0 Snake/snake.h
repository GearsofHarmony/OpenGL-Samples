#pragma once
#ifndef SNAKE_H
#define SNAKE_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "shape.h"

struct Node
{
	unsigned short key = 0;
	Node* left = NULL;
	Shape* data = NULL;
	Node* right = NULL;
};

Node* search(Node* node, unsigned short key, bool flag = true);
void insert(Node* node, unsigned short key, unsigned short count = 1);

class Snake
{
private:
	Shape* head;
	Node* body;
	Shape* tail;
	unsigned short KEY;
	bool player1;
	float xPos;
	float yPos;
	float theta;
public:
	Snake();
	~Snake();

	void setPlayer1(bool val) { player1 = val; }

	Node* getBody(unsigned short key) { return search(body,key); }
	Shape* getHead() { return head; }
	Shape* getTail() { return tail; }
	unsigned short getKey() { return KEY; }

	void startPosition(float xVal, float yVal, float degVal = 0.0f) { xPos = xVal; yPos = yVal; theta = degVal; }

	void initialize(int nWidth, int nHeight);
	void update(float);
	void processInput(GLFWwindow*, float);
	bool collision(Shape* ptr);
	void grow();
	void reset(int nWidth, int nHeight);
	void draw(Shape* ptr);
};

#endif
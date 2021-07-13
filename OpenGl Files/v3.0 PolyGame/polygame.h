#pragma once
#ifndef POLYGAME_H
#define POLYGAME_H

#include<list>
#include "game.h"
#include "shape.h"
using namespace std;

struct Node
{
	unsigned short key = 0;
	Node* left = NULL;
	Shape* data = NULL;
	Node* right = NULL;
};

Node* search(Node* node, unsigned short key, bool flag = true);
void insert(Node* node, unsigned short key, unsigned short count = 1);

class Point {
private:
	float xPos;
	float yPos;
public:
	Point(float x, float y) { xPos = x; yPos = y; }
	float getXPos() { return xPos; }
	float getYPos() { return yPos; }
	void setXPos(float x) { xPos = x; }
	void setYPos(float y) { yPos = y; }
};

class PolyGame : public Game
{
private:
	Shape* polygon;
	Node* node;
	unsigned short KEY;
	float* center;
	bool completed;
	list<Point> poly;
public:
	PolyGame();
	virtual ~PolyGame();
	void processInput(GLFWwindow*);
	void initialize(GLFWwindow*);
	void update();
	void collision();
	void render();
	virtual void reset();

	// CustomPoly Functions
	bool isFirstPoint(float xPos, float yPos);
	void scalePoly(float scale_x, float scale_y);
	void transPoly(float transX, float transY);
	//void getCenter(float xPos, float yPos);
	//void rotatePoly(float angle);
	bool isCompleted() { return completed; }
	//list<Point> getPoints() { return points; }
	void setCompleted(bool c) { completed = c; }
	//int numPoints() { return points.size(); }
};
#endif
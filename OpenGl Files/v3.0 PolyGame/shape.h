#pragma once
#ifndef SHAPE_H
#define SHAPE_H

#include "glad/glad.h"
#include "math.h"

class Shape
{
private:
	Vector2 pos;
	Vector2 vel;
	Vector2 rad;
	Vector2* vertex;
	float angle;
	int numVertices;
	unsigned int VAO, VBO;
	int Width, Height;
public:
	Shape();
	~Shape();

	Vector2 getPos() { return pos; }
	Vector2 getVel() { return vel; }
	Vector2 getRad() { return rad; }
	Vector2* getVertex() { return vertex; }
	float getAngle() { return angle; }
	int getNumVertices() { return numVertices; }
	unsigned int getVAO() { return VAO; };
	int getWidthRatio() { return Width; }
	int getHeightRatio() { return Height; }

	void setPos(float inX, float inY) { pos.Set(inX, inY); }
	void setVel(float inX, float inY) { vel.Set(inX, inY); }
	void setRad(float inX, float inY) { rad.Set(inX, inY); }
	void setAngle(float inAngle) { angle = inAngle; }
	void setNumVertices(int inVertex) { numVertices = inVertex; }
	void setRatio(int nWidth, int nHeight) { Width = nWidth; Height = nHeight; };

	void editVertices();
	void draw();
};
#endif 

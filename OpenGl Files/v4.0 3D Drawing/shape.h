#pragma once
#ifndef SHAPE_H
#define SHAPE_H

#include "glad/glad.h"
#include "math.h"
#include <stb-master/stb_image.h>

class Shape
{
private:
	struct Data
	{
		Vec3 vertex;
		Vec2 texCoord;
		Vec3 normal;
		//Vec3 RGB;
	} *data;
	Vec3 pos;
	Vec3 vel;
	Vec3 rad;
	float angle;
	int numVertices;
	int indiceSize;
	unsigned int VAO, VBO, EBO;
	unsigned int* indices;
public:
	Shape(int numVert, int numIndices);
	~Shape();

	Vec3 getPos() { return pos; };
	Vec3 getVel() { return vel; };
	Vec3 getRad() { return rad; };
	Data* getData() { return data; };
	float getAngle() { return angle; };
	int getNumVertices() { return numVertices; };
	unsigned int getVAO() { return VAO; };
	unsigned int getVBO() { return VBO; };
	unsigned int getEBO() { return EBO; };
	unsigned int* getIndices() { return indices; };

	void setPos(float inX, float inY, float inZ) { pos.Set(inX, inY, inZ); };
	void setVel(float inX, float inY, float inZ) { vel.Set(inX, inY, inZ); };
	void setRad(float inX, float inY, float inZ) { rad.Set(inX, inY, inZ); };
	void setAngle(float inAngle) { angle = inAngle; };
	void setNumVertices(int inVertex) { numVertices = inVertex; };

	// Calculates vertices of objects from a triangle to a circle in 2D
	// numVertices is self explanatory
	// type has two options:
	// 1) 2D
	// 2) 3D
	// Type 2 simply adds a different z value for all vertexs thus making a 3D option, 
	// theoretically can make a sphere but I have not tested it yet
	void editVertices(const int numVertices, const int type, const float OFFSET);
	void createCube(float xRad, float yRad, float zRad);
	void draw(); // may become irrelevant in the future but is here to stay in the meantime
};

// Load textures will implement class in future
// It is a personal preference that all images used are in RGBA format
unsigned int loadTexture(const char* file); 
#endif 

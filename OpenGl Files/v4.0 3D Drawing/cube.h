#pragma once
#ifndef CUBE_H
#define CUBE_H
#include "shape.h"

class Cube
{
private:
	Shape* thing;
	unsigned int thingTex;
public:
	Cube() { this->initialize(); };
	~Cube() { SAFE_DELETE(thing); };
	void initialize();
	void update(float frameTime);
	void render();
};

class Light
{
public:
	Shape* light;
	Light() { this->initialize(); };
	~Light() { SAFE_DELETE(light); };
	void initialize()
	{
		light = new Shape(24, 36);
		light->createCube(2.0f, 2.0f, 2.0f);
	};
	void update(float frameTime) {};
	void render()
	{

	};
};
#endif
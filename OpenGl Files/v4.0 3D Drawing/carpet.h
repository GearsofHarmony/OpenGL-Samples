#pragma once
#ifndef CARPET_H
#define CARPET_H
#include "shape.h"

class Carpet
{
private:
	Shape* thing;
	unsigned int thingTex;
public:
	Carpet() { this->initialize(); };
	~Carpet() { SAFE_DELETE(thing); };
	void initialize();
	void update(float frameTime);
	void render();
};
#endif
#pragma once
#ifndef ROOM_H
#define ROOM_H
#include "shape.h"

class Room
{
private:
	Shape* thing;
	unsigned int flatTex, wallTex;
public:
	Room() { this->initialize(); };
	~Room() { SAFE_DELETE(thing); };
	void initialize();
	void update(float frameTime);
	void render();
};
#endif
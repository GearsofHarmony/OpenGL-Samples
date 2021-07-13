#pragma once
#ifndef BOOKSHELF_H
#define BOOKSHELF_H
#include "shape.h"

class BookShelf
{
private:
	Shape* thing;
	unsigned int thingTex;
public:
	BookShelf() { this->initialize(); };
	~BookShelf() { SAFE_DELETE(thing); };
	void initialize();
	void update(float frameTime);
	void render();
};
#endif
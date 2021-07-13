#pragma once
#ifndef MAINGAME_H
#define MAINGAME_H

//#include <fstream>
#include "coreGame.h"
#include "shape.h"
#include "camera.h"
#include "cube.h"
#include "room.h"
#include "bookshelf.h"
#include "carpet.h"
using namespace std;

class MainGame : public CoreGame
{
private:
	//ofstream fout;	// debug file
	Cube* cube;
	Room* room;
	BookShelf* bookShelf;
	Carpet* carpet;
	//Shape* table;
	Camera camera;
	unsigned int bookShelfTex,carpetTex;
public:
	MainGame();
	virtual ~MainGame();
	void processInput(GLFWwindow*);
	void initialize(GLFWwindow*) ;
	void update();
	void collision();
	void render();
	virtual void reset();
};
#endif
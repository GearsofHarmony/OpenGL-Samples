#pragma once
#ifndef SNAKEGAME_H
#define SNAKEGAME_H

#include "game.h"
#include "snake.h"
#include <stdlib.h>

class SnakeGame : public Game
{
private:
	Snake* player1;
	Snake* player2;
	Shape* food;
	Shape* wall;
	bool gameover1;
	bool gameover2;
public:
	SnakeGame();
	virtual ~SnakeGame();
	void processInput(GLFWwindow*);
	void initialize(GLFWwindow*);
	void update();
	void collision();
	void render();
	virtual void reset();
};
#endif
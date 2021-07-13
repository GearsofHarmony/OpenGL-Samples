#pragma once
#ifndef GAME_H
#define GAME_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "shader.h"
#include "constants.h"

class Game
{
private:
	float timeStart;
	float timeEnd;
	bool pause;
	bool gameover;
protected:
	Shader* ourShader;
	float frameTime;
	float timer;
	int newWidth;
	int newHeight;
	int oldWidth;
	int oldHeight;
public:
	Game();
	~Game();

	void setGameOver() { gameover = true; }

	void run(GLFWwindow*);

	virtual void processInput(GLFWwindow*);
	virtual void renderGame(GLFWwindow*);
	virtual void initialize(GLFWwindow*);
	virtual void deleteAll();
	virtual void reset();

	virtual void update() = 0;
	virtual void collision() = 0;
	virtual void render() = 0;
};
#endif 

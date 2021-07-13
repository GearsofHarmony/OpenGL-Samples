#pragma once
#ifndef COREGAME_H
#define COREGAME_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "shader.h"
#include "constants.h"

class CoreGame
{
private:
	float timeStart;
	float timeEnd;
	bool pause;
	//bool gameover;
protected:
	Shader* ourShader;
	//Shader* lampShader;
	float frameTime;
	float timer;
	int newWidth;
	int newHeight;
	int oldWidth;
	int oldHeight;
public:
	CoreGame();
	~CoreGame();

	//void setGameOver() { gameover = true; }

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

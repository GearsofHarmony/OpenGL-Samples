#include "coreGame.h"

CoreGame::CoreGame()
{
	oldWidth = WIDTH;
	oldHeight = HEIGHT;
};
CoreGame::~CoreGame()
{
	deleteAll();
};
void CoreGame::initialize(GLFWwindow*)
{
	pause = false;
	//gameover = false;
	timeStart = glfwGetTime();
	// load files from GLSL Scripts
	// GLSL has been a bigger blessing than I anticipated at first 
	// especially when it came to the perspective and view matrix transformations
	// just send some of the important stuff into the gpu share the work for the cpu!
	// Note these files can be read like a normal txt file!
	ourShader = new Shader("cust.shader.vs.txt", "cust.shader.fs.txt");
	//lampShader = new Shader("cust.shader.vs", "lamp.shader.fs");
}
// Main game input
void CoreGame::processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS && timer >= 1.0f/* && gameover == false*/)
	{
		timer = 0.0f;
		if (pause == false)
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			pause = true;
		}
		else
		{
			glfwSetCursorPos(window, (float)oldWidth / 2.0f, (float)oldHeight / 2.0f);
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			pause = false;
		}
	}
};
// main game loop
void CoreGame::run(GLFWwindow* window)
{
	// Check if window size changes. 
	// If there is a difference and it is a not zero then reset old width and height;
	// Also reset any values that depend on the width and height such as the perspective matrix
	glfwGetFramebufferSize(window, &newWidth, &newHeight);

	if (oldWidth != newWidth || oldHeight != newHeight)
	{
		if (newWidth != 0 && newHeight != 0)
		{
			reset();
		}
		// pause after window resize
		pause = true;
	}

	timeEnd = (float)glfwGetTime();
	frameTime = timeEnd - timeStart;
	timeStart = timeEnd;
	if (frameTime > 0.01f)
		frameTime = 0.01f;
	if (frameTime < 0.001f)
		frameTime = 0.001f;
	timer += frameTime;
	//std::cout << frameTime << '\n';

	//if (gameover == true)
	//	pause = true;

	CoreGame::processInput(window);

	if (pause == false)
	{
		processInput(window);
		update();
		collision();
	}
	renderGame(window);
};
void CoreGame::renderGame(GLFWwindow* window)
{
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glClearColor(0.1f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	render();

	glfwSwapBuffers(window);
	glfwPollEvents();
};
void CoreGame::deleteAll()
{
	SAFE_DELETE(ourShader);
};
void CoreGame::reset()
{

};
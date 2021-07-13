#include "game.h"

Game::Game()
{
	oldWidth = WIDTH;
	oldHeight = HEIGHT;
};
Game::~Game()
{
	deleteAll();
};
void Game::initialize(GLFWwindow*)
{
	pause = true;
	gameover = false;
	timeStart = glfwGetTime();
	ourShader = new Shader("3.3.shader.vs", "3.3.shader.fs");
}
// Main game input
void Game::processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS && timer >= 1.0f && gameover == false)
	{
		timer = 0.0f;
		if (pause == false)
		{
			pause = true;
		}
		else
		{
			pause = false;
		}
	}
};
// main game loop
void Game::run(GLFWwindow* window)
{
	glfwGetFramebufferSize(window, &newWidth, &newHeight);

	if (oldWidth != newWidth || oldHeight != newHeight)
	{
		if (newWidth != 0 && newHeight != 0)
		{
			reset();
		}
		pause = true;
	}

	timeEnd = (float)glfwGetTime();
	frameTime = timeEnd - timeStart;
	timeStart = timeEnd;
	if (frameTime > 0.02f)
		frameTime = 0.02f;
	if (frameTime < 0.001f)
		frameTime = 0.001f;
	timer += frameTime;
	//std::cout << frameTime << '\n';

	if (gameover == true)
		pause = true;

	Game::processInput(window);

	if (pause == false)
	{
		processInput(window);
		update();
		collision();
	}
	renderGame(window);

	glfwPollEvents();
};
void Game::renderGame(GLFWwindow* window)
{
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	ourShader->use();

	render();

	glfwSwapBuffers(window);
};
void Game::deleteAll()
{
	delete ourShader;
};
void Game::reset()
{

};
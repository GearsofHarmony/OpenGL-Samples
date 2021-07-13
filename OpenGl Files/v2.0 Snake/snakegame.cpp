#include "snakegame.h"

SnakeGame::SnakeGame()
{
	srand(glfwGetTime());
}
SnakeGame::~SnakeGame()
{
	delete food;
}
void SnakeGame::processInput(GLFWwindow* window)
{
	player1->processInput(window, frameTime);
	player2->processInput(window, frameTime);
};
void SnakeGame::initialize(GLFWwindow* window)
{
	Game::initialize(window);

	player1 = new Snake;
	player2 = new Snake;
	food = new Shape;
	wall = new Shape[4];

	player1->setPlayer1(true);
	player1->startPosition(-0.4f, 0.0f);
	player1->initialize(oldWidth, oldHeight);
	player2->startPosition(0.4f, 0.0f, PI);
	player2->initialize(oldWidth, oldHeight);

	food->setNumVertices(5);
	food->setPos(0, 0);
	food->setRatio(oldWidth, oldHeight);
	food->editVertices();
	for (int vv = 0; vv < food->getNumVertices(); vv++)
	{
		food->getVertex()[vv] = Vector2::Transform(food->getVertex()[vv],
			Matrix3::createScale(1.0f / (float)food->getWidthRatio(), 1.0f / (float)food->getHeightRatio()));
	}
	food->draw();

	for (int ii = 0; ii < 4; ii++)
	{
		wall[ii].setNumVertices(2);
		wall[ii].setRatio(oldWidth, oldHeight);
		switch (ii)
		{
		case 0:
			wall[ii].setRad((float)wall[ii].getWidthRatio(), 0.0f);
			wall[ii].setPos(0.0f, 1.0f);
			break;
		case 1:
			wall[ii].setRad(0.0f, (float)wall[ii].getHeightRatio());
			wall[ii].setPos(-1.0f, 0.0f);
			break;
		case 2:
			wall[ii].setRad((float)wall[ii].getWidthRatio(), 0.0f);
			wall[ii].setPos(0.0f, -1.0f);
			break;
		case 3:
			wall[ii].setRad(0.0f, (float)wall[ii].getHeightRatio());
			wall[ii].setPos(1.0f, 0.0f);
			break;
		default:
			break;
		}
		wall[ii].editVertices(); 
		for (int vv = 0; vv < wall[ii].getNumVertices(); vv++)
		{
			wall[ii].getVertex()[vv] = Vector2::Transform(wall[ii].getVertex()[vv],
				Matrix3::createScale(1.0f / (float)wall[ii].getWidthRatio(), 1.0f / (float)wall[ii].getHeightRatio()));
		}
		wall[ii].draw();
	}
}
void SnakeGame::update()
{
	player1->update(frameTime);
	player2->update(frameTime);
};
void SnakeGame::collision()
{
	int randVal = rand() % int((2.0f * PI));
	bool player1Flag = false;
	bool player2Flag = false;

	if (player1->collision(food) == true)
	{
		player1Flag = true;
	}
	if (player2->collision(food) == true)
	{
		player2Flag = true;
	}

	if (player1->collision(&wall[0]) == true)
	{
		player1->getHead()->setPos(player1->getHead()->getPos().x, wall[0].getPos().y - (player1->getHead()->getRad().y / player1->getHead()->getHeightRatio()));
		player1->getHead()->setAngle(player1->getHead()->getAngle() - (float)randVal);
	}
	else if (player1->collision(&wall[1]) == true)
	{
		player1->getHead()->setPos(wall[1].getPos().x + (player1->getHead()->getRad().x / player1->getHead()->getWidthRatio()), player1->getHead()->getPos().y);
		player1->getHead()->setAngle(player1->getHead()->getAngle() - (float)randVal);
	}
	else if (player1->collision(&wall[2]) == true)
	{
		player1->getHead()->setPos(player1->getHead()->getPos().x, wall[2].getPos().y + (player1->getHead()->getRad().y / player1->getHead()->getHeightRatio()));
		player1->getHead()->setAngle(player1->getHead()->getAngle() - (float)randVal);
	}
	else if (player1->collision(&wall[3]) == true)
	{
		player1->getHead()->setPos(wall[3].getPos().x - (player1->getHead()->getRad().x / player1->getHead()->getWidthRatio()), player1->getHead()->getPos().y);
		player1->getHead()->setAngle(player1->getHead()->getAngle() - (float)randVal);
	}

	if (player2->collision(&wall[0]) == true)
	{
		player2->getHead()->setPos(player2->getHead()->getPos().x, wall[0].getPos().y - (player2->getHead()->getRad().y / player2->getHead()->getHeightRatio()));
		player2->getHead()->setAngle(player2->getHead()->getAngle() - (float)randVal);
	}
	else if (player2->collision(&wall[1]) == true)
	{
		player2->getHead()->setPos(wall[1].getPos().x + (player2->getHead()->getRad().x / player2->getHead()->getWidthRatio()), player2->getHead()->getPos().y);
		player2->getHead()->setAngle(player2->getHead()->getAngle() - (float)randVal);
	}
	else if (player2->collision(&wall[2]) == true)
	{
		player2->getHead()->setPos(player2->getHead()->getPos().x, wall[2].getPos().y + (player2->getHead()->getRad().y / player2->getHead()->getHeightRatio()));
		player2->getHead()->setAngle(player2->getHead()->getAngle() - (float)randVal);
	}
	else if (player2->collision(&wall[3]) == true)
	{
		player2->getHead()->setPos(wall[3].getPos().x - (player2->getHead()->getRad().x / player2->getHead()->getWidthRatio()), player2->getHead()->getPos().y);
		player2->getHead()->setAngle(player2->getHead()->getAngle() - (float)randVal);
	}

	for (int ii = 15; ii < player2->getKey()-10; ii++)
	{
		if (player1->collision(player2->getBody(ii)->data) == true)
		{
			gameover1 = true;
			setGameOver();
		}
	}
	for (int ii = 15; ii < player1->getKey()-10; ii++)
	{
		if (player2->collision(player1->getBody(ii)->data) == true)
		{
			gameover2 = true;
			setGameOver();
		}
	}

	// if any snake collide with food relocate within window
	if (player1Flag == true || player2Flag == true)
	{
		do
		{
			food->setPos(cosf(rand() % oldWidth), sinf(rand() % oldHeight));
		} while (food->getPos().x + food->getRad().x / oldWidth >= 1.0f
			|| food->getPos().x - food->getRad().x / oldWidth <= -1.0f
			|| food->getPos().y + food->getRad().y / oldHeight >= 1.0f
			|| food->getPos().y - food->getRad().y / oldHeight <= -1.0f);
		food->editVertices();
		for (int vv = 0; vv < food->getNumVertices(); vv++)
		{
			food->getVertex()[vv] = Vector2::Transform(food->getVertex()[vv],
				Matrix3::createScale(1.0f / (float)food->getWidthRatio(), 1.0f / (float)food->getHeightRatio()));
		}
		food->draw();
	}
	if (player1Flag == true)
	{
		player1->grow();
	}
	if (player2Flag == true)
	{
		player2->grow();
	}
};
void SnakeGame::render()
{
	for (int ii = 2; ii <= player1->getKey(); ii++)
	{
		ourShader->setVec4("ourColor", 0.0f, 0.2f, 0.8f, 1.0f);
		if (gameover1 == true)
			ourShader->setVec4("ourColor", 1.0f, 0.0f, 0.0f, 1.0f);
		glBindVertexArray(player1->getBody(ii)->data->getVAO());
		glDrawArrays(GL_TRIANGLE_FAN, 0, player1->getBody(ii)->data->getNumVertices());
	}
	for (int ii = 2; ii <= player2->getKey(); ii++)
	{
		ourShader->setVec4("ourColor", 0.0f, 0.2f, 0.8f, 1.0f);
		if (gameover2 == true)
			ourShader->setVec4("ourColor", 1.0f, 0.0f, 0.0f, 1.0f);
		glBindVertexArray(player2->getBody(ii)->data->getVAO());
		glDrawArrays(GL_TRIANGLE_FAN, 0, player2->getBody(ii)->data->getNumVertices());
	}

	for (int ii = 0; ii < 3; ii++)
	{
		ourShader->setVec4("ourColor", 0.8f, 1.0f, 0.0f, 1.0f);
		if (gameover1 == true)
			ourShader->setVec4("ourColor", 1.0f, 0.0f, 0.0f, 1.0f);
		glBindVertexArray(player1->getTail()[ii].getVAO());
		glDrawArrays(GL_TRIANGLE_FAN, 0, player1->getTail()[ii].getNumVertices());
	}
	for (int ii = 0; ii < 3; ii++)
	{
		ourShader->setVec4("ourColor", 1.0f, 0.2f, 0.8f, 1.0f);
		if (gameover2 == true)
			ourShader->setVec4("ourColor", 1.0f, 0.0f, 0.0f, 1.0f);
		glBindVertexArray(player2->getTail()[ii].getVAO());
		glDrawArrays(GL_TRIANGLE_FAN, 0, player2->getTail()[ii].getNumVertices());
	}

	ourShader->setVec4("ourColor", 1.0f, 0.2f, 0.8f, 1.0f);
	if (gameover1 == true)
		ourShader->setVec4("ourColor", 1.0f, 0.0f, 0.0f, 1.0f);
	glBindVertexArray(player1->getHead()->getVAO());
	glDrawArrays(GL_TRIANGLE_FAN, 0, player1->getHead()->getNumVertices());
	ourShader->setVec4("ourColor", 0.8f, 1.0f, 0.0f, 1.0f);
	if (gameover2 == true)
		ourShader->setVec4("ourColor", 1.0f, 0.0f, 0.0f, 1.0f);
	glBindVertexArray(player2->getHead()->getVAO());
	glDrawArrays(GL_TRIANGLE_FAN, 0, player2->getHead()->getNumVertices());

	ourShader->setVec4("ourColor", 1.0f, 0.8f, 0.1f, 1.0f);
	glBindVertexArray(food->getVAO());
	glDrawArrays(GL_TRIANGLE_FAN, 0, food->getNumVertices());
};
void SnakeGame::reset()
{
	Vector2 newVel;

	newVel = Vector2::Transform(player1->getHead()->getVel(), Matrix3::createScale((float)oldWidth / (float)newWidth, (float)oldHeight / (float)newHeight));
	player1->getHead()->setVel(newVel.x, newVel.y);


	newVel = Vector2::Transform(player2->getHead()->getVel(), Matrix3::createScale((float)oldWidth / (float)newWidth, (float)oldHeight / (float)newHeight));
	player2->getHead()->setVel(newVel.x, newVel.y);

	oldWidth = newWidth;
	oldHeight = newHeight;

	player1->reset(oldWidth, oldHeight);
	player2->reset(oldWidth, oldHeight);

	food->setRatio(oldWidth, oldHeight);
	food->editVertices();
	for (int vv = 0; vv < food->getNumVertices(); vv++)
	{
		food->getVertex()[vv] = Vector2::Transform(food->getVertex()[vv],
			Matrix3::createScale(1.0f / (float)food->getWidthRatio(), 1.0f / (float)food->getHeightRatio()));
	}

	food->draw(); 
	for (int ii = 0; ii < 4; ii++)
	{
		wall[ii].setRatio(oldWidth, oldHeight);
		switch (ii)
		{
		case 0:
			wall[ii].setRad((float)wall[ii].getWidthRatio(), 0.0f);
			wall[ii].setPos(0.0f, 1.0f);
			break;
		case 1:
			wall[ii].setRad(0.0f, (float)wall[ii].getHeightRatio());
			wall[ii].setPos(-1.0f, 0.0f);
			break;
		case 2:
			wall[ii].setRad((float)wall[ii].getWidthRatio(), 0.0f);
			wall[ii].setPos(0.0f, -1.0f);
			break;
		case 3:
			wall[ii].setRad(0.0f, (float)wall[ii].getHeightRatio());
			wall[ii].setPos(1.0f, 0.0f);
			break;
		default:
			break;
		}
		wall[ii].editVertices();
		wall[ii].draw();
	}
};
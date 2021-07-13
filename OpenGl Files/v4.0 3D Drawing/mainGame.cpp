#include "mainGame.h"

MainGame::MainGame()
{
};
MainGame::~MainGame()
{
	SAFE_DELETE(cube);
	SAFE_DELETE(bookShelf);
	SAFE_DELETE(room);
	SAFE_DELETE(carpet);
}
void MainGame::processInput(GLFWwindow* window)
{
	int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
	camera.processInput(window, frameTime);
	if (timer >= 1.5f)
	{
		if (state == GLFW_PRESS)
		{
			timer = 0.0f;
		}
	}
};
void MainGame::initialize(GLFWwindow* window)
{
	CoreGame::initialize(window);

	int index = 0;

	// Create objects
	room = new Room(); //The room
	bookShelf = new BookShelf(); //The bookshelf
	carpet = new Carpet(); // The fancy rug
	cube = new Cube();	//The crate

	ourShader->use();
	ourShader->setMat4("projection", Mat4::createPerspectiveFOV(PI / 4.0f, (float)oldWidth / oldHeight, 1.0f, 1024.0f));

	ourShader->setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
	ourShader->setVec3("dirLight.light.ambient", 1.0f, 1.0f, 1.0f);
	ourShader->setVec3("dirLight.light.diffuse", 1.0f, 1.0f, 1.0f);
	ourShader->setVec3("dirLight.light.specular", 0.0f, 0.0f, 0.0f);

	ourShader->setFloat("pointLight.constant", 1.0f);
	ourShader->setFloat("pointLight.linear", 0.22f);
	ourShader->setFloat("pointLight.quadratic", 0.2f);
	ourShader->setVec3("pointLight.light.ambient", 0.0f, 0.0f, 0.0f);
	ourShader->setVec3("pointLight.light.diffuse", 0.0f, 0.0f, 0.0f);
	ourShader->setVec3("pointLight.light.specular", 0.0f, 0.0f, 0.0f);
	ourShader->setVec3("pointLight.position", 0.0f, 16.0f, 128.0f);

	ourShader->setFloat("spotLight.cutOff", cosf(5.0f * PI / 180.0f));
	ourShader->setFloat("spotLight.outerCutOff", cosf(15.0f * PI / 180.0f));
	ourShader->setFloat("spotLight.constant", 1.0f);
	ourShader->setFloat("spotLight.linear", 0.07f);
	ourShader->setFloat("spotLight.quadratic", 0.017f);
	ourShader->setVec3("spotLight.light.ambient", 0.0f, 0.0f, 0.0f);
	ourShader->setVec3("spotLight.light.diffuse", 1.0f, 1.0f, 1.0f);
	ourShader->setVec3("spotLight.light.specular", 1.0f, 1.0f, 1.0f);

	// Index textures for openGL
	ourShader->setInt("material.diffuse", 0);
	ourShader->setVec3("material.specular", 0.0f, 0.0f, 0.0f);
	ourShader->setFloat("material.shininess", 32.0f);
};

void MainGame::update()
{
	ourShader->setVec3("spotLight.position", camera.getEyePos());
	ourShader->setVec3("spotLight.direction", camera.getFrontPos());
	ourShader->setMat4("view", camera.getView());
	ourShader->setVec3("viewPos", camera.getEyePos());
	//cube->update(frameTime, camera.getView(), Mat4::createPerspectiveFOV(PI / 4.0f, (float)oldWidth / oldHeight, 0.1f, 128.0f));
	//room->update(frameTime, camera.getView(), Mat4::createPerspectiveFOV(PI / 4.0f, (float)oldWidth / oldHeight, 0.1f, 128.0f));
};
void MainGame::collision()
{
};
void MainGame::render()
{
	//ourShader->setInt("material.diffuse", 3);
	bookShelf->render();
	//ourShader->setInt("material.diffuse", 0);
	room->render();
	cube->render();
	carpet->render();
};
void MainGame::reset()
{
	oldWidth = newWidth;
	oldHeight = newHeight;
	ourShader->setMat4("projection", Mat4::createPerspectiveFOV(PI / 4.0f, (float)oldWidth / oldHeight, 0.1f, 1024.0f));
};
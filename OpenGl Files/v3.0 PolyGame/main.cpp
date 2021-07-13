#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "polygame.h"
#include "constants.h"
using namespace std;

//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

void framebuffer_size_callback(GLFWwindow*, int, int);

int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_SCALE_TO_MONITOR, GL_TRUE);
	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Joshua Renfro: OpenGL: Snake Game", NULL, NULL);
	if (window == NULL)
	{
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetWindowPos(window, 100, 100);
	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initialize GLAD" << endl;
		return -1;
	}

	PolyGame* game = new PolyGame;
	game->initialize(window);
	while (!glfwWindowShouldClose(window))
	{
		game->run(window);
	}
	delete game;
	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

// dead code
//// build and compile our shader program
//// ------------------------------------
//Shader ourShader("3.3.shaderOld.vs", "3.3.shaderOld.fs");
//// set up vertex data (and buffer(s)) and configure vertex attributes
//// ------------------------------------------------------------------
//const int numObjects = 14;
//Shape *polygon = new Shape[numObjects];
////float vertices[720]; //Largest array for Circle and smaller; consists of (x,y) coordinate variables for 360 points
//unsigned int VBO[numObjects], //Vertex Buffer Object; Holds data for vertex primatives
//			 VAO[numObjects]; //Vertex Array Object; Must call and link VBO before OpenGL draws anything
//glGenVertexArrays(numObjects, VAO); //Tell OpenGL how many VAOs there are, VAO is a pointer
//glGenBuffers(numObjects, VBO); //Tell OpenGL how many VBOs there are, VBO is a pointer
//// Create polygons!
//// Set origin for each polygon in R[-1,1]
//for (int ii = 0, numVertices = 3; ii < numObjects; ii++, numVertices++)
//{
//	if (ii == 7)
//		numVertices = 3;
//
//	switch (numVertices)
//	{
//	case 3: // Triangle
//		polygon[ii].setPos(-0.8f, 0.7f);
//		polygon[ii].setNumVertices(numVertices);
//		break;
//	case 4: // Square
//		polygon[ii].setPos(-0.3f,0.7f);
//		polygon[ii].setNumVertices(numVertices);
//		break;
//	case 5: // Pentagon
//		polygon[ii].setPos(0.2f,0.7f);
//		polygon[ii].setNumVertices(numVertices);
//		break;
//	case 6: // Hexagon
//		polygon[ii].setPos(0.7f,0.7f);
//		polygon[ii].setNumVertices(numVertices);
//		break;
//	case 7: // Heptagon
//		polygon[ii].setPos(-0.7f,-0.2f);
//		polygon[ii].setNumVertices(numVertices);
//		break;
//	case 8: // Octagon
//		polygon[ii].setPos(0.0f,-0.2f);
//		polygon[ii].setNumVertices(numVertices);
//		break;
//	default: // Circle
//		polygon[ii].setPos(0.7f,-0.2f);
//		polygon[ii].setNumVertices(360);
//		break;
//	}
//	// Place outline drawn polygons below their filled versions
//	if (ii > 6)
//	{
//		polygon[ii].setPos(polygon[ii].getPos().x + 0.0f, polygon[ii].getPos().y - 0.5f);
//	}
//}
////glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
////glUseProgram(shaderProgram);
////int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
//
//float timeStart = (float)glfwGetTime();
//float timeEnd;
//float frameTime;
//int newWidth;
//int newHeight;
//int oldWidth = WIDTH;
//int oldHeight = HEIGHT;
//// main program loop
//while (!glfwWindowShouldClose(window))
//{
//	glfwGetFramebufferSize(window, &newWidth, &newHeight);
//
//	// Set frame rate capped at 60s
//	timeEnd = (float)glfwGetTime();
//	frameTime = (timeEnd - timeStart);
//	//cout << frameTime << endl;
//	if (frameTime > 0.01f)
//		frameTime = 0.01f;
//
//	processInput(window, frameTime, &polygon[0]);
//	
//	// Assign dynamic values for each iteration of loop to polygon(s)
//	polygon[1].setAngle(polygon[1].getAngle() + -0.3f * frameTime);
//	polygon[2].setAngle(polygon[2].getAngle() + frameTime);
//	polygon[2].setX(polygon[2].getX() + polygon[2].getVelX() * frameTime);
//	polygon[2].setY(polygon[2].getY() + polygon[2].getVelY() * frameTime);
//	polygon[3].setX(polygon[3].getX() + polygon[3].getVelX() * frameTime);
//	polygon[3].setY(polygon[3].getY() + polygon[3].getVelY() * frameTime);
//	polygon[5].setX(0.0f + (polygon[5].getRadX() * (cosf(glfwGetTime()) - sinf(glfwGetTime()))));
//	polygon[5].setY(0.0f + (polygon[5].getRadY() * (sinf(glfwGetTime()) + cosf(glfwGetTime()))));
//	polygon[7].setAngle(polygon[7].getAngle() + 0.8f * frameTime);
//	// Window Border for moving polygons
//	if (polygon[0].getX() + polygon[0].getRadX() > 1.0f)
//		polygon[0].setX(1.0f - polygon[0].getRadX());
//	if (polygon[0].getX() - polygon[0].getRadX() < -1.0f)
//		polygon[0].setX(-1.0f + polygon[0].getRadX());
//	if (polygon[0].getY() + polygon[0].getRadY() > 1.0f)
//		polygon[0].setY(1.0f - polygon[0].getRadY());
//	if (polygon[0].getY() - polygon[0].getRadY() < -1.0f)
//		polygon[0].setY(-1.0f + polygon[0].getRadY());
//	if (polygon[2].getX() + (polygon[2].getRadX()) > 1.0f)
//	{
//		polygon[2].setX(1.0f - (polygon[2].getRadX()));
//		polygon[2].setVelX(polygon[2].getVelX() * -1.0f);
//	}
//	if (polygon[2].getX() - (polygon[2].getRadX()) < -1)
//	{
//		polygon[2].setX(-1.0f + (polygon[2].getRadX()));
//		polygon[2].setVelX(polygon[2].getVelX() * -1);
//	}
//	if (polygon[2].getY() + (polygon[2].getRadY()) > 1)
//	{
//		polygon[2].setY(1.0f - (polygon[2].getRadY()));
//		polygon[2].setVelY(polygon[2].getVelY() * -1);
//	}
//	if (polygon[2].getY() - (polygon[2].getRadY()) < -1)
//	{
//		polygon[2].setY(-1.0f + (polygon[2].getRadY()));
//		polygon[2].setVelY(polygon[2].getVelY() * -1);
//	}
//	if (polygon[3].getX() - (polygon[3].getRadX()) > 1)
//		polygon[3].setX(-1.0f - (polygon[3].getRadX()));
//	if (polygon[3].getX() + (polygon[3].getRadX()) < -1.0f)
//		polygon[3].setX(1.0f + (polygon[3].getRadX()));
//	if (polygon[3].getY() - (polygon[3].getRadY()) > 1)
//		polygon[3].setY(-1.0f - (polygon[3].getRadY()));
//	if (polygon[3].getY() + (polygon[3].getRadY()) < -1)
//		polygon[3].setY(1.0f + (polygon[3].getRadY()));
//	// Edit vertices of each polygon in specific order
//	for (int ii = 0; ii < numObjects; ii++)
//	{
//		editVertices(vertices, &polygon[ii]);
//		rotatePolygon(vertices, &polygon[ii]);
//		scalePolygon(vertices, &polygon[ii], 1.0f / (float)newWidth, 1.0f / (float)newHeight);
//		normalize(&polygon[ii], (float)oldWidth / (float)newWidth, (float)oldHeight / (float)newHeight);
//		drawPolygon(vertices, VAO[ii], VBO[ii], &polygon[ii]);
//	}
//
//	Vector2 newVel = Vector2::Transform(polygon[0].getVel(), Matrix3::createScale((float)oldWidth / (float)newWidth, (float)oldHeight / (float)newHeight));
//	polygon[0].setVel(newVel.x, newVel.y);
//
//	// Draw vertices
//	for (int ii = 0; ii < numObjects; ii++)
//	{
//		editVertices(&polygon[ii]);
//
//		for (int vv = 0; vv < polygon[ii].getNumVertices(); vv++)
//		{
//			polygon[ii].getVertex()[vv] = Vector2::Transform(polygon[ii].getVertex()[vv],
//				Matrix3::createScale((float)1 / (float)oldWidth, (float)1 / (float)oldHeight) * Matrix3::createRotation(polygon[ii].getAngle()));
//		}
//
//		drawPolygon(VAO[ii], VBO[ii], &polygon[ii]);
//	}
//
//	if (newWidth != 0 && newHeight != 0)
//	{
//		oldWidth = newWidth;
//		oldHeight = newHeight;
//	}
//
//	timeStart = timeEnd;
//
//	// Draw polygons and add color
//	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//	glClear(GL_COLOR_BUFFER_BIT);
//	ourShader.use();
//	//ourShader.setVec4("ourColor", 1.0f, 0.2f, 0.8f, 1.0f);
//	for (int ii = 0, numVertices = 3; ii < 14; ii++, numVertices++)
//	{
//		if (ii == 7)
//			numVertices = 3;
//		switch (numVertices)
//		{
//		case 3: // Triangle
//			//ourShader.setFloat("ourColor", 1.0f);
//			ourShader.setVec4("ourColor", 1.0f, 0.2f, 0.8f, 1.0f);
//			//glUniform4f(vertexColorLocation, 1.0f, 0.2f, 0.8f, 1.0f);
//			break;
//		case 4: // Square
//			ourShader.setVec4("ourColor", 0.5f, 0.1f, 1.0f, 1.0f);
//			//glUniform4f(vertexColorLocation, 0.5f, 0.1f, 1.0f, 1.0f);
//			break;
//		case 5: // Pentagon
//			ourShader.setVec4("ourColor", 0.3f, 1.0f, 0.4f, 1.0f);
//			//glUniform4f(vertexColorLocation, 0.3f, 1.0f, 0.4f, 1.0f);
//			break;
//		case 6: // Hexagon
//			ourShader.setVec4("ourColor", 0.0f, 0.4f, 0.6f, 1.0f);
//			//glUniform4f(vertexColorLocation, 0.0f, 0.4f, 0.6f, 1.0f);
//			break;
//		case 7: // Heptagon
//			ourShader.setVec4("ourColor", 0.3f, 0.0f, 0.7f, 1.0f);
//			//glUniform4f(vertexColorLocation, 0.3f, 0.0f, 0.7f, 1.0f);
//			break;
//		case 8: // Octagon
//			ourShader.setVec4("ourColor", 0.9f, 0.2f, 0.0f, 1.0f);
//			//glUniform4f(vertexColorLocation, 0.9f, 0.2f, 0.0f, 1.0f);
//			break;
//		default: // Circle
//			numVertices = 360;
//			ourShader.setVec4("ourColor", 0.0f, 1.0f, 0.0f, 1.0f);
//			//glUniform4f(vertexColorLocation, 0.0f, 1.0f, 0.0f, 1.0f);
//			break;
//		}
//		glBindVertexArray(VAO[ii]);
//		if (ii < 7)
//			glDrawArrays(GL_TRIANGLE_FAN, 0, polygon[ii].getNumVertices());
//		else
//			glDrawArrays(GL_LINE_LOOP, 0, polygon[ii].getNumVertices());
//	}
//	glfwSwapBuffers(window);
//	glfwPollEvents();
//}
//// delete objects before terminating window and exiting program
//// Although OpenGL deletes the VAO and VBO automatically with
//// glfwTerminate it is a good habit to delete them ourselves
//delete[] polygon;
//glDeleteVertexArrays(numObjects, VAO);
//glDeleteBuffers(numObjects, VBO);

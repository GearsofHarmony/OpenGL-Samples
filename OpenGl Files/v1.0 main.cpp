//Version 0.3
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
using namespace std;

//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

// Settings
const int WIDTH = 600;
const int HEIGHT = 600;

// Global Variables
const float PI = 3.1415926f;

// These are shaders necessary for the graphics pipeline
// Vertex Shader -> Shape Assembly -> Geometry Shader -> Rasterization -> Fragment Shader -> Tests and Blending
const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec4 ourColor;\n"
"void main()\n"
"{\n"
"   FragColor = ourColor;\n"
//"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

class Shape
{
private:
	float vecX;
	float vecY;
	float angle;
	float rad;
	float radX;
	float radY;
	float VelX;
	float VelY;
	int numVertices;
public:
	Shape();
	~Shape();

	float getX() { return vecX; }
	float getY() { return vecY; }
	float getAngle() { return angle; }
	float getRad() { return rad; }
	float getRadX() { return radX; }
	float getRadY() { return radY; }
	float getVelX() { return VelX; }
	float getVelY() { return VelY; }
	int getNumVertices() { return numVertices; }

	void setX(float X) { vecX = X; }
	void setY(float Y) { vecY = Y; }
	void setAngle(float A) { angle = A; }
	void setRad(float R) { rad = R; }
	void setRadX(float R) { radX = R; }
	void setRadY(float R) { radY = R; }
	void setVelX(float s) { VelX = s; }
	void setVelY(float s) { VelY = s; }
	void setNumVertices(int v) { numVertices = v; }
};

Shape::Shape() { vecX = 0.0f; vecY = 0.0f; angle = 0.0f, rad = 120.0f, radX = 0.0f; radY = 0.0f, VelX = 0.0f; VelY = 0.0f; numVertices = 3; };
Shape::~Shape() {};

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window, float frameTime, Shape* ptr)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		ptr->setX(ptr->getX() + (ptr->getVelX() * frameTime * cosf(ptr->getAngle())));
		ptr->setY(ptr->getY() + (ptr->getVelY() * frameTime * sinf(ptr->getAngle())));
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		ptr->setX(ptr->getX() - (ptr->getVelX() * frameTime * cosf(ptr->getAngle())));
		ptr->setY(ptr->getY() - (ptr->getVelY() * frameTime * sinf(ptr->getAngle())));
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		ptr->setAngle(ptr->getAngle() + ((2 * PI / 2) * frameTime));
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		ptr->setAngle(ptr->getAngle() - ((2 * PI / 2) * frameTime));
	}
}

void editVertices(float* vertices, Shape* ptr)
{
	const float ANGLE = (2 * PI) / ptr->getNumVertices();

	for (int ii = 0, vv = 0; ii < ptr->getNumVertices(); ii++)
	{
		float newX = ptr->getRad() * cosf(ii * ANGLE), newY = ptr->getRad() * sinf(ii * ANGLE);
		vertices[vv] = newX;
		vertices[vv + 1] = newY;
		vv += 2;
	}
}

void shearPolygon(float* vertices, Shape* ptr, float mh = 0, float mv = 0)
{
	float matrix2D[2][2] = { 1, mh,
							mv, 1 };
}

void scalePolygon(float* vertices, Shape* ptr, float scaleX = 1, float scaleY = 1)
{
	float newX, newY;
	float matrix2D[2][2] = { scaleX, 0, 0, scaleY };

	for (int ii = 0, vv = 0; ii < ptr->getNumVertices(); ii++)
	{
		newX = vertices[vv], newY = vertices[vv + 1];
		vertices[vv] = (newX * matrix2D[0][0]) + (newY * matrix2D[0][1]);
		vertices[vv + 1] = (newX * matrix2D[1][0]) + (newY * matrix2D[1][1]);
		vv += 2;
	}
	newX = ptr->getRad(), newY = ptr->getRad();
	ptr->setRadX((newX* matrix2D[0][0]) + (newY * matrix2D[0][1]));
	ptr->setRadY((newX* matrix2D[1][0]) + (newY * matrix2D[1][1]));
}

/*void normalize(float* vertices, Shape* ptr, float scaleX = 1, float scaleY = 1)
{
	float matrix2D[2][2] = { scaleX, 0, 0, scaleY };
	float newX, newY;

	newX = ptr->getRad(), newY = ptr->getRad();
	ptr->setRadX((newX* matrix2D[0][0]) + (newY * matrix2D[0][1]));
	ptr->setRadY((newX* matrix2D[1][0]) + (newY * matrix2D[1][1]));
}*/

void normalize(Shape* ptr, float scaleX = 1, float scaleY = 1)
{
	float matrix2D[2][2] = { scaleX, 0, 0, scaleY };
	float newX, newY;

	newX = ptr->getVelX(), newY = ptr->getVelY();
	ptr->setVelX((newX * matrix2D[0][0]) + (newY * matrix2D[0][1]));
	ptr->setVelY((newX * matrix2D[1][0]) + (newY * matrix2D[1][1]));
}

void rotatePolygon(float* vertices, Shape* ptr)
{
	float matrix2D[2][2] = { {cosf(ptr->getAngle()), -sinf(ptr->getAngle())},
							 {sinf(ptr->getAngle()), cosf(ptr->getAngle())} };

	for (int ii = 0, vv = 0; ii < ptr->getNumVertices(); ii++)
	{
		float newX = vertices[vv], newY = vertices[vv + 1];
		vertices[vv] = (newX * matrix2D[0][0]) + (newY * matrix2D[0][1]);
		vertices[vv + 1] = (newX * matrix2D[1][0]) + (newY * matrix2D[1][1]);
		vv += 2;
	}
}

void drawPolygon(float* vertices, unsigned int& VAO, unsigned int& VBO, Shape* ptr)
{
	for (int ii = 0, vv = 0; ii < ptr->getNumVertices(); ii++)
	{
		vertices[vv] = ptr->getX() + vertices[vv];
		vertices[vv + 1] = ptr->getY() + vertices[vv + 1];
		vv += 2;
	}
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 2 * ptr->getNumVertices(), vertices, GL_STATIC_DRAW);
}

void createPolygon(float *vertices, unsigned int& VAO, unsigned int& VBO, Shape *ptr)
{
	glBindVertexArray(VAO); //Bind current VAO first before modifying values
	glBindBuffer(GL_ARRAY_BUFFER, VBO); //Bind current VBO to VAO before modifying values
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 2 * ptr->getNumVertices(), vertices, GL_STATIC_DRAW); //Copy vertice array to buffer with memory size in bytes
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0); //Tell OpenGL how to read vertex data in buffer
	glEnableVertexAttribArray(0);
}

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
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Joshua Renfro: OpenGL", NULL, NULL);
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
	// build and compile our shader program
	// ------------------------------------
	// vertex shader
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	// check for shader compile errors
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		cout << "ERROR::SHADER::VERTEX::COMPLICATION_FAILED\n" << infoLog << endl;
	}
	// fragment shader
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	// check for shader compile errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		cout << "ERROR::SHADER::FRAGMENT::COMPLICATION_FAILED\n" << infoLog << endl;
	}
	// link shader
	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	// check for linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		cout << "ERROR::SHADER::PROGRAM::COMPLICATION_FAILED\n" << infoLog << endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	const int numObjects = 14;
	Shape *polygon = new Shape[numObjects];
	float vertices[720]; //Largest array for Circle and smaller; consists of (x,y) coordinate variables for 360 points
	unsigned int VBO[numObjects], //Vertex Buffer Object; Holds data for vertex primatives
				 VAO[numObjects]; //Vertex Array Object; Must call and link VBO before OpenGL draws anything
	glGenVertexArrays(numObjects, VAO); //Tell OpenGL how many VAOs there are, VAO is a pointer
	glGenBuffers(numObjects, VBO); //Tell OpenGL how many VBOs there are, VBO is a pointer
	// Create polygons!
	// Set origin for each polygon in R[-1,1]
	for (int ii = 0, numVertices = 3; ii < numObjects; ii++, numVertices++)
	{
		if (ii == 7)
			numVertices = 3;
		
		switch (numVertices)
		{
		case 3: // Triangle
			polygon[ii].setX(-0.8f);
			polygon[ii].setY(0.7f);
			polygon[ii].setNumVertices(numVertices);
			break;
		case 4: // Square
			polygon[ii].setX(-0.3f);
			polygon[ii].setY(0.7f);
			polygon[ii].setNumVertices(numVertices);
			break;
		case 5: // Pentagon
			polygon[ii].setX(0.2f);
			polygon[ii].setY(0.7f);
			polygon[ii].setNumVertices(numVertices);
			break;
		case 6: // Hexagon
			polygon[ii].setX(0.7f);
			polygon[ii].setY(0.7f);
			polygon[ii].setNumVertices(numVertices);
			break;
		case 7: // Heptagon
			polygon[ii].setX(-0.7f);
			polygon[ii].setY(-0.2f);
			polygon[ii].setNumVertices(numVertices);
			break;
		case 8: // Octagon
			polygon[ii].setX(0.0f);
			polygon[ii].setY(-0.2f);
			polygon[ii].setNumVertices(numVertices);
			break;
		default: // Circle
			polygon[ii].setX(0.7f);
			polygon[ii].setY(-0.2f);
			polygon[ii].setNumVertices(360);
			break;
		}
		// Place outline drawn polygons below their filled versions
		if (ii > 6)
		{
			polygon[ii].setX(polygon[ii].getX() + 0.0f);
			polygon[ii].setY(polygon[ii].getY() - 0.5f);
		}
		createPolygon(vertices, VAO[ii], VBO[ii], &polygon[ii]);
		// Unbind VBO then VAO
		// It is a good habit to unbind first before rebinding so other objects won't accidentally be modified
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glUseProgram(shaderProgram);
	int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
	float timeStart = glfwGetTime();
	float timeEnd;
	float frameTime;
	int newWidth, newHeight, oldWidth = WIDTH, oldHeight = HEIGHT;
	// static variables that does not require frequent updates for polygon(s)
	polygon[0].setRad(120.0f);
	polygon[0].setVelX(1.0f);
	polygon[0].setVelY(1.0f);
	polygon[2].setVelX(1.0f);
	polygon[2].setVelY(1.0f);
	polygon[3].setVelX(-1.5f);
	polygon[3].setVelY(1.0f);
	// main program loop
	while (!glfwWindowShouldClose(window))
	{
		glfwGetFramebufferSize(window, &newWidth, &newHeight);
		// Set frame rate capped at 60s
		timeEnd = glfwGetTime();
		frameTime = (timeEnd - timeStart);
		if (frameTime > 0.005f)
			frameTime = 0.005f;
		processInput(window, frameTime, &polygon[0]);		
		// Assign dynamic values for each iteration of loop to polygon(s)
		polygon[1].setAngle(polygon[1].getAngle() + -0.3f * frameTime);
		polygon[2].setAngle(polygon[2].getAngle() + frameTime);
		polygon[2].setX(polygon[2].getX() + polygon[2].getVelX() * frameTime);
		polygon[2].setY(polygon[2].getY() + polygon[2].getVelY() * frameTime);
		polygon[3].setX(polygon[3].getX() + polygon[3].getVelX() * frameTime);
		polygon[3].setY(polygon[3].getY() + polygon[3].getVelY() * frameTime);
		polygon[5].setX(0.0f + (polygon[5].getRadX() * (cosf(glfwGetTime()) - sinf(glfwGetTime()))));
		polygon[5].setY(0.0f + (polygon[5].getRadY() * (sinf(glfwGetTime()) + cosf(glfwGetTime()))));
		/*polygon[7].setAngle(polygon[7].getAngle() + 0.8f * frameTime);*/
		// Window Border for moving polygons
		if (polygon[0].getX() + polygon[0].getRadX() > 1.0f)
			polygon[0].setX(1.0f - polygon[0].getRadX());
		if (polygon[0].getX() - polygon[0].getRadX() < -1.0f)
			polygon[0].setX(-1.0f + polygon[0].getRadX());
		if (polygon[0].getY() + polygon[0].getRadY() > 1.0f)
			polygon[0].setY(1.0f - polygon[0].getRadY());
		if (polygon[0].getY() - polygon[0].getRadY() < -1.0f)
			polygon[0].setY(-1.0f + polygon[0].getRadY());
		if (polygon[2].getX() + (polygon[2].getRadX()) > 1.0f)
		{
			polygon[2].setX(1.0f - (polygon[2].getRadX()));
			polygon[2].setVelX(polygon[2].getVelX() * -1.0f);
		}
		if (polygon[2].getX() - (polygon[2].getRadX()) < -1)
		{
			polygon[2].setX(-1.0f + (polygon[2].getRadX()));
			polygon[2].setVelX(polygon[2].getVelX() * -1);
		}
		if (polygon[2].getY() + (polygon[2].getRadY()) > 1)
		{
			polygon[2].setY(1.0f - (polygon[2].getRadY()));
			polygon[2].setVelY(polygon[2].getVelY() * -1);
		}
		if (polygon[2].getY() - (polygon[2].getRadY()) < -1)
		{
			polygon[2].setY(-1.0f + (polygon[2].getRadY()));
			polygon[2].setVelY(polygon[2].getVelY() * -1);
		}
		if (polygon[3].getX() - (polygon[3].getRadX()) > 1)
			polygon[3].setX(-1.0f - (polygon[3].getRadX()));
		if (polygon[3].getX() + (polygon[3].getRadX()) < -1.0f)
			polygon[3].setX(1.0f + (polygon[3].getRadX()));
		if (polygon[3].getY() - (polygon[3].getRadY()) > 1)
			polygon[3].setY(-1.0f - (polygon[3].getRadY()));
		if (polygon[3].getY() + (polygon[3].getRadY()) < -1)
			polygon[3].setY(1.0f + (polygon[3].getRadY()));
		// Edit vertices of each polygon in specific order 
		for (int ii = 0; ii < numObjects; ii++)
		{
			editVertices(vertices, &polygon[ii]);
			rotatePolygon(vertices, &polygon[ii]);
			scalePolygon(vertices, &polygon[ii], 1.0f / (float)newWidth, 1.0f / (float)newHeight); 
			normalize(&polygon[ii], (float)oldWidth / (float)newWidth, (float)oldHeight / (float)newHeight);
			drawPolygon(vertices, VAO[ii], VBO[ii], &polygon[ii]);
		}

		/*editVertices(vertices, &polygon[0]);
		//scalePolygon(vertices, &polygon[0], (float)WIDTH / (float)newWidth, (float)HEIGHT / (float)newHeight);
		rotatePolygon(vertices, &polygon[0]);
		normalize(vertices, &polygon[0], 1.0f / (float)newWidth, 1.0f / (float)newHeight);
		normalizeVel(&polygon[0], (float)oldWidth / (float)newWidth, (float)oldHeight / (float)newHeight);
		drawPolygon(vertices, VAO[0], VBO[0], &polygon[0]);*/

		timeStart = timeEnd;
		oldWidth = newWidth;
		oldHeight = newHeight;
		// Draw polygons and add color
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		for (int ii = 0, numVertices = 3; ii < numObjects; ii++, numVertices++)
		{
			if (ii == 7)
				numVertices = 3;
			switch (numVertices)
			{
			case 3: // Triangle
				glUniform4f(vertexColorLocation, 1.0f, 0.2f, 0.8f, 1.0f);
				break;
			case 4: // Square
				glUniform4f(vertexColorLocation, 0.5f, 0.1f, 1.0f, 1.0f);
				break;
			case 5: // Pentagon
				glUniform4f(vertexColorLocation, 0.3f, 1.0f, 0.4f, 1.0f);
				break;
			case 6: // Hexagon
				glUniform4f(vertexColorLocation, 0.0f, 0.4f, 0.6f, 1.0f);
				break;
			case 7: // Heptagon
				glUniform4f(vertexColorLocation, 0.3f, 0.0f, 0.7f, 1.0f);
				break;
			case 8: // Octagon
				glUniform4f(vertexColorLocation, 0.9f, 0.2f, 0.0f, 1.0f);
				break;
			default: // Circle
				numVertices = 360;
				glUniform4f(vertexColorLocation, 0.0f, 1.0f, 0.0f, 1.0f);
				break;
			}				
			glBindVertexArray(VAO[ii]);
			if (ii < 7)
				glDrawArrays(GL_TRIANGLE_FAN, 0, numVertices);
			else
				glDrawArrays(GL_LINE_LOOP, 0, numVertices);
		}
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	// delete objects before terminating window and exiting program
	// Although OpenGL deletes the VAO and VBO automatically with 
	// glfwTerminate it is a good habit to delete them ourselves
	delete[] polygon;
	glDeleteVertexArrays(numObjects, VAO);
	glDeleteBuffers(numObjects, VBO);
	glfwTerminate();
	return 0;
}
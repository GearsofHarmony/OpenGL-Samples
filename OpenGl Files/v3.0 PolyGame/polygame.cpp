#include "polygame.h"

PolyGame::PolyGame()
{
	completed = false;
}
PolyGame::~PolyGame()
{
	delete polygon;
}
void PolyGame::processInput(GLFWwindow* window)
{
	int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
	double xPos, yPos;
	glfwGetCursorPos(window, &xPos, &yPos);
	xPos -= oldWidth / 2;
	xPos /= oldWidth / 2;
	yPos -= oldHeight / 2;
	yPos /= oldHeight / 2;
	yPos = -yPos;
	//cout << xPos << ' ' << yPos << '\n';
	if (timer >= 0.5f)
	{
		if (!isCompleted()) { //handling for before the polygon is drawn
			if (state == GLFW_PRESS)
			{
				timer = 0.0f;
				if (poly.size() != 0 && isFirstPoint(xPos, yPos)) //if they clicked within the first point, draw the polygon
				{
					center[0] = center[1] = 0.0f;
					for (int ii = 0; ii < poly.size(); ii++)
					{
						center[0] += poly.front().getXPos();
						center[1] += poly.front().getYPos();

						poly.push_back(Point(poly.front().getXPos(), poly.front().getYPos()));
						poly.pop_front();
					}
					center[0] /= poly.size();
					center[1] /= poly.size();
					setCompleted(true);
				}
				else //add a point and display its position on the screen
				{
					poly.push_back(Point(xPos, yPos));
					KEY += 1;
					if (KEY == 1)
					{
						node = new Node;
						insert(node, KEY);
					}
					else
					{
						insert(node, KEY + 1, KEY);
					}
					search(node, KEY)->data->setRatio(oldWidth, oldHeight);
					search(node, KEY)->data->setPos(xPos, yPos);
					search(node, KEY)->data->setRad(0.005f, 0.005f);
					search(node, KEY)->data->setNumVertices(360);
					search(node, KEY)->data->editVertices();
					search(node, KEY)->data->draw();
					//cout << search(node, KEY)->data->getPos().x << ' ' << search(node, KEY)->data->getPos().y << '\n';
				}
			} //end if state
		}
		else { //the polygon has already been drawn, so the click is for transforming it
			if (state == GLFW_PRESS) //make sure it's only on the down press
			{
				timer = 0.0f;
				//call different methods depending on the click
				if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS)
				{
					scalePoly(xPos, yPos);
				}
				else if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_ALT) == GLFW_PRESS)
				{
					cout << "Alt was pressed with this click!\n";
				}
				else
				{
					transPoly(xPos, yPos);
				}
				center[0] = center[1] = 0.0f;
				for (int ii = 0; ii < poly.size(); ii++)
				{
					center[0] += poly.front().getXPos();
					center[1] += poly.front().getYPos();

					poly.push_back(Point(poly.front().getXPos(), poly.front().getYPos()));
					poly.pop_front();
				}
				center[0] /= poly.size();
				center[1] /= poly.size();
			}
		}
	}
};
void PolyGame::initialize(GLFWwindow* window)
{
	Game::initialize(window);
	polygon = new Shape;
	KEY = 0;
	center = new float[2];
	center[0] = center[1] = 0.0f;
}
void PolyGame::update()
{
	float theta = PI / 2 * frameTime;


	if (completed == true)
	{
		polygon->setNumVertices(poly.size());

		for (int ii = 0; ii < poly.size(); ii++)
		{
			float mat[3][3] =
			{
				{ cosf(theta), -sinf(theta), 0.0f },
				{ sinf(theta), cosf(theta), 0.0f },
				{ 0.0f, 0.0f, 1.0f }
			};

			float newX = (poly.front().getXPos() - center[0]) * mat[0][0] + (poly.front().getYPos() - center[1]) * mat[0][1] + 1.0f * mat[0][2];
			float newY = (poly.front().getXPos() - center[0]) * mat[1][0] + (poly.front().getYPos() - center[1]) * mat[1][1] + 1.0f * mat[1][2];

			newX += center[0];
			newY += center[1];

			poly.pop_front();
			poly.push_back(Point(newX, newY));
		}

		for (int ii = 0; ii < polygon->getNumVertices(); ii++)
		{
			float xx = poly.front().getXPos();
			float yy = poly.front().getYPos();
			polygon->getVertex()[ii].x = xx;
			polygon->getVertex()[ii].y = yy;
			poly.pop_front();
			poly.push_back(Point(xx, yy));
			polygon->draw();
			//cout << polygon->getVertex()[ii].x << ' ' << polygon->getVertex()[ii].x << '\n';
		}
	}
	else
		for (int ii = 1; ii <= KEY; ii++)
		{
			if (search(node, ii)->key != NULL)
			{
				search(node, ii)->data->editVertices();
				search(node, ii)->data->draw();
			}
		}
};
void PolyGame::collision()
{
};
void PolyGame::render()
{
	if (completed == false)
		for (int ii = 1; ii <= KEY; ii++)
		{
			if (search(node, ii)->key != NULL)
			{
				ourShader->setVec4("ourColor", 1.0f, 0.8f, 0.1f, 1.0f);
				glBindVertexArray(search(node, ii)->data->getVAO());
				glDrawArrays(GL_TRIANGLE_FAN, 0, search(node, ii)->data->getNumVertices());
				//cout << search(node, ii)->key << ' ' << search(node, ii)->data->getVAO() << '\n';
			}
		}
	else {
		ourShader->setVec4("ourColor", 1.0f, 0.8f, 0.1f, 1.0f);
		glBindVertexArray(polygon->getVAO());
		glDrawArrays(GL_TRIANGLE_FAN, 0, polygon->getNumVertices());
	}
};
void PolyGame::reset()
{
	oldWidth = newWidth;
	oldHeight = newHeight;
};

Node* search(Node* node, unsigned short key, bool flag)
{
	bool found = false;

	while (!found)
	{
		if (node->key == 0)
			return node;
		if (node->key == key)
			found = true;
		else if (flag == true)
			node = node->right;
		else
			node = node->left;
	}
	return node;
}
void insert(Node* node, unsigned short key, unsigned short count)
{
	Node* temp = new Node;
	temp->data = new Shape;
	if (count == 1)
	{
		//count = 1;
		temp->key = count;
		*node = *temp;
		node->left = node->right = node;
	}
	else
	{
		while (node->key != count - 1)
		{
			node = node->right;
		}
		temp->key = count;
		temp->left = node;
		temp->right = node->right;
		(node->right)->left = temp;
		node->right = temp;
	}
	if (count == key)
		return;
	insert(node, key, count + 1);
};

//returns whether or not the user clicked the first point. for use only when initializing the polygon
bool PolyGame::isFirstPoint(float x, float y) {
	float distance = sqrt(pow(poly.front().getXPos() - x, 2) + pow(poly.front().getYPos() - y, 2));
	if (distance <= 0.05f) { //result of distance formula
		return true;
	}
	else {
		return false;
	}
}

void PolyGame::scalePoly(float scale_x, float scale_y)
{
	/*
		Author:        Katie Easlon
					COSC 4332 01
		Edit Date:    3/3/2020
		scalePoly(): Scales and moves the Polygon according to the new scaled points
	*/

	list<Point> orig = poly; //Temp to helo with list manipulation 

	float x, y, ratio_x, ratio_y = 0; //x and y are the new points where ratio_x and ratio_y are what the old points are multipled by

	ratio_x = scale_x / orig.front().getXPos(); //sets the ratio for x
	ratio_y = scale_y / orig.front().getYPos();    //sets the ratio for y

	for (int i = 0; i < poly.size(); i++) //Scales the old points to the new values
	{
		x = ratio_x * orig.front().getXPos(); //Sets x to the new value
		y = ratio_y * orig.front().getYPos(); // Sets y to the new value

		//Manipulate the temp list
		orig.pop_front();
		orig.push_back(Point(x, y));

		//Manipulat the real list
		poly.pop_front();
		poly.push_back(Point(x, y));

		//Set both to zero for the next itteration of the for loop
		x = 0;
		y = 0;
	}

}

void PolyGame::transPoly(float transX, float transY)
{
	list<Point> temp = poly;

	float x_prime, y_prime = 0;

	float x, y = 0;

	x = transX - temp.front().getXPos();
	y = transY - temp.front().getYPos();

	for (int k = 0; k < poly.size(); k++)
	{
		x_prime = x + temp.front().getXPos();
		y_prime = y + temp.front().getYPos();

		temp.pop_front();
		temp.push_back(Point(x_prime, y_prime));
		poly.pop_front();
		poly.push_back(Point(x_prime, y_prime));

		x_prime, y_prime = 0;
	}

}
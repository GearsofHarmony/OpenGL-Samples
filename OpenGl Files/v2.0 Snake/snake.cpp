#include "snake.h"

Node* search(Node* node, unsigned short key, bool flag)
{
	bool found = false;

	while (!found)
	{
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

Snake::Snake()
{
	player1 = false;
	srand(glfwGetTime());
}
Snake::~Snake()
{
	delete head;
	delete body;
	delete[] tail;
}
void Snake::initialize(int nWidth, int nHeight)
{
	head = new Shape;
	tail = new Shape[3];
	body = new Node;
	KEY = 75;

	insert(body, KEY);
	head->setNumVertices(360);
	head->setPos(xPos, yPos);
	head->setAngle(theta);
	head->setVel(0.5f, 0.5f);
	head->setRatio(nWidth, nHeight);

	draw(head);


	for (int ii = 1, count = 1; ii <= KEY; ii++)
	{
		search(body, ii)->data->setNumVertices(4);
		search(body, ii)->data->setAngle(head->getAngle());
		search(body, ii)->data->setPos(head->getPos().x, head->getPos().y);
		if (ii > KEY - 10)
		{
			search(body, ii)->data->setRad(search(body, ii)->data->getRad().x - 1.0f * count, search(body, ii)->data->getRad().y - 1.0f * count);
			count++;
		}
		search(body, ii)->data->setRatio(nWidth, nHeight);
		draw(search(body, ii)->data);
	}

	for (int ii = 0; ii < 3; ii++)
	{
		tail[ii].setNumVertices(360);
		tail[ii].setAngle(head->getAngle());
		tail[ii].setRad(tail[ii].getRad().x - 7.5f * (ii + 1), tail[ii].getRad().y - 7.5f * (ii + 1));
		tail[ii].setPos(head->getPos().x, head->getPos().y);
		tail[ii].setRatio(nWidth, nHeight);
		draw(&tail[ii]);
	}
}
void Snake::update(float frameTime)
{
	head->setPos(head->getPos().x + (head->getVel().x * frameTime * cosf(head->getAngle())),
		head->getPos().y + (head->getVel().y * frameTime * sinf(head->getAngle())));

	draw(head);

	search(body, 1)->data->setAngle(head->getAngle());
	search(body, 1)->data->setPos(head->getPos().x, head->getPos().y);
	draw(search(body, 1)->data);

	for (int ii = KEY; ii >= 2; ii--)
	{
		search(body, ii)->data->setAngle((search(body, ii)->left)->data->getAngle());
		search(body, ii)->data->setPos((search(body, ii)->left)->data->getPos().x, (search(body, ii)->left)->data->getPos().y);
		draw(search(body, ii)->data);
	}

	for (int ii = 0; ii < 3; ii++)
	{
		if (ii == 0)
		{
			tail[0].setAngle(search(body, KEY)->data->getAngle());
			tail[0].setPos(search(body, KEY)->data->getPos().x, search(body, KEY)->data->getPos().y);
		}
		else
		{
			tail[ii].setPos(tail[ii - 1].getPos().x - (tail[ii - 1].getRad().x / tail[ii].getWidthRatio()) * cosf(tail[0].getAngle()),
				tail[ii - 1].getPos().y - (tail[ii - 1].getRad().y / tail[ii].getHeightRatio()) * sinf(tail[0].getAngle()));
		}
		draw(&tail[ii]);
	}
};
void Snake::processInput(GLFWwindow* window, float frameTime)
{
	if (player1 == true)
	{
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		{
			head->setAngle(head->getAngle() + ((3.0f * PI / 1.0f) * frameTime));
		}
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		{
			head->setAngle(head->getAngle() - ((3.0f * PI / 1.0f) * frameTime));
		}
	}
	else
	{
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			head->setAngle(head->getAngle() + ((3.0f * PI / 1.0f) * frameTime));
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			head->setAngle(head->getAngle() - ((3.0f * PI / 1.0f) * frameTime));
		}
	}
}
bool Snake::collision(Shape* ptr)
{
	if (head->getPos().x + head->getRad().x / (float)head->getWidthRatio() > ptr->getPos().x - ptr->getRad().x / (float)ptr->getWidthRatio()
		&& head->getPos().x - head->getRad().x / (float)head->getWidthRatio() < ptr->getPos().x + ptr->getRad().x / (float)ptr->getWidthRatio())
	{
		if (head->getPos().y + head->getRad().y / (float)head->getHeightRatio() > ptr->getPos().y - ptr->getRad().y / (float)ptr->getHeightRatio()
			&& head->getPos().y - head->getRad().y / (float)head->getHeightRatio() < ptr->getPos().y + ptr->getRad().y / (float)ptr->getHeightRatio())
		{
			return true;
		}
	}
	return false;
}
void Snake::reset(int nWidth, int nHeight)
{
	head->setRatio(nWidth, nHeight);
	draw(head);

	for (int ii = 1; ii <= KEY; ii++)
	{
		search(body, ii)->data->setRatio(nWidth, nHeight);
		draw(search(body, ii)->data);
	}

	for (int ii = 0; ii < 3; ii++)
	{
		tail[ii].setRatio(nWidth, nHeight);
		if (ii == 0)
		{
			tail[0].setAngle(search(body, KEY)->data->getAngle());
			tail[0].setPos(search(body, KEY)->data->getPos().x, search(body, KEY)->data->getPos().y);
		}
		else
		{
			tail[ii].setPos(tail[ii - 1].getPos().x - (tail[ii - 1].getRad().x / tail[ii].getWidthRatio()) * cosf(tail[0].getAngle()),
				tail[ii - 1].getPos().y - (tail[ii - 1].getRad().y / tail[ii].getHeightRatio()) * sinf(tail[0].getAngle()));
		}
		draw(&tail[ii]);
	}
};
void Snake::grow()
{
	insert(this->body, KEY + 10, KEY);
	KEY += 10;
	for (int ii = KEY - 20, count = 1; ii <= KEY; ii++)
	{
		search(body, ii)->data->setNumVertices(4);
		search(body, ii)->data->setAngle(search(body, ii)->left->data->getAngle());
		search(body, ii)->data->setPos(search(body, ii)->left->data->getPos().x, search(body, ii)->left->data->getPos().y);
		search(body, ii)->data->setRad(search(body, ii)->left->data->getRad().x, search(body, ii)->left->data->getRad().y);
		if (ii > KEY - 10)
		{
			search(body, ii)->data->setRad(search(body, ii)->data->getRad().x - 1.0f * count, search(body, ii)->data->getRad().y - 1.0f * count);
			count++;
		}
		search(body, ii)->data->setRatio(search(body, ii)->left->data->getWidthRatio(), search(body, ii)->left->data->getHeightRatio());
		draw(search(body, ii)->data);
	}
};
void Snake::draw(Shape* ptr)
{
	ptr->editVertices();

	for (int vv = 0; vv < ptr->getNumVertices(); vv++)
	{
		ptr->getVertex()[vv] = Vector2::Transform(ptr->getVertex()[vv],
			Matrix3::createScale(1.0f / (float)ptr->getWidthRatio(), 1.0f / (float)ptr->getHeightRatio()));
	}

	ptr->draw();
};
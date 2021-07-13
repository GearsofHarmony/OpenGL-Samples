#include "shape.h"

Shape::Shape()
{
	pos.Set(0.0f, 0.0f);
	vel.Set(0.0f, 0.0f);
	rad.Set(30.0f, 30.0f);
	angle = 0.0f;
	numVertices = 3;
	vertex = new Vector2[360];

	glGenVertexArrays(1, &VAO); //Tell OpenGL how many VAOs there are, VAO is a pointer
	glGenBuffers(1, &VBO); //Tell OpenGL how many VBOs there are, VBO is a pointer
};
Shape::~Shape() 
{ 
	delete[] vertex;
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
};

void Shape::editVertices()
{
	const float ANGLE = (2*PI) / this->getNumVertices();

	for (int ii = 0; ii < this->getNumVertices(); ii++)
	{
		this->getVertex()[ii].x = this->getPos().x + this->getRad().x * cosf(ii * ANGLE);
		this->getVertex()[ii].y = this->getPos().y + this->getRad().y * sinf(ii * ANGLE);
		if (abs(this->getVertex()[ii].x) < 0.00009f)
			this->getVertex()[ii].x = 0.0f;
		if (abs(this->getVertex()[ii].y) < 0.00009f)
			this->getVertex()[ii].y = 0.0f;
	}
}

void Shape::draw()
{
	float vertices[720] = { 0.0f };
	for (int ii = 0, vv = 0; ii < this->getNumVertices(); ii++)
	{
		vertices[vv] = /*this->getPos().x + */this->getVertex()[ii].x;
		vertices[vv + 1] = /*this->getPos().y + */this->getVertex()[ii].y;
		vv += 2;
	}
	for (int ii = 0; ii < this->getNumVertices() * 2; ii++)
	{
		if (abs(vertices[ii]) < 0.00009f)
			vertices[ii] = 0.0f;
	}
	glBindVertexArray(this->VAO); //Bind current VAO first before modifying values
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO); //Bind current VBO to VAO before modifying values
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 2 * this->getNumVertices(), vertices, GL_STATIC_DRAW); //Copy vertice array to buffer with memory size in bytes
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0); //Tell OpenGL how to read vertex data in buffer
	// It is a good habit to unbind first before rebinding so other objects won't accidentally be modified
	glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind VBO first
	glBindVertexArray(0); // Unbind VAO last
}
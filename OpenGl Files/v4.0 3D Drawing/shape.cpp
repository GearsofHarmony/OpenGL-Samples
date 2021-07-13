#include "shape.h"

Shape::Shape(int numVert, int numIndices) :numVertices(numVert), indiceSize(numIndices)
{
	pos.Set(0.0f, 0.0f, 0.0f);
	vel.Set(0.0f, 0.0f, 0.0f);
	rad.Set(2.0f, 2.0f, 0.0f);
	angle = 0.0f;
	data = new Data[numVertices];
	indices = new unsigned int[indiceSize];

	glGenVertexArrays(1, &VAO); //Tell OpenGL how many VAOs there are, VAO is a pointer
	glGenBuffers(1, &VBO); //Tell OpenGL how many VBOs there are, VBO is a pointer
	glGenBuffers(1, &EBO); //Tell OpenGL how many EBOs there are, EBO is a pointer
};
Shape::~Shape() 
{ 
	SAFE_DELETE_ARRAY(data);
	SAFE_DELETE_ARRAY(indices);
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
};

void Shape::editVertices(const int numVertices, const int type, const float OFFSET)
{
	const float ANGLE = (2 * PI) / numVertices;

	for (int vv = 0; vv < type; vv++)
	{
		int index = vv * numVertices;
		for (int ii = index; ii < index + numVertices; ii++)
		{
			this->getData()[ii].vertex.x = this->getPos().x + this->getRad().x * cosf(ii * ANGLE + OFFSET);
			if (abs(this->getData()[ii].vertex.x) < 0.00009f)
				this->getData()[ii].vertex.x = 0.0f;

			this->getData()[ii].vertex.y = this->getPos().y + this->getRad().y * sinf(ii * ANGLE + OFFSET);
			if (abs(this->getData()[ii].vertex.y) < 0.00009f)
				this->getData()[ii].vertex.y = 0.0f;

			this->getData()[ii].vertex.z = this->getPos().z + this->getRad().z * cosf(vv * PI + OFFSET);
			if (abs(this->getData()[ii].vertex.z) < 0.00009f)
				this->getData()[ii].vertex.z = 0.0f;
		}
	}
}

void Shape::createCube(float xRad, float yRad, float zRad)
{
	this->setRad(xRad, yRad, zRad);
	this->setPos(0.0f, (this->getRad().y * sinf(3 * PI / 4)), 0.0f);
	this->editVertices(4, 2, PI / 4.0f);

	this->getData()[19].vertex = this->getData()[13].vertex = this->getData()[0].vertex;
	this->getData()[18].vertex = this->getData()[8].vertex = this->getData()[1].vertex;
	this->getData()[21].vertex = this->getData()[11].vertex = this->getData()[2].vertex;
	this->getData()[20].vertex = this->getData()[14].vertex = this->getData()[3].vertex;

	this->getData()[16].vertex = this->getData()[12].vertex = this->getData()[4].vertex;
	this->getData()[17].vertex = this->getData()[9].vertex = this->getData()[5].vertex;
	this->getData()[22].vertex = this->getData()[10].vertex = this->getData()[6].vertex;
	this->getData()[23].vertex = this->getData()[15].vertex = this->getData()[7].vertex;

	unsigned int indice[] =
	{
		0,1,2,2,3,0,
		4,5,6,6,7,4,
		8,9,10,10,11,8,
		12,13,14,14,15,12,
		16,17,18,18,19,16,
		20,21,22,22,23,20
	};

	for (int ii = 0; ii < 36; ii++)
	{
		this->getIndices()[ii] = indice[ii];
	}
};

void Shape::draw()
{
	glBindVertexArray(this->getVAO()); //Bind current VAO first before modifying values
	glBindBuffer(GL_ARRAY_BUFFER, this->getVBO()); //Bind current VBO to VAO before modifying values
	glBufferData(GL_ARRAY_BUFFER, sizeof(*this->getData()) * this->getNumVertices(), this->getData(), GL_STATIC_DRAW); //Copy object data to buffer with memory size in bytes
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->getEBO()); //Bind current EBO to VAO before modifying values
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(*this->getIndices()) * this->indiceSize, this->getIndices(), GL_STATIC_DRAW); //Copy object indices data to buffer with memory size in bytes
	//Tell OpenGL how to read vertex data in buffer
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(*this->getData()), (void*)0); // Vertices
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(*this->getData()), (void*)sizeof(Vec3)); // Texture Coordinates
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(*this->getData()), (void*)((sizeof(Vec3) + sizeof(Vec2)))); // Normal Values
	//glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(*this->getData()), (void*)((sizeof(Vec3) + sizeof(Vec3) + sizeof(Vec2)))); // Color values
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	//glEnableVertexAttribArray(3);
	// It is a good habit to unbind first before rebinding so other objects won't accidentally be modified
	//glBindVertexArray(0);
}

unsigned int loadTexture(const char* file)
{
	unsigned int id;
	glGenTextures(1, &id);

	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
	unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 0);
	if (data)
	{
		GLenum format = GL_RGBA;
		if (nrChannels == 1)
			format = GL_RED;
		else if (nrChannels == 3)
			format = GL_RGB;
		else if (nrChannels == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, id);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		// set the texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	return id;
};
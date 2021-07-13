#include "room.h"

void Room::initialize()
{
	// texture floor and ceiling
	// -------------------------
	flatTex = loadTexture("textures/wood1.png");

	// texture wall
	// ------------
	wallTex = loadTexture("textures/wood3.png");

	thing = new Shape(24, 36);
	thing->createCube(96.0f, 32.0f, 96.0f);
	for (int ii = 0; ii < thing->getNumVertices();)
	{
		if (ii < 16)
		{
			thing->getData()[ii++].texCoord.Set(8.0f, 1.0f);
			thing->getData()[ii++].texCoord.Set(0.0f, 1.0f);
			thing->getData()[ii++].texCoord.Set(0.0f, 0.0f);
			thing->getData()[ii++].texCoord.Set(8.0f, 0.0f);
		}
		else
		{
			thing->getData()[ii++].texCoord.Set(8.0f, 8.0f);
			thing->getData()[ii++].texCoord.Set(0.0f, 8.0f);
			thing->getData()[ii++].texCoord.Set(0.0f, 0.0f);
			thing->getData()[ii++].texCoord.Set(8.0f, 0.0f);
		}
	}
	Vec3 normal[24];
	normal[3] = normal[2] = normal[1] = normal[0] = Vec3(0.0f, 0.0f, -1.0f);
	normal[7] = normal[6] = normal[5] = normal[4] = Vec3(0.0f, 0.0f, 1.0f);
	normal[11] = normal[10] = normal[9] = normal[8] = Vec3(1.0f, 0.0f, 0.0f);
	normal[15] = normal[14] = normal[13] = normal[12] = Vec3(-1.0f, 0.0f, 0.0f);
	normal[19] = normal[18] = normal[17] = normal[16] = Vec3(0.0f, -1.0f, 0.0f);
	normal[23] = normal[22] = normal[21] = normal[20] = Vec3(0.0f, 1.0f, 0.0f);
	for (int ii = 0; ii < thing->getNumVertices(); ii++)
	{
		//thing->getData()[ii].RGB.Set(1.0f, 1.0f, 1.0f);
		thing->getData()[ii].normal = normal[ii];
	}
	thing->draw();
};
void Room::update(float frameTime) {};
void Room::render()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, wallTex);
	glBindVertexArray(thing->getVAO());
	glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, (void*)0);
	glBindTexture(GL_TEXTURE_2D, flatTex);
	glBindVertexArray(thing->getVAO());
	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, (void*)(sizeof(unsigned int) * 24));
};
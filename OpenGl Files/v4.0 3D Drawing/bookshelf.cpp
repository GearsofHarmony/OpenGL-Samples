#include "bookshelf.h"

void BookShelf::initialize()
{
	// load and create a texture 
	// -------------------------
	thingTex = loadTexture("textures/bookshelf2.png");

	thing = new Shape(24, 36);
	thing->createCube(16.0f, 23.0f, 4.0f);
	Vec3 normal[24];
	normal[3] = normal[2] = normal[1] = normal[0] = Vec3(0.0f, 0.0f, 1.0f);
	normal[7] = normal[6] = normal[5] = normal[4] = Vec3(0.0f, 0.0f, -1.0f);
	normal[11] = normal[10] = normal[9] = normal[8] = Vec3(-1.0f, 0.0f, 0.0f);
	normal[15] = normal[14] = normal[13] = normal[12] = Vec3(1.0f, 0.0f, 0.0f);
	normal[19] = normal[18] = normal[17] = normal[16] = Vec3(0.0f, 1.0f, 0.0f);
	normal[23] = normal[22] = normal[21] = normal[20] = Vec3(0.0f, -1.0f, 0.0f);
	for (int ii = 0; ii < thing->getNumVertices(); ii++)
	{
		thing->getData()[ii].vertex = Vec3::Transform(thing->getData()[ii].vertex, Mat4::createTranslation(Vec3(0.0f, 0.01f, -45.0f)));
		thing->getData()[ii].normal = normal[ii];
	}
	Vec2 texCoord[] = { 
		Vec2(0.0f, 1.0f), Vec2(0.4f, 1.0f), Vec2(0.5f, 1.0f), Vec2(0.9f, 1.0f), Vec2(1.0f, 1.0f), 
		Vec2(0.0f, 0.0f), Vec2(0.4f, 0.0f), Vec2(0.5f, 0.0f), Vec2(0.9f, 0.0f), Vec2(0.9f, 32.0f / 46.0f), Vec2(1.0f, 32.0f / 46.0f) };
	unsigned int index[] = { 1,0,5,6,3,2,7,8,2,1,6,7,2,1,6,7,10,4,3,9,10,4,3,9 };
	for (int ii = 0; ii < thing->getNumVertices();)
	{
		thing->getData()[ii].texCoord = texCoord[index[ii++]];
		thing->getData()[ii].texCoord = texCoord[index[ii++]];
		thing->getData()[ii].texCoord = texCoord[index[ii++]];
		thing->getData()[ii].texCoord = texCoord[index[ii++]];
	}
	thing->draw();
};
void BookShelf::update(float frameTime) {};
void BookShelf::render()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, thingTex);
	glBindVertexArray(thing->getVAO());
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(sizeof(unsigned int) * 6));
	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, (void*)(sizeof(unsigned int) * 12));
	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, (void*)(sizeof(unsigned int) * 24));
};
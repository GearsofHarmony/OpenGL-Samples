#include "carpet.h"

void Carpet::initialize()
{
	// load and create a texture 
	// -------------------------
	thingTex = loadTexture("textures/carpet.png");

	thing = new Shape(8, 10);
	thing->setRad(32.0f, 32.0f, 0.0f);
	thing->editVertices(thing->getNumVertices() / 2.0f, 1, 0*PI / 4.0f);

	thing->getData()[4].vertex.Set(thing->getData()[0].vertex.x - 8.0f, thing->getData()[0].vertex.y, 0.0f);
	thing->getData()[5].vertex.Set(thing->getData()[1].vertex.x, thing->getData()[1].vertex.y - 8.0f, 0.0f);
	thing->getData()[6].vertex.Set(thing->getData()[2].vertex.x + 8.0f, thing->getData()[2].vertex.y, 0.0f);
	thing->getData()[7].vertex.Set(thing->getData()[3].vertex.x, thing->getData()[3].vertex.y + 8.0f, 0.0f);
	//Position cube
	for (int ii = 0; ii < thing->getNumVertices(); ii++)
	{
		thing->getData()[ii].vertex = Vec3::Transform(thing->getData()[ii].vertex, Mat4::createRotationZ(PI / 4.0f));
		thing->getData()[ii].vertex = Vec3::Transform(thing->getData()[ii].vertex, Mat4::createRotationX(PI / 2.0f));
		thing->getData()[ii].vertex = Vec3::Transform(thing->getData()[ii].vertex, Mat4::createTranslation(Vec3(00.0f, 0.01f, 0.0f)));
	}
	//Assign Texture Coordinates
	for (int ii = 0; ii < thing->getNumVertices();)
	{
		thing->getData()[ii++].texCoord.Set(2.0f, 2.0f);
		thing->getData()[ii++].texCoord.Set(0.0f, 2.0f);
		thing->getData()[ii++].texCoord.Set(0.0f, 0.0f);
		thing->getData()[ii++].texCoord.Set(2.0f, 0.0f);
		thing->getData()[ii++].texCoord.Set(1.75f, 1.75f);
		thing->getData()[ii++].texCoord.Set(0.25f, 1.75f);
		thing->getData()[ii++].texCoord.Set(0.25f, 0.25f);
		thing->getData()[ii++].texCoord.Set(1.75f, 0.25f);
	}
	//Color data
	for (int ii = 0; ii < thing->getNumVertices(); ii++)
	{
		thing->getData()[ii].normal.Set(0.0f, 1.0f, 0.0f);
		//thing->getData()[ii].RGB.Set(1.0f, 1.0f, 1.0f);
	}
	unsigned int indice[] =
	{
		//0,1,2,2,3,0
		//0,1,5,5,0,4,1,2,5,5,6,2,2,3,6,6,7,3,3,0,7,7,4,0
		0,4,1,5,2,6,3,7,0,4
	};
	for (int ii = 0; ii < 10; ii++)
	{
		thing->getIndices()[ii] = indice[ii];
	}
	thing->draw();
};
void Carpet::update(float frameTime) {};
void Carpet::render()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, thingTex);
	glBindVertexArray(thing->getVAO());
	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glDrawElements(GL_TRIANGLE_STRIP, 10, GL_UNSIGNED_INT, 0);
};
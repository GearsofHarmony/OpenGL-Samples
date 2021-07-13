#include "cube.h"

void Cube::initialize()
{
	thing = new Shape(24, 36);
	thing->createCube(16.0f, 16.0f, 16.0f); //Create the evil cube

	Vec3 normal[24];
	normal[3] = normal[2] = normal[1] = normal[0] = Vec3(0.0f, 0.0f, 1.0f);
	normal[7] = normal[6] = normal[5] = normal[4] = Vec3(0.0f, 0.0f, -1.0f);
	normal[11] = normal[10] = normal[9] = normal[8] = Vec3(-1.0f, 0.0f, 0.0f);
	normal[15] = normal[14] = normal[13] = normal[12] = Vec3(1.0f, 0.0f, 0.0f);
	normal[19] = normal[18] = normal[17] = normal[16] = Vec3(0.0f, 1.0f, 0.0f);
	normal[23] = normal[22] = normal[21] = normal[20] = Vec3(0.0f, -1.0f, 0.0f);

	for (int ii = 0; ii < thing->getNumVertices(); ii++)
	{
		//Position cube
		thing->getData()[ii].vertex = Vec3::Transform(thing->getData()[ii].vertex, Mat4::createTranslation(Vec3(0.0f, /*(thing->getRad().y * sinf(3 * PI / 4)) + */0.01f, 0.0f)));
		
		//Color data
		//thing->getData()[ii].RGB.Set(1.0f, 1.0f, 1.0f);
		//thing->getData()[ii].RGB.Set(1.0f, 0.5f, 0.31f);
		//if (ii < 4)//Front face
		//	thing->getData()[ii].RGB.Set(1.0f, 1.0f, 1.0f);
		//else if (ii < 8)//Back face
		//	thing->getData()[ii].RGB.Set(1.0f, 0.0f, 0.0f);
		//else if (ii < 12)//Left face
		//	thing->getData()[ii].RGB.Set(0.0f, 0.1f, 0.0f);
		//else if (ii < 16)//Right face
		//	thing->getData()[ii].RGB.Set(0.0f, 0.0f, 0.1f);
		//else if (ii < 20)//Top face
		//	thing->getData()[ii].RGB.Set(0.5f, 0.5f, 0.5f);
		//else//Bottom face
		//	thing->getData()[ii].RGB.Set(0.0f, 0.0f, 0.0f);

		thing->getData()[ii].normal = normal[ii];
	}
	
	//Assign Texture Coordinates
	for (int ii = 0; ii < thing->getNumVertices();)
	{
		thing->getData()[ii++].texCoord.Set(1.0f, 1.0f);
		thing->getData()[ii++].texCoord.Set(0.0f, 1.0f);
		thing->getData()[ii++].texCoord.Set(0.0f, 0.0f);
		thing->getData()[ii++].texCoord.Set(1.0f, 0.0f);
	}

	thing->draw();

	// load and create a texture 
	// -------------------------
	thingTex = loadTexture("textures/container2.png");
};
void Cube::update(float frameTime)
{
	for (int ii = 0; ii < thing->getNumVertices(); ii++)
	{
		thing->getData()[ii].vertex = Vec3::Transform(thing->getData()[ii].vertex, Mat4::createRotationZ(PI / 4.0f * frameTime));
		thing->getData()[ii].normal = Vec3::Transform(thing->getData()[ii].normal, Mat4::createRotationZ(PI / 4.0f * frameTime));
	}
	thing->draw();
};
void Cube::render()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, thingTex);
	glBindVertexArray(thing->getVAO());
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
};
//Vec3 normal[24];
//normal[0] = Vec3::Cross((thing->getData()[1].vertex - thing->getData()[0].vertex),(thing->getData()[3].vertex - thing->getData()[0].vertex));
//normal[4] = Vec3::Cross((thing->getData()[4].vertex - thing->getData()[5].vertex), (thing->getData()[6].vertex - thing->getData()[5].vertex));
//normal[8] = Vec3::Cross((thing->getData()[9].vertex - thing->getData()[8].vertex), (thing->getData()[11].vertex - thing->getData()[8].vertex));
//normal[12] = Vec3::Cross((thing->getData()[13].vertex - thing->getData()[12].vertex), (thing->getData()[15].vertex - thing->getData()[12].vertex));
//normal[16] = Vec3::Cross((thing->getData()[17].vertex - thing->getData()[16].vertex), (thing->getData()[19].vertex - thing->getData()[16].vertex));
//normal[20] = Vec3::Cross((thing->getData()[21].vertex - thing->getData()[20].vertex), (thing->getData()[23].vertex - thing->getData()[20].vertex));
////normal[3] = normal[2] = normal[1] = normal[0] = Vec3(0.0f, 0.0f, 1.0f);
////normal[7] =normal[6] =normal[5] =normal[4] = Vec3(0.0f, 0.0f, -1.0f);
////normal[11] =normal[10] =normal[9] =normal[8] = Vec3(-1.0f, 0.0f, 0.0f);
////normal[15] =normal[14] =normal[13] =normal[12] = Vec3(1.0f, 0.0f, 0.0f);
////normal[19] =normal[18] =normal[17] =normal[16] = Vec3(0.0f, 1.0f, 0.0f);
////normal[23] =normal[22] =normal[21] =normal[20] = Vec3(0.0f, -1.0f, 0.0f);
//for (int ii = 0, vv = 0; ii < thing->getNumVertices();vv+=4)
//{
//	normal[ii++] = normal[vv];
//	normal[ii++] = normal[vv];
//	normal[ii++] = normal[vv];
//	normal[ii++] = normal[vv];
//}
//for (int ii = 0; ii < thing->getNumVertices(); ii++)
//{
//	thing->getData()[ii].normal = normal[ii];
//	thing->getData()[ii].normal.Normalize();
//}
#include "Planet.h"
#include "../gl/glut.h"
#include "3DSLoader.h"
#include "Texture2D.h"

Planet::Planet(Vector3D startPosition, string modelFileName)
{
	std::strcpy(fileName, modelFileName.c_str());
	loadModel();
}

void Planet::loadModel()
{
	if (fileName[0] != '---')
	{
		Load3DS(&object, fileName);
	}
}

void Planet::loadTexture(char* path, int width, int height)
{

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	Texture2D* planetTex = new Texture2D;
	planetTex->Load(path, width, height);
	object.id_texture = planetTex->GetID();
}

void Planet::update(float deltaTime)
{

}

void Planet::translate(float x, float y, float z)
{
	glTranslatef(x, y, z);
}

void Planet::rotate(float a, float x, float y, float z)
{
	glRotatef(a, x, y, z);
}

void Planet::render()
{
	glPushMatrix();
	glBegin(GL_TRIANGLES);
	glBindTexture(GL_TEXTURE_2D, 0);

	for (int l_index = 0; l_index < object.polygons_qty; l_index++)
	{
		glTexCoord2f(object.mapcoord[object.polygon[l_index].a].u, object.mapcoord[object.polygon[l_index].a].v);

		glVertex3f(object.vertex[object.polygon[l_index].a].x,
			object.vertex[object.polygon[l_index].a].y,
			object.vertex[object.polygon[l_index].a].z);

		glTexCoord2f(object.mapcoord[object.polygon[l_index].b].u, object.mapcoord[object.polygon[l_index].b].v);

		glVertex3f(object.vertex[object.polygon[l_index].b].x,
			object.vertex[object.polygon[l_index].b].y,
			object.vertex[object.polygon[l_index].b].z);

		glTexCoord2f(object.mapcoord[object.polygon[l_index].c].u, object.mapcoord[object.polygon[l_index].c].v);

		glVertex3f(object.vertex[object.polygon[l_index].c].x,
			object.vertex[object.polygon[l_index].c].y,
			object.vertex[object.polygon[l_index].c].z);
	}

	glEnd();
	glPopMatrix();
}
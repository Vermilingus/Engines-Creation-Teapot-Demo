#include "Denzil.h"
#include "../gl/glut.h"
#include "3DSLoader.h"
#include "Texture2D.h"
#include "Collision.h"
#include "GameScreenManager.h"
#include "PhysObj.h"
#include "Constants.h"
#include <math.h> 
#include <iostream>
#include "Dodgeball.h"

static float moveSpeed = 2.0f;

Denzil::Denzil(string modelFileName, GameScreenManager* GSM) : PhysObj()
{
	mPosition.x = -7;
	mPosition.y = -4;
	mPosition.z = 0;
	std::strcpy(fileName, modelFileName.c_str());
	loadModel();
	mScale = 0.01;
	collision = new Sphere(mPosition, mScale*75);
	mAccel.x = 0;
	mAccel.y = 0;
	mAccel.z = 0;
	PhysObj::PhysObj();
	hitsLeft = 4;
	manager = GSM;
	trailStepCounter = 0;
	pos10 = Vector3D(0, 0, 0);
	pos20 = Vector3D(0, 0, 0);
}

void Denzil::update(float deltaTime, SDL_Event e)
{
	
	
	mPosition.x += mVelocity.x*deltaTime;
	mPosition.y += mVelocity.y*deltaTime;
	mPosition.z += mVelocity.z*deltaTime;

	mPosition += mVelocity*deltaTime + mAccel * (0.5*deltaTime*deltaTime);
	mVelocity += mAccel*deltaTime;
	mVelocity = mVelocity*0.99;

	if (mPosition.x < -7 || mPosition.x > 7)
		mVelocity.x *= -0.95;

	if (mPosition.y > 4 || mPosition.y < -4)
		mVelocity.y *= -0.95;

	if (mPosition.z > 4 || mPosition.z < -4)
		mVelocity.z *= -0.95;

	if (mPosition.x > 6)
	{
		manager->PlaySoundEffect(2);
		manager->ChangeScreen(SCREEN_WIN, deltaTime);
	}

	collision->SetCollided(false);
	collision->Update(mPosition);

	if (hitsLeft > 0)
	{
		if (e.type == SDL_KEYDOWN)
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_w:
				mVelocity = Vector3D(0, 0, -1) * moveSpeed;
				break;
			case SDLK_s:
				mVelocity = Vector3D(0, 0, 1) * moveSpeed;
				break;
			case SDLK_d:
				mVelocity = Vector3D(1, 0, 0) * moveSpeed;
				break;
			case SDLK_a:
				mVelocity = Vector3D(-1, 0, 0) * moveSpeed;
				break;
			}
		}
	}

	
	
}
int Denzil::getHit()
{
	hitsLeft--;
	trail.push_back(new Dodgeball("court.raw",true));
	return hitsLeft;
}

int Denzil::GetBalls()
{
	return(4 - hitsLeft);
}

void Denzil::render()
{
	glPushMatrix();
	glTranslatef(mPosition.x, mPosition.y, mPosition.z);
		glPushMatrix();
		glColor3f(0, 0, 0);
		glutWireSphere(mScale * 75, 10, 10);
		glPopMatrix();
	glScalef(mScale, mScale, mScale);
	glColor3f(1, 1, 1);
	
	glBindTexture(GL_TEXTURE_2D, object.id_texture);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_TRIANGLES);
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

	prevPositions.insert(prevPositions.begin(),mPosition);

	if (prevPositions.size() >= 20)
	{
		cout << prevPositions[19].x << " " << prevPositions[19].y << " " << prevPositions[19].z << " " << endl;
		pos10 = prevPositions[19];
	}

	if (prevPositions.size() >= 40)
	{
		pos20 = prevPositions[39];
	}

	if (prevPositions.size() >= 60)
	{
		prevPositions.pop_back();
		pos30 = prevPositions.back();
	}

	if (trail.size() > 0)
	{
		glPushMatrix();
		trail[0]->setPosition(pos10);
		glPopMatrix();
	}

	if (trail.size() > 1)
	{
		glPushMatrix();
		trail[1]->setPosition(pos20);
		glPopMatrix();
	}

	if (trail.size() > 2)
	{
		glPushMatrix();
		trail[2]->setPosition(pos30);
		glPopMatrix();
	}

	

	for (int i = 0; i < trail.size(); i++)
	{
		trail[i]->render();
	}

	PhysObj::render();
}

void Denzil::loadModel()
{
	if (fileName[0] != '---')
	{
		Load3DS(&object, fileName);
	}
}

void Denzil::translate(float x, float y, float z)
{
	glTranslatef(x, y, z);
}
void Denzil::rotate(float a, float x, float y, float z)
{
	glRotatef(a, x, y, z);
}

void Denzil::loadTexture(char* path, int width, int height) 
{
	PhysObj::loadTexture(path, width, height);
}
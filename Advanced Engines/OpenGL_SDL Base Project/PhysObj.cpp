#include "PhysObj.h"
#include <stdlib.h>
#include "../gl/glut.h"
#include "Texture2D.h"
#include <string>
#include "Collision.h"
using namespace std;


PhysObj::PhysObj()
{
	mAccel.x = 0;
	mAccel.y = -2;
	mAccel.z = 0;
	bounced = false;
	timeActive = 0;
}

void PhysObj::loadTexture(char* path, int width, int height)
{
	Texture2D* ObjectTex = new Texture2D();
	if (ObjectTex->Load(path, width, height))
	{
		object.id_texture = ObjectTex->GetID();
	}
}

void PhysObj::update(float deltaTime)
{
	bounced = false;
	timeActive += deltaTime;

	mPosition.x += mVelocity.x*deltaTime;
	mPosition.y += mVelocity.y*deltaTime;
	mPosition.z += mVelocity.z*deltaTime;

	mPosition += mVelocity*deltaTime + mAccel * (0.5*deltaTime*deltaTime);
	mVelocity += mAccel*deltaTime;
	mVelocity = mVelocity*0.99;

	if (mPosition.x < 7 && mPosition.z < 4 && mPosition.z > -4 && mPosition.x > -7)
	{
		if (mPosition.y < -4)
		{
			bounced = true;
			mVelocity.y *= -0.99;
		}
	}
}

void PhysObj::translate(float x, float y, float z)
{
	glTranslatef(x, y, z);
}

void PhysObj::rotate(float a, float x, float y, float z)
{
	glRotatef(a, x, y, z);
}

void PhysObj::scale(float x, float y, float z)
{
	glScalef(x, y, z);
}

void PhysObj::bounce()
{

}

void PhysObj::setPosition(Vector3D newPos)
{
	mPosition = newPos;
}

void PhysObj::setBounced(bool newBounced)
{
	bounced = newBounced;
}

void PhysObj::render()
{
	//glBindTexture(GL_TEXTURE_2D, object.id_texture);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

#include "Dodgeball.h"
#include "PhysObj.h"
#include <stdlib.h>
#include "../gl/glut.h"
#include "Texture2D.h"
#include <string>
#include "Collision.h"
#include <iostream>
#include <SDL_mixer.h>

Dodgeball::Dodgeball(char* textureName, bool isTrail) : PhysObj()
{
	if (!isTrail)
	{
		mPosition.x = rand() % 14 - 7;
		mPosition.y = 3.5 + rand()% 1 - 0.5;
		mPosition.z = rand() % 6 - 3;

		mVelocity.x = rand() % 2-1;
		mVelocity.z = rand() % 2-1;
	}
	else
	{
		mVelocity.x = 0;
		mVelocity.z = 0;
	}

	mScale = 0.5;

	
	loadTexture(textureName, 512, 512);
	collision = new Sphere(mPosition, mScale*1.1);
	PhysObj::PhysObj();
}

Dodgeball::~Dodgeball()
{
	delete collision;
}

void Dodgeball::update(float deltaTime)
{
	PhysObj::update(deltaTime);
	collision->SetCollided(false);
	collision->Update(mPosition);
}

void Dodgeball::render() 
{
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, object.id_texture);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	
	glTranslatef(mPosition.x, mPosition.y, mPosition.z);
	glutSolidTeapot(mScale);
	//glColor3f(0.0, 0.0, 0.0);

	PhysObj::render();
	glPopMatrix();
}
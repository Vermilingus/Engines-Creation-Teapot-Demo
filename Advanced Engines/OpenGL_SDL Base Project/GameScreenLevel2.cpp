#include "GameScreenLevel2.h"
#include <time.h>
#include <windows.h>
#include <GL\gl.h>
#include <GL\glu.h>
#include "../gl/glut.h"
#include "Constants.h"
#include "Texture2D.h"
#include "Commons.h"
#include "Planet.h"
#include "Camera.h"

using namespace::std;

//--------------------------------------------------------------------------------------------------

GameScreenLevel2::GameScreenLevel2(GameScreenManager* manager) : GameScreen()
{
	srand(time(NULL));

	glEnable(GL_DEPTH_TEST);

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	float aspect = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;
	gluPerspective(60.0f, aspect, 0.1f, 1000.0f);

	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_CULL_FACE);								//Stop calculation of inside faces
	glEnable(GL_DEPTH_TEST);							//Hidden surface removal

														//clear background colour.
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glEnable(GL_TEXTURE_2D);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	Sol = new Planet(Vector3D(0.0f, 0.0f, 0.0f), "Planet.3DS");
	Sol->loadTexture("sun.raw", 512, 512);
	Mercury = new Planet(Vector3D(0.0f, 0.0f, 0.0f), "Planet.3DS");
	Venus = new Planet(Vector3D(0.0f, 0.0f, 0.0f), "Planet.3DS");
	Terra = new Planet(Vector3D(0.0f, 0.0f, 0.0f), "Planet.3DS");
	Luna = new Planet(Vector3D(0.0f, 0.0f, 0.0f), "Planet.3DS");
	Mars = new Planet(Vector3D(0.0f, 0.0f, 0.0f), "Planet.3DS");
	Jupiter = new Planet(Vector3D(0.0f, 0.0f, 0.0f), "Planet.3DS");
	Saturn = new Planet(Vector3D(0.0f, 0.0f, 0.0f), "Planet.3DS");
	SaturnRing = new Planet(Vector3D(0.0f, 0.0f, 0.0f), "PlanetRing.3DS");
	Uranus = new Planet(Vector3D(0.0f, 0.0f, 0.0f), "Planet.3DS");
	Neptune = new Planet(Vector3D(0.0f, 0.0f, 0.0f), "Planet.3DS");
	cam = new Camera();

	gameManager = manager;

	rotation = 0;
}

//--------------------------------------------------------------------------------------------------

GameScreenLevel2::~GameScreenLevel2()
{
}

//--------------------------------------------------------------------------------------------------

void GameScreenLevel2::SetLight()
{
	lighting light = {
		{ 0.2f,0.2f,0.2f,1.0f },
		{ 0.7f,0.7f,0.7f,1.0f },
		{ 0.5f,0.5f,0.5f,1.0f },
	};

	float light_pos[] = { 1.0f,1.0f,1.0f,0.0f };

	glLightfv(GL_LIGHT0, GL_AMBIENT, light.ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light.diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light.specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
}

void GameScreenLevel2::SetMaterial()
{
	material material = {
		{ 0.80f,0.05f,0.05f,1.0f },
		{ 0.80f,0.05f,0.05f,1.0f },
		{ 1.0f,1.0f,1.0f,1.0 },
		100.0f
	};

	glMaterialfv(GL_LIGHT0, GL_AMBIENT, material.ambient);
	glMaterialfv(GL_LIGHT0, GL_DIFFUSE, material.diffuse);
	glMaterialfv(GL_LIGHT0, GL_SPECULAR, material.specular);
	glMaterialf(GL_LIGHT0, GL_SHININESS, material.shininess);
}

void GameScreenLevel2::Render()
{
	//Clear the screen.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	cam->Render();
	rotation += 0.01;

	//Layer 1 of Solar System
	glPushMatrix();
	//Sun rotation and translation around own Axis
	glRotatef(rotation, 0, 1, 0);
	glTranslatef(0.0f, -30.0f, 0.0f);
	glRotatef(rotation * 12, 0, -1, 0);
	glPushMatrix();
	glScalef(0.9f, 0.9f, 0.9f);


	Sol->render();

	glPopMatrix();

	glPushMatrix();
	//Mercury rotation and translation around Sun
	glRotatef(rotation* 47.9, 0, -1, 0);
	glTranslatef(0.0f, 0.0f, 40.0f);
	glRotatef(rotation * 47, 0, -1, 0);
	glScalef(0.02f, 0.02f, 0.02f);

	Mercury->render();


	glPopMatrix();

	glPushMatrix();
	//Venus rotation and translation around Sun
	glRotatef(rotation * 35, 0, -1, 0);
	glTranslatef(0.0f, 0.0f, 50.0f);
	glRotatef(rotation * 35, 0, -1, 0);
	glScalef(0.08f, 0.08f, 0.08f);


	Venus->render();

	glPopMatrix();

	glPushMatrix();
	//Earth rotation and translation around Sun
	glRotatef(rotation*29.8f, 0, -1, 0);
	glTranslatef(0.0f, 0.0f, 70.0f);
	glRotatef(rotation * 29, 0, -1, 0);
	glScalef(0.1f, 0.1f, 0.1f);

	Terra->render();

	glPushMatrix();
	//Moon rotation and translation around Earth
	glRotatef(rotation * 1, 0, 1, 0);
	glTranslatef(0.0f, 0.0f, 70.0f);
	glRotatef(rotation * 50, 0, 1, 0);
	glScalef(0.5f, 0.5f, 0.5f);

	Luna->render();

	glPopMatrix();

	glPopMatrix();



	glPushMatrix();
	//Mars rotation and translation around Sun
	glRotatef(rotation * 4, 0, 1, 0);
	glTranslatef(0.0f, 0.0f, 85.0f);
	glRotatef(rotation * 24, 0, -1, 0);
	glScalef(0.04f, 0.04f, 0.04f);
	Mars->render();

	glPopMatrix();

	glPushMatrix();
	//Jupiter rotation and translation around Sun
	glRotatef(rotation * 2, 0, 1, 0);
	glTranslatef(0.0f, 0.0f, 110.0f);
	glRotatef(rotation * 13, 0, -1, 0);
	glScalef(0.5f, 0.5f, 0.5f);
	Jupiter->render();


	glPopMatrix();

	glPushMatrix();
	//Saturn rotation and translation around Sun
	glRotatef(rotation * 5, 0, 1, 0);
	glTranslatef(0.0f, 0.0f, 160.0f);
	glRotatef(rotation * 9.7f, 0, -1, 0);
	glScalef(0.3f, 0.3f, 0.3f);
	Saturn->render();
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	SaturnRing->render();
	glPopMatrix();

	glPopMatrix();

	glPushMatrix();
	//Uranus rotation and translation around Sun
	glRotatef(rotation * 2, 0, 1, 0);
	glTranslatef(0.0f, 0.0f, 200.0f);
	glRotatef(rotation * 6.8f, 0, -1, 0);
	glScalef(0.45f, 0.45f, 0.45f);
	Uranus->render();

	glPopMatrix();

	glPushMatrix();
	//Neptune rotation and translation around Sun
	glRotatef(rotation * 5, 0, 1, 0);
	glTranslatef(0.0f, 0.0f, 300.0f);
	glRotatef(rotation * 5.4f, 0, -1, 0);
	glScalef(0.4f, 0.4f, 0.4f);
	Neptune->render();
	glPopMatrix();

	glPopMatrix();


}

//--------------------------------------------------------------------------------------------------

void GameScreenLevel2::Update(float deltaTime, SDL_Event e)
{
	mCurrentTime += deltaTime;
	cam->Update(deltaTime, e);
	Sol->update(deltaTime);
	Mercury->update(deltaTime);
	Venus->update(deltaTime);
	Terra->update(deltaTime);
	Mars->update(deltaTime);
	Jupiter->update(deltaTime);
	Saturn->update(deltaTime);
	Uranus->update(deltaTime);
	Neptune->update(deltaTime);

	if (e.type == SDL_KEYDOWN)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_SPACE:
			gameManager->ChangeScreen(SCREEN_LEVEL1, deltaTime);
		}
	}
}

//--------------------------------------------------------------------------------------------------
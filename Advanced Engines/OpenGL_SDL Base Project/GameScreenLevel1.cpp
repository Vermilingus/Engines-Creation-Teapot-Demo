#include "GameScreenLevel1.h"
#include <time.h>
#include <windows.h>
#include <GL\gl.h>
#include <GL\glu.h>
#include "../gl/glut.h"
#include "Constants.h"
#include "Texture2D.h"
#include "Commons.h"
#include "Dodgeball.h"
#include "Camera.h"
#include "Collision.h"
#include "Denzil.h"
#include <SDL_mixer.h>

using namespace::std;

//--------------------------------------------------------------------------------------------------

GameScreenLevel1::GameScreenLevel1(GameScreenManager* manager) : GameScreen()
{

	gameManager = manager;
	spawnTimer = 0;
	timer = 0;

	srand(time(NULL));

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	float aspect = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;
	gluPerspective(60.0f,aspect,0.1f,1000.0f);

	
	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_CULL_FACE);								//Stop calculation of inside faces
	glEnable(GL_DEPTH_TEST);							//Hidden surface removal

	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);

	//clear background colour.
	glClearColor(0.5f,0.5f,1,1);

	glEnable(GL_TEXTURE_2D);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	player = new Denzil("PlanetRing.3DS",manager);
	player->loadTexture("sun.raw",512,512);

	for (int i = 0; i < 1; i++)
	{
		objects.push_back(new Dodgeball("court.raw",false));
	}

	isRunning = true;
}

//--------------------------------------------------------------------------------------------------

GameScreenLevel1::~GameScreenLevel1()
{	
}

//--------------------------------------------------------------------------------------------------

void GameScreenLevel1::SetLight()
{
	lighting light = {
		{0.2f,0.2f,0.2f,1.0f},
		{0.7f,0.7f,0.7f,1.0f},
		{0.5f,0.5f,0.5f,1.0f},
	};

	float light_pos[] = { 1.0f,1.0f,1.0f,0.0f };

	glLightfv(GL_LIGHT0, GL_AMBIENT, light.ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light.diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light.specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
}

void GameScreenLevel1::SetMaterial()
{
	material material = {
		{0.80f,0.05f,0.05f,1.0f},
		{ 0.80f,0.05f,0.05f,1.0f },
		{1.0f,1.0f,1.0f,1.0},
		100.0f
	};

	glMaterialfv(GL_LIGHT0, GL_AMBIENT, material.ambient);
	glMaterialfv(GL_LIGHT0, GL_DIFFUSE, material.diffuse);
	glMaterialfv(GL_LIGHT0, GL_SPECULAR, material.specular);
	glMaterialf(GL_LIGHT0, GL_SHININESS, material.shininess);
}

void GameScreenLevel1::Render()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	float aspect = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;
	gluPerspective(60.0f, aspect, 0.1f, 1000.0f);


	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	gluLookAt(0.0f, 5.0f, 12.0f,
		0.0f, -5.0f, -10.0f,
		0.0f, 1.0f, 0.0f);

	glPushMatrix();
	player->render();
	glPopMatrix();

	glPushMatrix();
	//cam->Render();
	for(int i = 0; i < objects.size(); i++)
	{
		objects[i]->render();
	}
	glPopMatrix();

	
	glPushMatrix();
	
	DrawCourt();
	glPopMatrix();

	gameManager->lineOut(0, 50, to_string(player->GetBalls()));
	gameManager->lineOut(0, 0, to_string(timer));

	
}



//--------------------------------------------------------------------------------------------------

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	mCurrentTime += deltaTime;
	timer += deltaTime;
	spawnTimer += deltaTime;
	if (spawnTimer >= 0.5)
	{
		objects.push_back(new Dodgeball("court.raw", false));
		spawnTimer = 0;
	}
	for (int i = 0; i < objects.size(); i++) {
		objects[i]->update(deltaTime);
	}
	player->update(deltaTime, e);
	
	int i = 0;
	while (objects.size() != i && isRunning) {

		if (objects[i]->GetTimeActive() >= 10.0f)
			{
				objects.erase(objects.begin() + i);
			}
		if (Collision::SphereSphereCollision(objects[i]->GetCollider(), player->GetCollider()))
			{
			if (player->getHit() == 0)
				{
				gameManager->ChangeScreen(SCREEN_GAMEOVER, timer);
				isRunning = false;
				
					
				}
			else
				{
					objects.erase(objects.begin() + i);
				}

					//delete objects[i];
				}
			else if (objects[i]->getBounced())
				{
					gameManager->PlaySoundEffect(0);
					objects[i]->setBounced(false);
				}
			else if ((objects[i]->getPosition().y) < -6)
				{
					objects.erase(objects.begin() + i);
					//delete objects[i];
				}

			else
				{
					i++;
				}
		}
}

void GameScreenLevel1::DrawCourt()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBindTexture(GL_TEXTURE_2D, 0);

	glPushMatrix();
	glColor3f(0.5,0.5,0.5);
	glBegin(GL_POLYGON);
	glVertex3f(-8, -4.5, 4);
	glVertex3f(8, -4.5, 4);
	glVertex3f(8, -4.5, -4);
	glVertex3f(-8, -4.5, -4);
	glEnd();
	glPopMatrix();
}
//--------------------------------------------------------------------------------------------------
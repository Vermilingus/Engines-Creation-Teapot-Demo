#include "GameScreenIntro.h"
#include <time.h>
#include <windows.h>
#include <GL\gl.h>
#include <GL\glu.h>
#include "../gl/glut.h"
#include "Constants.h"
#include "Texture2D.h"
#include "Commons.h"

using namespace::std;

//--------------------------------------------------------------------------------------------------

GameScreenIntro::GameScreenIntro(GameScreenManager* manager) : GameScreen()
{
	srand(time(NULL));

	glEnable(GL_DEPTH_TEST);

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	float aspect = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;
	gluPerspective(60.0f,aspect,0.1f,1000.0f);

	//glMatrixMode(GL_MODELVIEW);

	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);

	//clear background colour.
	glClearColor(0,0,0,0);

	glEnable(GL_TEXTURE_2D);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	gameManager = manager;
}

//--------------------------------------------------------------------------------------------------

GameScreenIntro::~GameScreenIntro()
{	

}

void GameScreenIntro::Render()
{
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	gluLookAt(0.0f, 5.0f, 12.0f,
		0.0f, -5.0f, -10.0f,
		0.0f, 1.0f, 0.0f);

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);
	gameManager->lineOut(0, 100, "Use WASD to get Denzil 'Saturn but the sun' Denzilton to the other side.");
	gameManager->lineOut(0, 50, "Get hit by 4 teapo-I mean dodgeballs and you lose.");
	gameManager->lineOut(0, 0, "Press SPACE to start.");
	glPopMatrix();
}

void GameScreenIntro::Update(float deltaTime, SDL_Event e)
{
	if (e.type == SDL_KEYDOWN)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_SPACE:
			gameManager->ChangeScreen(SCREEN_LEVEL1, deltaTime);
		}
	}
}
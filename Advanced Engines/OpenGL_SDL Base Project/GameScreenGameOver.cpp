#include "GameScreenGameOver.h"
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

GameScreenGameOver::GameScreenGameOver(GameScreenManager* manager, float finalTime) : GameScreen()
{
	srand(time(NULL));

	glEnable(GL_DEPTH_TEST);

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	float aspect = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;
	gluPerspective(60.0f, aspect, 0.1f, 1000.0f);

	//glMatrixMode(GL_MODELVIEW);

	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);

	//clear background colour.
	glClearColor(0, 0, 0, 0);

	glEnable(GL_TEXTURE_2D);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	gameManager = manager;
	timeSurvived = finalTime;
	manager->PlaySoundEffect(1);
}

//--------------------------------------------------------------------------------------------------

GameScreenGameOver::~GameScreenGameOver()
{

}

void GameScreenGameOver::Render()
{
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	gluLookAt(0.0f, 5.0f, 12.0f,
		0.0f, -5.0f, -10.0f,
		0.0f, 1.0f, 0.0f);

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);
	gameManager->lineOut(0,100, "You Lose!");
	gameManager->lineOut(0, 50, "But you did last for");
	gameManager->lineOut(170, 50, to_string(timeSurvived) + " seconds!");
	gameManager->lineOut(0, 0, "Press SPACE to restart");
	glPopMatrix();
}

void GameScreenGameOver::Update(float deltaTime, SDL_Event e)
{
	if (e.type == SDL_KEYDOWN)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_SPACE:
			gameManager->ChangeScreen(SCREEN_INTRO, deltaTime);
		}
	}
}
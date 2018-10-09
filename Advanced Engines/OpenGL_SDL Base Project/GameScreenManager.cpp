#include "GameScreenManager.h"
#include "GameScreen.h"
#include "GameScreenLevel1.h"
#include "GameScreenIntro.h"
#include "GameScreenLevel2.h"
#include "GameScreenGameOver.h"
#include "GameScreenWin.h"
#include <SDL_mixer.h>
#include "../gl/glut.h"
#include <SDL.h>
#include "Constants.h"

//--------------------------------------------------------------------------------------------------

GameScreenManager::GameScreenManager(SCREENS startScreen, GameScreenManager* GSM, Mix_Chunk* gBounce, Mix_Chunk* gScream, Mix_Chunk* gVictory)
{
	mCurrentScreen = NULL;
	self = GSM;
	soundBounce = gBounce;
	soundScream = gScream;
	soundVictory = gVictory;
	float timer = NULL;
	//Ensure the first screen is set up.
	ChangeScreen(startScreen, timer);
}

//--------------------------------------------------------------------------------------------------

GameScreenManager::~GameScreenManager()
{
	delete mCurrentScreen;
	mCurrentScreen = NULL;
}

//--------------------------------------------------------------------------------------------------

void GameScreenManager::PlaySoundEffect(int sound)
{
	switch (sound)
	{
	case 0:
		Mix_PlayChannel(-1, soundBounce, 0);
		break;

	case 1:
		Mix_PlayChannel(-1, soundScream, 0);
		break;

	case 2:
		Mix_PlayChannel(-1, soundVictory, 0);
		break;

	default:
		break;
	}
}

void GameScreenManager::lineOut(float x, float y, string text)
{
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glPushMatrix();
	gluOrtho2D(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT);
	glBindTexture(GL_TEXTURE_2D, 0);
	glColor3f(1, 1, 1);

	glRasterPos2f(x, y);
	for (int i = 0; i < text.size(); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
	}
	glPopMatrix();
}

//--------------------------------------------------------------------------------------------------

void GameScreenManager::Render()
{
	mCurrentScreen->Render();
}

//--------------------------------------------------------------------------------------------------

void GameScreenManager::Update(float deltaTime, SDL_Event e)
{
	mCurrentScreen->Update(deltaTime, e);
}

//--------------------------------------------------------------------------------------------------

void GameScreenManager::ChangeScreen(SCREENS newScreen, float time)
{
	//Clear up the old screen.
	if(mCurrentScreen != NULL)
	{
		delete mCurrentScreen;
	}

	GameScreenIntro* tempIntro;
	GameScreenLevel1* tempScreen1;
	GameScreenLevel2* tempScreen2;
	GameScreenGameOver* tempScreenOver;
	GameScreenWin* tempScreenWin;


	//Initialise the new screen.
	switch(newScreen)
	{


		case SCREEN_INTRO:
			tempIntro = new GameScreenIntro(this);
			mCurrentScreen = (GameScreen*)tempIntro;
			tempIntro = NULL;
		break;

		case SCREEN_MENU:
		break;

		case SCREEN_LEVEL1:
			tempScreen1 = new GameScreenLevel1(this);
			mCurrentScreen = (GameScreen*)tempScreen1;
			tempScreen1 = NULL;
		break;

		case SCREEN_LEVEL2:
			tempScreen2 = new GameScreenLevel2(this);
			mCurrentScreen = (GameScreen*)tempScreen2;
			tempScreen2 = NULL;
			break;
		
		case SCREEN_GAMEOVER:
			tempScreenOver = new GameScreenGameOver(this, time);
			mCurrentScreen = (GameScreen*)tempScreenOver;
			tempScreenOver = NULL;
		break;
		
		case SCREEN_WIN:
			tempScreenWin = new GameScreenWin(this);
			mCurrentScreen = (GameScreen*)tempScreenWin;
			tempScreenWin = NULL;
		break;
		
		default:
		break;
	}
}

//--------------------------------------------------------------------------------------------------
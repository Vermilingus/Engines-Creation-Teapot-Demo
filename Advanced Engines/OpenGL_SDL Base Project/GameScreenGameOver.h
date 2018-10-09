#ifndef _GAMESCREENGAMEOVER_H
#define _GAMESCREENGAMEOVER_H

#include <SDL.h>
#include "GameScreen.h"
#include "Dodgeball.h"
#include "GameScreenManager.h"
#include <vector>
#include "Camera.h"
#include "Denzil.h"
#include "GameScreen.h"

class GameScreenGameOver : GameScreen
{
	//--------------------------------------------------------------------------------------------------
public:
	GameScreenGameOver(GameScreenManager* manager, float finalTime);
	~GameScreenGameOver();

	//bool		SetUpLevel();
	void		Render();
	void		Update(float deltaTime, SDL_Event e);


	//--------------------------------------------------------------------------------------------------
private:
	GameScreenManager * gameManager;
	float timeSurvived;
};



#endif //_GAMESCREENLEVEL1_H#pragma once

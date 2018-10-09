#ifndef _GAMESCREENWIN_H
#define _GAMESCREENWIN_H

#include <SDL.h>
#include "GameScreen.h"
#include "Dodgeball.h"
#include "GameScreenManager.h"
#include <vector>
#include "Camera.h"
#include "Denzil.h"
#include "GameScreen.h"

class GameScreenWin : GameScreen
{
	//--------------------------------------------------------------------------------------------------
public:
	GameScreenWin(GameScreenManager* manager);
	~GameScreenWin();

	//bool		SetUpLevel();
	void		Render();
	void		Update(float deltaTime, SDL_Event e);


	//--------------------------------------------------------------------------------------------------
private:
	GameScreenManager * gameManager;
	float timeSurvived;

};



#endif //_GAMESCREENLEVEL1_H
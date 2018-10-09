#ifndef _GAMESCREENINTRO_H
#define _GAMESCREENINTRO_H

#include <SDL.h>
#include "GameScreen.h"
#include "Dodgeball.h"
#include "GameScreenManager.h"
#include <vector>
#include "Camera.h"
#include "Denzil.h"
#include "GameScreen.h"

class GameScreenIntro : GameScreen
{
//--------------------------------------------------------------------------------------------------
public:
	GameScreenIntro(GameScreenManager* manager);
	~GameScreenIntro();

	//bool		SetUpLevel();
	void		Render();
	void		Update(float deltaTime, SDL_Event e);


//--------------------------------------------------------------------------------------------------
private:
	GameScreenManager * gameManager;
};



#endif //_GAMESCREENLEVEL1_H
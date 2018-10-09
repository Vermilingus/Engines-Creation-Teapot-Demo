#ifndef _GAMESCREENLEVEL2_H
#define _GAMESCREENLEVEL2_H

#include <SDL.h>
#include "GameScreen.h"
#include "GameScreenManager.h"
#include "Planet.h"
#include "Camera.h"

class GameScreenLevel2 : GameScreen
{
	//--------------------------------------------------------------------------------------------------
public:
	GameScreenLevel2(GameScreenManager* manager);
	~GameScreenLevel2();

	bool		SetUpLevel();
	void		Render();
	void		Update(float deltaTime, SDL_Event e);

	void		SetLight();
	void		SetMaterial();

	//--------------------------------------------------------------------------------------------------
private:

	float mCurrentTime;
	float rotation;

	Planet* Sol;
	Planet* Mercury;
	Planet* Venus;
	Planet* Terra;
	Planet* Luna;
	Planet* Mars;
	Planet* Jupiter;
	Planet* Saturn;
	Planet* SaturnRing;
	Planet* Uranus;
	Planet* Neptune;
	Camera* cam;

	GameScreenManager* gameManager;
};


#endif //_GAMESCREENLEVEL1_H
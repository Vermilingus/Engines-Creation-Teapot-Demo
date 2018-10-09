#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H

#include <SDL.h>
#include "GameScreen.h"
#include "Dodgeball.h"
#include "GameScreenManager.h"
#include <vector>
#include "Camera.h"
#include "Denzil.h"
#include "GameScreen.h"

class GameScreenLevel1 : GameScreen
{
//--------------------------------------------------------------------------------------------------
public:
	GameScreenLevel1(GameScreenManager* manager);
	~GameScreenLevel1();

	//bool		SetUpLevel();
	void		Render();
	void		Update(float deltaTime, SDL_Event e);

	void		SetLight();
	void		SetMaterial();
	void		DrawCourt();


//--------------------------------------------------------------------------------------------------
private:
	
	float mCurrentTime;

	vector<Dodgeball*> objects;

	Camera* cam;

	float spawnTimer;
	float timer;

	Denzil* player;

	GameScreenManager* gameManager;
	bool isRunning;
};



#endif //_GAMESCREENLEVEL1_H
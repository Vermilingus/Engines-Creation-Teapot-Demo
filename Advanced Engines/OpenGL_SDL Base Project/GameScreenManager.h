#ifndef _GAMESCREENMANAGER_H
#define _GAMESCREENMANAGER_H

#include <SDL.h>
#include <vector>
#include "Commons.h"
#include <SDL_mixer.h>
#include <string>

class GameScreen;

class GameScreenManager
{
public:
	GameScreenManager(SCREENS startScreen, GameScreenManager* GSM, Mix_Chunk* gBounce, Mix_Chunk* gScream, Mix_Chunk* gVictory);
	~GameScreenManager();

	void Render();
	void Update(float deltaTime, SDL_Event e);

	void ChangeScreen(SCREENS newScreen, float time);

	void PlaySoundEffect(int sound);
	void lineOut(float x, float y, std::string text);

private:
	GameScreen* mCurrentScreen;
	GameScreenManager* self;

	Mix_Chunk* soundBounce;
	Mix_Chunk* soundScream;
	Mix_Chunk* soundVictory;
};


#endif //_GAMESCREENMANAGER_H
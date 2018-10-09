#ifndef _DENZIL_H_
#define _DENZIL_H_

#include "Commons.h"
#include <string>
#include "PhysObj.h"
#include <SDL.h>
#include <vector>
#include "Dodgeball.h"
#include "GameScreenManager.h"

using std::string;

class Denzil : public PhysObj
{
public:
	Denzil(string modelFileName, GameScreenManager* GSM);
	~Denzil() {}

	void update(float deltaTime, SDL_Event e);
	void render();

	void loadModel();

	void translate(float x, float y, float z);
	void rotate(float a, float x, float y, float z);

	void loadTexture(char* path, int width, int height);
	int getHit();
	int GetBalls();

protected:
	vector<Dodgeball*> trail;
	int hitsLeft;
	GameScreenManager* manager;
	int trailStepCounter;
	Vector3D pos10;
	Vector3D pos20;
	Vector3D pos30;
	vector<Vector3D> prevPositions;
};

#endif

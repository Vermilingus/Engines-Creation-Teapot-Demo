#ifndef _DODGEBALL_H_
#define _DODGEBALL_H_

#include "PhysObj.h"

using namespace std;

class Dodgeball: public PhysObj
{
public:
	Dodgeball(char* texName, bool isTrail);
	~Dodgeball();

	void update(float deltaTime);
	void render();

};

#endif
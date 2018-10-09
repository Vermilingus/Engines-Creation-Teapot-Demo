#ifndef _PLANET_H_
#define _PLANET_H_

#include "Commons.h"
#include <string>

using std::string;

class Planet
{
public:
	Planet(Vector3D startPosition, string modelFileName);
	~Planet() {}

	void update(float deltaTime);
	void render();

	void loadModel();

	void translate(float x, float y, float z);
	void rotate(float a, float x, float y, float z);

	void loadTexture(char* texture, int width, int height);

private:
	Vector3D mPosition;

	char fileName[20];
	char textureName[20];

	obj_type object;
};

#endif

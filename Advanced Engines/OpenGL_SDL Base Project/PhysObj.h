#ifndef _PhysObj_H_
#define _PhysObj_H_
#include "Commons.h"
#include <string>

using namespace std;

class Sphere;

class PhysObj
{
public:
	PhysObj();
	~PhysObj() {}

	void update(float deltaTime);
	void render();

	void translate(float x, float y, float z);
	void rotate(float a, float x, float y, float z);
	void scale(float x, float y, float z);
	void bounce();
	void loadTexture(char* texture, int width, int height);

	Vector3D getPosition() { return mPosition; };
	Vector3D getVelocity() { return mVelocity; };
	bool getBounced() { return bounced; };
	Sphere* GetCollider() {return collision;}
	void setBounced(bool newBounced);
	float GetTimeActive() { return timeActive; };

	void setPosition(Vector3D newPos);
	
protected:
	Vector3D mPosition;
	Vector3D mVelocity;
	Vector3D mAccel;
	float mScale;

	char fileName[20];
	char textureName[20];

	obj_type object;
	Sphere * collision;

	bool bounced;
	float timeActive;
};

#endif

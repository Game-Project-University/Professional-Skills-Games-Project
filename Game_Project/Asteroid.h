#pragma once

#include "Global.h"
//#include "AsteroidFireSystem.h"
#include "Player.h"

class CAsteroid
{
public:
	static IMesh* asteroidMsh;
	static IMesh* outerMsh;
	IModel* GetModel();
	float GenerateRandomFloat(float, float);
	void ResetAsteroidPosition();
	void Update(float, CPlayer*);
	CAsteroid();
	~CAsteroid();
private:
	IModel* asteroidMdl;
	IModel* outerMdl;
	//CAsteroidFireSystem* assFire;
	float skyX;
	float skyY;
	float skyZ;
	float fallSpeed;
	bool asteroidPositionReset;
};
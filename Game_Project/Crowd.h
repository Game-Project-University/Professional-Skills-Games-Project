#pragma once

#include "Object.h"
#include "Player.h"
class CCrowd
{
public:
	CCrowd(float x, float y, float z);
	~CCrowd();
	static IMesh* crowdMsh;
	void update(float frametime, CPlayer* playerPtr);

private:
	IModel* crowdMdl[4];
	float originX;
	float originY;
	float originZ;
};
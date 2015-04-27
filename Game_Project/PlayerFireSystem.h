#pragma once

#include "BaseParticle.h"
#include "Player.h"

const int fireNo = 200;
class CFireSystem : CBaseParticle
{
public:
	CFireSystem();
	~CFireSystem();

	static IMesh* particleMsh;
	void update(float frametime, CPlayer* playerPtr);
private:

	SParticle particleArray[fireNo];

};
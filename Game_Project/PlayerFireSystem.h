#pragma once

#include "BaseParticle.h"
#include "Player.h"
#include "AI.h"

const int fireNo = 200;
class CFireSystem : CBaseParticle
{
public:
	CFireSystem();
	~CFireSystem();

	static IMesh* particleMsh;

	void update(float frametime, CPlayer* playerPtr);
	void updateAi(float frametime, CAI* playerPtr, ICamera* camera);
private:

	SParticle particleArray[fireNo];

};
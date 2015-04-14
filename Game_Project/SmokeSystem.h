#pragma once

#include "BaseParticle.h"
#include "Player.h"

const int AMOUNT_OF_PARTICLES = 200;
class CSmokeSystem : CBaseParticle
{
public:
	CSmokeSystem();
	~CSmokeSystem();

	static IMesh* particleMsh;
	void update(float frametime, CPlayer* playerPtr);
private:

	SParticle particleArray[AMOUNT_OF_PARTICLES];

};
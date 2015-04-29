#pragma once

#include "Baseparticle.h"
#include "Player.h"

const int AMOUNT_OF_ASS_FIRE = 15;

class CAsteroidFireSystem : CBaseParticle
{
public:
	static IMesh* assFireParticleMsh;
	CAsteroidFireSystem();
	~CAsteroidFireSystem();
	void update(float frameTime, IModel* ass, CPlayer* playerPtr);
	void MoveOffTheTrack();
private:
	SParticle assFireParticleArray[AMOUNT_OF_ASS_FIRE];
};
#pragma once

#include "Global.h"

class CBaseParticle
{
public:
	CBaseParticle();
	~CBaseParticle();

	// random function 
	float random(int rangeMin, int rangeMax);

private:


protected:
	struct SParticle
	{
		IModel* mPartMdl;
		float mDirX;
		float mDirY;
		float mDirZ;
		float mLifeTime;
		float mVelocity;
		float mlifeSpan;
	};

};

#include "BaseParticle.h"

CBaseParticle::CBaseParticle()
{
	
}

CBaseParticle::~CBaseParticle()
{
}

float CBaseParticle::random(int rangeMin, int rangeMax)
{
	float result = (float)rand() / (float)(RAND_MAX + 1);
	result *= (float)(rangeMax - rangeMin);
	result += rangeMin;

	return result;
}

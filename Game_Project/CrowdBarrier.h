#pragma once

#include "Object.h"

class CCrowdBarrier : public CObject
{
public:
	CCrowdBarrier(float x, float y, float z, float width, float length, bool rotated);
	~CCrowdBarrier();

	static IMesh* crowdBarrierMsh;

private:
};
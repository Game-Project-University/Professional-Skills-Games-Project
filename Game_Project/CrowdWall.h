#pragma once

#include "Object.h"

class CCrowdWall : public CObject
{
public:
	CCrowdWall(float x, float y, float z, float width, float length, bool rotated);
	~CCrowdWall();

	static IMesh* crowdWallMsh;

private:
};
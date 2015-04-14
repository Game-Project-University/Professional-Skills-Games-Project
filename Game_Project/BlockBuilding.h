#pragma once

#include "Object.h"

class CBlockBuilding : public CObject
{
public:
	CBlockBuilding(float x, float y, float z, float width, float length);
	~CBlockBuilding();

	static IMesh* blockBuildingMsh;

private:
};
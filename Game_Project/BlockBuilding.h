#pragma once

#include "Object.h"
#include "Global.h"

class CBlockBuilding : public CObject
{
public:
	CBlockBuilding(float x, float y, float z, float width, float length);
	~CBlockBuilding();

private:
	IMesh* blockBuildingMsh;
};
#pragma once

#include "Object.h"

class CPadBuilding : public CObject
{
public:
	CPadBuilding(float x, float y, float z, float width, float length);
	~CPadBuilding();

	static IMesh* padBuildingMsh;
private:
	
};
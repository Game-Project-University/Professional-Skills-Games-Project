#pragma once

#include "Object.h"

class CBattleShip : public CObject
{
public:
	CBattleShip(float x, float y, float z, float width, float length);
	~CBattleShip();

private:
	IMesh* battleShipMsh;

};
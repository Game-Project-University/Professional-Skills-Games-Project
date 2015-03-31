#pragma once
#include "Object.h"
#include "SkyScraper.h"
#include "BlockBuilding.h"
#include "Player.h"
#include "Global.h"

const int NUMBER_OF_OBJECTS = 9;
class CTrack
{
public:
	CTrack();
	~CTrack();

	void Collision(CPlayer* cPlayer);
private:
	CObject* courseObjects[NUMBER_OF_OBJECTS];


};
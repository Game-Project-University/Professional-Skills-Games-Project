#pragma once
#include "Object.h"
#include "SkyScraper.h"
#include "BlockBuilding.h"
#include "Battleship.h"
#include "Player.h"
#include "Checkpoint.h"
#include "Global.h"

const int NUMBER_OF_OBJECTS = 11;
const int NUMBER_OF_CHECKPOINTS = 2;

class CTrack
{
public:
	CTrack();
	~CTrack();

	void Collision(CPlayer* cPlayer);
private:
	CObject* courseObjects[NUMBER_OF_OBJECTS];
	CCheckpoint* courseCheckpoints[NUMBER_OF_CHECKPOINTS];
};
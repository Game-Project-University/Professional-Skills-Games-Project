#pragma once
#include "Object.h"
#include "SkyScraper.h"
#include "BlockBuilding.h"
#include "Battleship.h"
#include "Player.h"
#include "Checkpoint.h"

const int NUMBER_OF_OBJECTS = 11;
const int NUMBER_OF_CHECKPOINTS = 2;

class CTrack
{
public:
	CTrack();
	~CTrack();

	void ObjectCollision(CPlayer* cPlayer);
	void CheckPointCollision(CPlayer* cPlayer);


	template <class T,class S> bool SphereToSphereCollision(T* cPLayer, S* cCheckPoints, float radius1, float radius2);

private:
	CObject* courseObjects[NUMBER_OF_OBJECTS];
	CCheckpoint* courseCheckpoints[NUMBER_OF_CHECKPOINTS];

	int checkPoint;
	int lap;
};
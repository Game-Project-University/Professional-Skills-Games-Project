#pragma once
#include "Object.h"
#include "SkyScraper.h"
#include "BlockBuilding.h"
#include "Battleship.h"
#include "Player.h"
#include "AI.h"
#include "Checkpoint.h"
#include "Sound.h"
#include "BaseItem.h"
#include "PadBuilding.h"
#include "Vortex.h"
#include "Wallh.h"
#include "Health.h"
#include "Shield.h"
#include "Speed.h"

const int NUMBER_OF_OBJECTS = 37;
const int NUMBER_OF_CHECKPOINTS = 5;
const int NUMBER_OF_ITEMS = 3;
const int NUMBER_OF_VORTEX = 4;

class CTrack
{
public:
	CTrack();
	~CTrack();

	static IMesh* HeartMsh;
	static IMesh* SpeedMsh;
	static IMesh* SheildMsh;

	void ObjectCollision(CPlayer* cPlayer, CAI* cAI[], CSound* sound, CSound* explosion);
	void CheckPointCollision(CPlayer* cPlayer);
	void ItemCollision(CPlayer* cPlayer, CSound* sound);

	// template class for spheretospherecollision so that this function can be used on any objects
	template <class T,class S> bool SphereToSphereCollision(T* cPLayer, S* cCheckPoints, float radius1, float radius2);
	
	//-- GETTER FUNCTIONS --//
	// return the checkpoint that has mostly recently been passed
	inline int GetCheckpoint(){ return checkPoint; };
	// return the lap that the player is on
	inline int GetLap(){ return lap; };

	void ResetPlayerPosition(CPlayer* cPlayer);
	void TrackUpdate(float frameTime);
	void OwnedItems(CPlayer* cPlayer);


private:
	CObject* courseObjects[NUMBER_OF_OBJECTS];
	CCheckpoint* courseCheckpoints[NUMBER_OF_CHECKPOINTS];
	CBaseItem* courseItems[NUMBER_OF_ITEMS];
	CVortex* vortexObjects[NUMBER_OF_VORTEX];

	int checkPoint;
	int lap;

	
};
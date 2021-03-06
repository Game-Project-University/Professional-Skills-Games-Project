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
#include "Crowd.h"
#include "CrowdBarrier.h"
#include "CrowdWall.h"
#include "Arrow.h"
#include "gun.h"
#include "Asteroid.h"

const int NUMBER_OF_OBJECTS = 91;
const int NUMBER_OF_CHECKPOINTS = 7;
const int NUMBER_OF_ITEMS = 9;
const int NUMBER_OF_VORTEX = 4;
const int NUMBER_OF_CROWDS = 18;
const int NUMBER_OF_ARROWS = 12;
const int NUMBER_OF_ASTEROIDS = 15;
const int MAXLAPS = 3;

class CTrack
{
public:
	CTrack();
	~CTrack();

	static IMesh* HeartMsh;
	static IMesh* SpeedMsh;
	static IMesh* SheildMsh;
	static IMesh* DummyMsh;

	stringstream interfaceText;
	IFont* font;

	string ItemShow;

	bool playerAi;
	bool aiPlayer;

	void ObjectCollision(CPlayer* cPlayer, CAI* cAI[], CSound* sound, CSound* explosion, CSound* use);
	void CheckPointCollision(CBasePlayer* cPlayer,CAI* cAi[]);
	void ItemCollision(CPlayer* cPlayer, CSound* sound);
	void AICollision(CPlayer* cPlayer, CAI* cAI[], CSound* sound);
	void RacePosition(CPlayer* cPlayer, CAI* cAI[]);

	// template class for spheretospherecollision so that this function can be used on any objects
	template <class T,class S> bool SphereToSphereCollision(T* cPLayer, S* cCheckPoints, float radius1, float radius2);

	bool bulletToAICollision(float BulletX, float BulletZ, CAI* ai, float radius1, float radius2);
	
	//-- GETTER FUNCTIONS --//
	// return the checkpoint that has mostly recently been passed
	// return the lap that the player is on

	void ResetPlayerPosition(CBasePlayer* cPlayer);
	void TrackUpdate(float frameTime, CPlayer* cPlayer, bool asteroidStormActive, CSound* asteroidHit);
	void OwnedItems(CPlayer* cPlayer, CSound* sound);

	void DisplayItemHeld();

	bool itemHeld;

	template <class T, class S> float dotProduct(T* mdl1, S* mdl2);
	template <class T, class S> float distance(T* mdl1, S* mdl2);

private:
	CObject* courseObjects[NUMBER_OF_OBJECTS];
	CCheckpoint* courseCheckpoints[NUMBER_OF_CHECKPOINTS];
	CBaseItem* courseItems[NUMBER_OF_ITEMS];
	CVortex* vortexObjects[NUMBER_OF_VORTEX];
	CCrowd* crowdObjects[NUMBER_OF_CROWDS];
	CArrow* arrowObjects[NUMBER_OF_ARROWS];
	CAsteroid* asteroidObjects[NUMBER_OF_ASTEROIDS];
	//IModel* FixLookObjects[NUMBER_OF_CHECKPOINTS];
};
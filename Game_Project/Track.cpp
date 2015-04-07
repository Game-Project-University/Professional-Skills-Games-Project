#include "Track.h"

CTrack::CTrack()
{
	//-- checkpoints and laps variables to show on interface and track players progress
	checkPoint = 0;
	lap = 0;

	//-- creation of objects (x, y, z, width, height)
	//-- i will make this read in from a file eventually
	courseObjects[0] = new CSkyScraper(-40.0f,0.0f,60.0f, 52.0f, 54.0f);
	courseObjects[1] = new CSkyScraper(40.0f, 0.0f, 60.0f, 52.0f, 54.0f);
	courseObjects[2] = new CSkyScraper(-40.0f, 0.0f, 0.0f, 52.0f, 54.0f);
	courseObjects[3] = new CSkyScraper(40.0f, 0.0f, 0.0f, 52.0f, 54.0f);
	courseObjects[4] = new CSkyScraper(-40.0f, 0.0f, 120.0f, 52.0f, 54.0f);
	courseObjects[5] = new CSkyScraper(40.0f, 0.0f, 120.0f, 52.0f, 54.0f);
	courseObjects[6] = new CBlockBuilding(36.0f, 0.0f, 170.0f, 40.0f, 54.0f);
	courseObjects[7] = new CBlockBuilding(0.0f, 0.0f, 210.0f, 40.0f, 54.0f);
	courseObjects[8] = new CBlockBuilding(-30.0f, 0.0f, 210.0f, 40.0f, 54.0f);
	courseObjects[9] = new CBlockBuilding(-85.0f, 0.0f, 120.0f, 40.0f, 54.0f);
	courseObjects[10] = new CBattleShip(-130.0f, 15.0f, 200.0f, 20.0f, 170.0f);

	//-- checkpoint creation (x, y, y, wether the checkpoint is to be rotated or not)
	courseCheckpoints[0] = new CCheckpoint(0, 0, 30, false);
	courseCheckpoints[1] = new CCheckpoint(0, 0, 120, false);
	courseCheckpoints[2] = new CCheckpoint(0, 0, 260, true);
	courseCheckpoints[3] = new CCheckpoint(70, 0, 260, true);

}

CTrack::~CTrack()
{
	// delte the course objects
	for (int i = 0; i < NUMBER_OF_OBJECTS; i++)
	{
		delete(courseObjects[i]);
	}
	
}

//-- AABB COLLISION
void CTrack::ObjectCollision(CPlayer* cPlayer)
{
	// check for collision using AABB
	// count through and array of objects
	for (int i = 0; i < NUMBER_OF_OBJECTS; i++)
	{
		if (cPlayer->GetPlayerPos().posX > courseObjects[i]->GetBoundaries().minX && cPlayer->GetPlayerPos().posX < courseObjects[i]->GetBoundaries().maxX &&
			cPlayer->GetPlayerPos().posZ > courseObjects[i]->GetBoundaries().minZ && cPlayer->GetPlayerPos().posZ < courseObjects[i]->GetBoundaries().maxZ)
		{
			cPlayer->SetMovementSpeed(-20);
			cPlayer->MoveBeforeCollision();
			cPlayer->DecreaseHealth(20);
		}
	}

	for (int i = 0; i < NUMBER_OF_CHECKPOINTS; i++)
	{
		//-- check for collision with the left boundarie of the checkpoints
		if (cPlayer->GetPlayerPos().posX > courseCheckpoints[i]->GetLBoundarie().minX && cPlayer->GetPlayerPos().posX < courseCheckpoints[i]->GetLBoundarie().maxX &&
			cPlayer->GetPlayerPos().posZ > courseCheckpoints[i]->GetLBoundarie().minZ && cPlayer->GetPlayerPos().posZ < courseCheckpoints[i]->GetLBoundarie().maxZ)
		{
			cPlayer->SetMovementSpeed(0);
			cPlayer->MoveBeforeCollision();
		}

		//-- check for collision with the right boundarie of the checkpoints
		if (cPlayer->GetPlayerPos().posX > courseCheckpoints[i]->GetRBoundarie().minX && cPlayer->GetPlayerPos().posX < courseCheckpoints[i]->GetRBoundarie().maxX &&
			cPlayer->GetPlayerPos().posZ > courseCheckpoints[i]->GetRBoundarie().minZ && cPlayer->GetPlayerPos().posZ < courseCheckpoints[i]->GetRBoundarie().maxZ)
		{
			cPlayer->SetMovementSpeed(0);
			cPlayer->MoveBeforeCollision();
		}
	}
}
//-- CHECKPOINT COLLISION --//
void CTrack::CheckPointCollision(CPlayer* cPlayer)
{
	for (int i = 0; i < NUMBER_OF_CHECKPOINTS; i++)
	{
		if (SphereToSphereCollision(cPlayer, courseCheckpoints[i], 10.0f, 60.0f))
		{
			if (checkPoint == i)
			{
				checkPoint++;
			}

			if (checkPoint == NUMBER_OF_CHECKPOINTS)
			{
				checkPoint = 0;
				lap++;
			}
		}
	}
}

//-- SPHERE TO SPHERE COLLISION --//
template <class T, class S> bool CTrack::SphereToSphereCollision(T* cPLayer, S* cCheckPoints, float radius1, float radius2)
{
	float distX = cPLayer->GetPlayerX() - cCheckPoints->GetCheckPointX();
	float distZ = cPLayer->GetPlayerZ() - cCheckPoints->GetCheckPointZ();
	
	return distX*distX + distZ*distZ <= radius1*2 + radius2*2;
}

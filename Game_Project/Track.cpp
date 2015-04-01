#include "Track.h"

CTrack::CTrack()
{
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

	courseCheckpoints[0] = new CCheckpoint(0, 0, 30, false);
	courseCheckpoints[1] = new CCheckpoint(0, 0, 120, true);

}

CTrack::~CTrack()
{
	// delte the course objects
	for (int i = 0; i < NUMBER_OF_OBJECTS; i++)
	{
		delete(courseObjects[i]);
	}
	
}

void CTrack::Collision(CPlayer* cPlayer)
{
	// check for collision using AABB
	// count through and array of objects
	for (int i = 0; i < NUMBER_OF_OBJECTS; i++)
	{
		if (cPlayer->GetPlayerPos().posX > courseObjects[i]->GetBoundaries().minX && cPlayer->GetPlayerPos().posX < courseObjects[i]->GetBoundaries().maxX &&
			cPlayer->GetPlayerPos().posZ > courseObjects[i]->GetBoundaries().minZ && cPlayer->GetPlayerPos().posZ < courseObjects[i]->GetBoundaries().maxZ)
		{
			cPlayer->SetMovementSpeed(0);
			cPlayer->MoveBeforeCollision();
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
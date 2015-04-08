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
	courseCheckpoints[0] = new CCheckpoint(0, 0, 0, false);
	courseCheckpoints[1] = new CCheckpoint(0, 0, 120, false);
	courseCheckpoints[2] = new CCheckpoint(0, 0, 260, true);
	courseCheckpoints[3] = new CCheckpoint(70, 0, 260, true);

	//-- Items
	IMesh* itemMsh = myEngine->LoadMesh("Sphere.x");
	courseItems[0] = new CBaseItem(itemMsh, 90, 0, 0, 0);
}

CTrack::~CTrack()
{
	// delte the course objects
	for (int i = 0; i < NUMBER_OF_OBJECTS; i++)
	{
		delete(courseObjects[i]);
	}
}

void CTrack::TrackUpdate(float frameTime)
{
	courseItems[0]->SinHoverMovement(frameTime);
}

//-- AABB COLLISION
void CTrack::ObjectCollision(CPlayer* cPlayer, CSound* sound, CSound* explostion)
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

			if (cPlayer->GetPlayerHealth() > 0)
			{
				sound->PlaySound();
			}
			else
			{
				explostion->PlaySound();
			}
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

//-- Reset the players position to the last checkpoint when player dies

void CTrack::ResetPlayerPosition(CPlayer* cPlayer)
{
	// if the checkpoint is = to 0 eg the starting checkpoint then when the car blows up reset the cars position to this checkpoint 
	if (checkPoint == 0)
	{
		cPlayer->GetModel()->SetPosition(courseCheckpoints[0]->GetX(), 0.0f, courseCheckpoints[0]->GetZ());
	}
	// set the cars position to the last checkpoint that the player drove through 
	else
	{
		cPlayer->GetModel()->SetPosition(courseCheckpoints[checkPoint - 1]->GetX(), 0.0f, courseCheckpoints[checkPoint - 1]->GetZ());
	}
}

//-- CHECKPOINT COLLISION --//
void CTrack::CheckPointCollision(CPlayer* cPlayer)
{
	for (int i = 0; i < NUMBER_OF_CHECKPOINTS; i++)
	{
		// (playerpos, checkpoint position, radious of player, radious of checkpoint)
		if (SphereToSphereCollision(cPlayer, courseCheckpoints[i], 10.0f, 60.0f))
		{
			if (checkPoint == i)
			{
				checkPoint++;
			}
			// if the checkpoint is equal to the number of checkpoints (so the lap is nearly complete) then when the collision happens with the starting checkpoint increment the lap variable
			if (checkPoint == NUMBER_OF_CHECKPOINTS && SphereToSphereCollision(cPlayer, courseCheckpoints[0], 10.0f, 60.0f))
			{
				checkPoint = 0;
				lap++;
			}
		}
	}
}

//-- ITEM COLLISION --//
void CTrack::ItemCollision(CPlayer* cPlayer, CSound* sound)
{
	for (int i = 0; i < NUMBER_OF_ITEMS; i++)
	{
		if(courseItems[i]->GetState() == false)
		{
			if (SphereToSphereCollision(cPlayer, courseItems[i], 5.0f, 5.0f))
			{
				sound->PlaySound();
				courseItems[i]->Collide();
			}
		}
	}
}

//-- SPHERE TO SPHERE COLLISION --//
template <class T, class S> bool CTrack::SphereToSphereCollision(T* cPLayer, S* cCheckPoints, float radius1, float radius2)
{
	float distX = cPLayer->GetPlayerX() - cCheckPoints->GetX();
	float distZ = cPLayer->GetPlayerZ() - cCheckPoints->GetZ();
	
	return distX*distX + distZ*distZ <= radius1*2 + radius2*2;
}
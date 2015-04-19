#include "Track.h"

IMesh* CTrack::itemMsh = nullptr;
CTrack::CTrack()
{
	//-- checkpoints and laps variables to show on interface and track players progress
	checkPoint = 0;
	lap = 0;

	//-- creation of objects (x, y, z, width, height)
	//-- i will make this read in from a file eventually
	courseObjects[0]  = new CSkyScraper(-40.0f,0.0f,60.0f, 52.0f, 54.0f);
	courseObjects[1]  = new CSkyScraper(40.0f, 0.0f, 60.0f, 52.0f, 54.0f);
	courseObjects[2]  = new CSkyScraper(-40.0f, 0.0f, 0.0f, 52.0f, 54.0f);
	courseObjects[3]  = new CSkyScraper(40.0f, 0.0f, 0.0f, 52.0f, 54.0f);
	courseObjects[4]  = new CSkyScraper(-40.0f, 0.0f, 120.0f, 52.0f, 54.0f);
	courseObjects[5]  = new CSkyScraper(40.0f, 0.0f, 120.0f, 52.0f, 54.0f);
	courseObjects[6]  = new CBlockBuilding(36.0f, 0.0f, 170.0f, 40.0f, 54.0f);
	courseObjects[7]  = new CBlockBuilding(0.0f, 0.0f, 210.0f, 40.0f, 54.0f);
	courseObjects[8]  = new CBlockBuilding(-30.0f, 0.0f, 210.0f, 40.0f, 54.0f);
	courseObjects[9]  = new CBlockBuilding(-85.0f, 0.0f, 120.0f, 40.0f, 54.0f);
	courseObjects[10] = new CBattleShip(-130.0f, 20.0f, 200.0f, 20.0f, 170.0f);
	courseObjects[11] = new CPadBuilding(-100.0f, -5.0f, 310.0f, 90.0f, 60.0f);
	courseObjects[12] = new CBlockBuilding(-30.0f, 0.0f, 310.0f, 40.0f, 54.0f);
	courseObjects[13] = new CBlockBuilding(10.0f, 0.0f, 310.0f, 40.0f, 54.0f);
	courseObjects[14] = new CBlockBuilding(50.0f, 0.0f, 210.0f, 40.0f, 54.0f);
	courseObjects[15] = new CBlockBuilding(50.0f, 0.0f, 310.0f, 40.0f, 54.0f);
	courseObjects[16] = new CWall(320.0f, 0.0f, 280.0f, 18.0f, 10.0f, true);
	courseObjects[17] = new CWall(320.0f, 0.0f, 240.0f, 18.0f, 10.0f, true);
	courseObjects[18] = new CWall(340.0f, 0.0f, 280.0f, 18.0f, 10.0f, true);
	courseObjects[19] = new CWall(340.0f, 0.0f, 240.0f, 18.0f, 10.0f, true);
	courseObjects[20] = new CWall(360.0f, 0.0f, 280.0f, 18.0f, 10.0f, true);
	courseObjects[21] = new CWall(360.0f, 0.0f, 240.0f, 18.0f, 10.0f, true);
	courseObjects[22] = new CWall(380.0f, 0.0f, 280.0f, 18.0f, 10.0f, true);
	courseObjects[23] = new CWall(380.0f, 0.0f, 240.0f, 18.0f, 10.0f, true);
	courseObjects[24] = new CWall(400.0f, 0.0f, 280.0f, 18.0f, 10.0f, true);
	courseObjects[25] = new CWall(420.0f, 0.0f, 280.0f, 18.0f, 10.0f, true);
	courseObjects[26] = new CWall(440.0f, 0.0f, 280.0f, 18.0f, 10.0f, true);
	courseObjects[27] = new CWall(450.0f, 0.0f, 280.0f, 10.0f, 18.0f, false);
	courseObjects[28] = new CWall(450.0f, 0.0f, 260.0f, 10.0f, 18.0f, false);
	courseObjects[29] = new CWall(450.0f, 0.0f, 240.0f, 10.0f, 18.0f, false);
	courseObjects[30] = new CWall(450.0f, 0.0f, 220.0f, 10.0f, 18.0f, false);
	courseObjects[31] = new CWall(390.0f, 0.0f, 230.0f, 10.0f, 18.0f, false);
	courseObjects[32] = new CWall(390.0f, 0.0f, 210.0f, 10.0f, 18.0f, false);
	courseObjects[33] = new CSkyScraper(360.0f, 0.0f, 200.0f, 52.0f, 54.0f);
	courseObjects[34] = new CSkyScraper(480.0f, 0.0f, 200.0f, 52.0f, 54.0f);
	courseObjects[35] = new CBlockBuilding(500.0f, 0.0f, -250.0f, 40.0f, 840.0f);
	courseObjects[35]->ScaleZ(15);
	courseObjects[35]->ScaleY(6);
	courseObjects[36] = new CBlockBuilding(350.0f, 0.0f, -250.0f, 40.0f, 840.0f);
	courseObjects[36]->ScaleZ(15);
	courseObjects[36]->ScaleY(6);
	//-- vortex 1
	vortexObjects[0] = new CVortex(110.0f, 10.0f, 260.0f, false);
	vortexObjects[0]->Scale(2);
	vortexObjects[1] = new CVortex(300.0f, 10.0f, 260.0f, false);

	// vortex2
	vortexObjects[2] = new CVortex(425.0f, 50.0f, -700.0f, true);
	vortexObjects[2]->Scale(5);
	vortexObjects[3] = new CVortex(0.0f, 5.0f, -300.0f, true);

	//-- checkpoint creation (x, y, y, wether the checkpoint is to be rotated or not)
	courseCheckpoints[0] = new CCheckpoint(0, 0, 0, false);
	courseCheckpoints[1] = new CCheckpoint(0, 0, 120, false);
	courseCheckpoints[2] = new CCheckpoint(-20, 0, 260, true);
	courseCheckpoints[3] = new CCheckpoint(70, 0, 260, true);
	courseCheckpoints[4] = new CCheckpoint(420, 0, 200, false);

	//-- Items
	//IMesh* itemMsh = myEngine->LoadMesh("Sphere.x");
	courseItems[0] = new CHealth(itemMsh, 90, 0, 0, 0);
	courseItems[1] = new CShield(itemMsh, 90, 0, 0, 40);
	courseItems[2] = new CSpeed(itemMsh, 90, 0, 0, 80);
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
	for (int i = 0; i < NUMBER_OF_ITEMS; i++)
	{
		if (courseItems[i] != nullptr)
		{
			courseItems[i]->SinHoverMovement(frameTime);
		}
	}

	// rotate vortex
	for (int i = 0; i < NUMBER_OF_VORTEX; i++)
	{
		vortexObjects[i]->RotateVortex(frameTime);
	}
}

//-- AABB COLLISION
void CTrack::ObjectCollision(CPlayer* cPlayer, CAI* cAI[], CSound* sound, CSound* explostion)
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

		//-- check for collision with the right boundarie of the checkpoints
		if (cPlayer->GetPlayerPos().posX > courseCheckpoints[i]->GetRBoundarie().minX && cPlayer->GetPlayerPos().posX < courseCheckpoints[i]->GetRBoundarie().maxX &&
			cPlayer->GetPlayerPos().posZ > courseCheckpoints[i]->GetRBoundarie().minZ && cPlayer->GetPlayerPos().posZ < courseCheckpoints[i]->GetRBoundarie().maxZ)
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
	
	if (SphereToSphereCollision(cPlayer, vortexObjects[0], 10, 700))
	{
		cPlayer->SetPlayerPos(vortexObjects[1]->GetX(), vortexObjects[1]->GetY(), vortexObjects[1]->GetZ());
	}

	if (SphereToSphereCollision(cPlayer, vortexObjects[2], 10,3000))
	{
		cPlayer->SetPlayerPos(vortexObjects[3]->GetX(), vortexObjects[3]->GetY(), vortexObjects[3]->GetZ());
		cPlayer->GetModel()->LookAt(courseCheckpoints[0]->GetModel());
	}

	for (int i = 0; i < 4; i++)
	{
		if (SphereToSphereCollision(cAI[i], vortexObjects[0], 10, 700))
		{
			cAI[i]->IncreaseWaypoint();
			cAI[i]->SetPlayerPos(vortexObjects[1]->GetX(), vortexObjects[1]->GetY(), vortexObjects[1]->GetZ());
		}

		if (SphereToSphereCollision(cAI[i], vortexObjects[2], 10, 3000))
		{
			cAI[i]->IncreaseWaypoint(); 
			cAI[i]->SetPlayerPos(vortexObjects[3]->GetX(), vortexObjects[3]->GetY(), vortexObjects[3]->GetZ());
			cAI[i]->GetModel()->LookAt(courseCheckpoints[0]->GetModel());
		}
	}
	OwnedItems(cPlayer);
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
				// item recreation
				if (courseItems[0] == nullptr)
				{
					courseItems[i] = new CHealth(itemMsh, 90, 0, 0, 0);
				}
				if (courseItems[1] == nullptr)
				{
					courseItems[i] = new CShield(itemMsh, 90, 0, 0, 40);
				}
				if (courseItems[2] == nullptr)
				{
					courseItems[i] = new CSpeed(itemMsh, 90, 0, 0, 80);
				}
			}
		}
	}
}

//-- ITEM COLLISION --//
void CTrack::ItemCollision(CPlayer* cPlayer, CSound* sound)
{
	for (int i = 0; i < NUMBER_OF_ITEMS; i++)
	{
		if (courseItems[i] != nullptr)
		{
			if (courseItems[i]->GetState() == false)
			{
				if (SphereToSphereCollision(cPlayer, courseItems[i], 5.0f, 5.0f))
				{
					sound->PlaySound();
					courseItems[i]->Collide();
					courseItems[i]->SetOwner(cPlayer);
				}
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

//-- check if owned items are being used --//
void CTrack::OwnedItems(CPlayer* cPlayer)
{
	for (int i = 0; i < NUMBER_OF_ITEMS; i++)
	{
		if (courseItems[i] != nullptr)
		{
			if (courseItems[i]->GetOwner() == cPlayer)
			{
				cPlayer->ActivateItem(courseItems[i]);

				if (courseItems[i]->GetUsed())
				{
					delete(courseItems[i]);
					courseItems[i] = nullptr;
				}
			}
		}
	}
}
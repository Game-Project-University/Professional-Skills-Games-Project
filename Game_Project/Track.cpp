#include "Track.h"

IMesh* CTrack::HeartMsh = nullptr;
IMesh* CTrack::SpeedMsh = nullptr;
IMesh* CTrack::SheildMsh = nullptr;

CTrack::CTrack()
{
	//-- checkpoints and laps variables to show on interface and track players progress
	
	itemHeld = false;

	font = myEngine->LoadFont("Comic Sans MS", 36.0f);

	playerAi = false;
	aiPlayer = false;
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
	courseObjects[37] = new CCrowdBarrier(375.0f, -1.0f, -20.0f, 5.0f, 350.0f, true);
	courseObjects[38] = new CCrowdBarrier(375.0f, -1.0f, 5.0f, 5.0f, 350.0f, false);
	courseObjects[39] = new CCrowdBarrier(475.0f, -1.0f, -20.0f, 5.0f, 350.0f, true);
	courseObjects[40] = new CCrowdBarrier(475.0f, -1.0f, 5.0f, 5.0f, 350.0f, false);
	courseObjects[41] = new CCrowdWall(375.0f, -2.0f, 168.0f, 7.5f, 20.0f, false);
	courseObjects[42] = new CCrowdWall(475.0f, -2.0f, 168.0f, 7.5f, 20.0f, false);
	courseObjects[43] = new CCrowdWall(375.0f, -2.0f, -12.5f, 7.5f, 20.0f, false);
	courseObjects[44] = new CCrowdWall(475.0f, -2.0f, -12.5f, 7.5f, 20.0f, false);
	courseObjects[45] = new CCrowdWall(375.0f, -2.0f, -182.5f, 7.5f, 20.0f, false);
	courseObjects[46] = new CCrowdWall(475.0f, -2.0f, -182.5f, 7.5f, 20.0f, false);

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
	courseCheckpoints[5] = new CCheckpoint(420, 0, -180, false);

	//Crowds
	crowdObjects[0] = new CCrowd(374.0f, 0.0f, -45.0f);
	crowdObjects[1] = new CCrowd(374.0f, 0.0f, -55.0f);
	crowdObjects[2] = new CCrowd(374.0f, 0.0f, -100.0f);
	crowdObjects[3] = new CCrowd(374.0f, 0.0f, -110.0f);
	crowdObjects[4] = new CCrowd(374.0f, 0.0f, 55.0f);
	crowdObjects[5] = new CCrowd(374.0f, 0.0f, 80.0f);
	crowdObjects[6] = new CCrowd(374.0f, 0.0f, 100.0f);
	crowdObjects[7] = new CCrowd(374.0f, 0.0f, 95.0f);
	crowdObjects[8] = new CCrowd(374.0f, 0.0f, 20.0f);
	//Far Side
	crowdObjects[9] = new CCrowd(477.0f, 0.0f, -45.0f);
	crowdObjects[10] = new CCrowd(477.0f, 0.0f, -110.0f);
	crowdObjects[11] = new CCrowd(477.0f, 0.0f, -60.0f);
	crowdObjects[12] = new CCrowd(477.0f, 0.0f, -80.0f);
	crowdObjects[13] = new CCrowd(477.0f, 0.0f, -30.0f);
	crowdObjects[14] = new CCrowd(477.0f, 0.0f, 20.0f);
	crowdObjects[15] = new CCrowd(477.0f, 0.0f, 125.0f);
	crowdObjects[16] = new CCrowd(477.0f, 0.0f, 50.0f);
	crowdObjects[17] = new CCrowd(477.0f, 0.0f, 10.0f);

	//Arrows - ( x / y / z / +rotation amount )
	arrowObjects[0] = new CArrow(-15.25f, 11.0f, 17.0f, 0.0f);
	arrowObjects[1] = new CArrow(15.25f, 11.0f, 17.0f, 0.0f);
	arrowObjects[2] = new CArrow(0.0f, 12.0f, 190.0f, 270.0f);
	arrowObjects[3] = new CArrow(-120.0f, 15.0f, 160.0f, 0.0f);
	arrowObjects[4] = new CArrow(-120.0f, 15.0f, 180.0f, 0.0f);
	arrowObjects[5] = new CArrow(-85.0f, 14.0f, 270.0f, 90.0f);
	arrowObjects[6] = new CArrow(477.0f, 12.0f, 240.0f, 180.0f);
	arrowObjects[7] = new CArrow(477.0f, 12.0f, 260.0f, 180.0f);
	arrowObjects[8] = new CArrow(367.0f, 18.0f, 0.0f, 180.0f);
	arrowObjects[9] = new CArrow(483.0f, 18.0f, 0.0f, 180.0f);
	arrowObjects[10] = new CArrow(367.0f, 18.0f, -50.0f, 180.0f);
	arrowObjects[11] = new CArrow(483.0f, 18.0f, -50.0f, 180.0f);

	//-- Items
	//IMesh* itemMsh = myEngine->LoadMesh("Sphere.x");
	courseItems[0] = new CHealth(HeartMsh, 90, 0, 0, 100, "health");
	courseItems[1] = new CShield(SheildMsh, 90, 10, 0, 100, "Shield");
	courseItems[2] = new CSpeed(SpeedMsh, 90, -10, 0, 100, "Speed");

	courseItems[3] = new CHealth(HeartMsh, 90, 20, 0, 245, "health");
	courseItems[4] = new CShield(SheildMsh, 90, 20, 0, 260, "Shield");
	courseItems[5] = new CSpeed(SpeedMsh, 90, 20, 0, 275, "Speed");

	courseItems[6] = new CHealth(HeartMsh, 90, 420, 0, -220, "health");
	courseItems[7] = new CShield(SheildMsh, 90, 440, 0, -220, "Shield");
	courseItems[8] = new CSpeed(SpeedMsh, 90, 400, 0, -220, "Speed");
}

CTrack::~CTrack()
{
	// delte the course objects
	for (int i = 0; i < NUMBER_OF_OBJECTS; i++)
	{
		delete(courseObjects[i]);
	}
}

void CTrack::TrackUpdate(float frameTime, CPlayer* playerPtr)
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

	//Update crowds if player is in that track area
	if (playerPtr->GetX() > 360.0f && playerPtr->GetX() < 480.0f)
	{
		for (int i = 0; i < NUMBER_OF_CROWDS; i++)
		{
			crowdObjects[i]->update(frameTime, playerPtr);
		}
	}

	//Update Arrow "Colour"
	for (int i = 0; i < NUMBER_OF_ARROWS; i++)
	{
		arrowObjects[i]->update(frameTime);
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
		
			if (cPlayer->GetPlayerS() > 0)
			{
				cPlayer->SetMovementSpeed(-20);
				cPlayer->MoveBeforeCollision();
				cPlayer->DecreaseHealth(40);
			}
			else if (cPlayer->GetPlayerS() < 0)
			{
				cPlayer->SetMovementSpeed(20);
				cPlayer->MoveBeforeCollision();
				cPlayer->DecreaseHealth(40);
			}
			
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
			cPlayer->DecreaseHealth(40);

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
			cPlayer->DecreaseHealth(40);

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
	if (cPlayer->GetCheckpoint() == 0)
	{
		cPlayer->GetModel()->SetPosition(courseCheckpoints[0]->GetX(), 0.0f, courseCheckpoints[0]->GetZ());
	}
	// set the cars position to the last checkpoint that the player drove through 
	else
	{
		cPlayer->GetModel()->SetPosition(courseCheckpoints[cPlayer->GetCheckpoint() - 1]->GetX(), 0.0f, courseCheckpoints[cPlayer->GetCheckpoint() - 1]->GetZ());
	}
}

//-- CHECKPOINT COLLISION --//
void CTrack::CheckPointCollision(CBasePlayer* cPlayer)
{
	for (int i = 0; i < NUMBER_OF_CHECKPOINTS; i++)
	{
		// (playerpos, checkpoint position, radious of player, radious of checkpoint)
		if (SphereToSphereCollision(cPlayer, courseCheckpoints[i], 10.0f, 60.0f))
		{
			if (cPlayer->GetCheckpoint() == i)
			{
				cPlayer->IncrementCheckpoint();
			}
			// if the checkpoint is equal to the number of checkpoints (so the lap is nearly complete) then when the collision happens with the starting checkpoint increment the lap variable
			if (cPlayer->GetCheckpoint() == NUMBER_OF_CHECKPOINTS && SphereToSphereCollision(cPlayer, courseCheckpoints[0], 10.0f, 60.0f))
			{
				cPlayer->ResetCheckpoint();
				cPlayer->IncrementLap();
				// item recreation
				if (courseItems[0] == nullptr)
				{
					courseItems[0] = new CHealth(HeartMsh, 90, 0, 0, 100, "health");
				}
				if (courseItems[1] == nullptr)
				{
					courseItems[1] = new CShield(SheildMsh, 90, 10, 0, 100, "Shield");
				}
				if (courseItems[2] == nullptr)
				{
					courseItems[2] = new CSpeed(SpeedMsh, 90, -10, 0, 100, "Speed");
				}
				if (courseItems[3] == nullptr)
				{
					courseItems[3] = new CHealth(HeartMsh, 90, 20, 0, 250, "health");
				}
				if (courseItems[4] == nullptr)
				{
					courseItems[4] = new CShield(SheildMsh, 90, 20, 0, 260, "Shield");
				}
				if (courseItems[5] == nullptr)
				{
					courseItems[5] = new CSpeed(SpeedMsh, 90, 20, 0, 270, "Speed");
				}
				if (courseItems[6] == nullptr)
				{
					courseItems[6] = new CHealth(HeartMsh, 90, 420, 0, 140, "health");
				}
				if (courseItems[7] == nullptr)
				{
					courseItems[7] = new CShield(SheildMsh, 90, 440, 0, 140, "Shield");
				}
				if (courseItems[8] == nullptr)
				{
					courseItems[8] = new CSpeed(SpeedMsh, 90, 400, 0, -220, "Speed");
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
				if (SphereToSphereCollision(cPlayer, courseItems[i], 5.0f, 5.0f) && itemHeld == false)
				{
					if (courseItems[i]->type == "Shield")
					{
						ItemShow = "Item Collected: Shield";
					}

					if (courseItems[i]->type == "Speed")
					{
						ItemShow = "Item Collected: Speed";
					}

					sound->PlaySound();
					courseItems[i]->Collide();
					courseItems[i]->SetOwner(cPlayer);
					itemHeld = true;
				}
			}
		}
	}
}

void CTrack::DisplayItemHeld()
{
	interfaceText << ItemShow;
	font->Draw(interfaceText.str(), 500, 798, kWhite);
	interfaceText.str("");
}

//-- ITEM COLLISION --//
void CTrack::AICollision(CPlayer* cPlayer, CAI* cAI[], CSound* sound)
{
	
	// Collision with player to AI
	for (int i = 0; i < 4; i++)
	{
		if (SphereToSphereCollision(cPlayer, cAI[i], 4.0f, 4.0f))
		{
				cPlayer->SetMovementSpeed(-10);
				cPlayer->MoveBeforeCollision();
				cAI[i]->SetMovementSpeed(10);
				//cPlayer->DecreaseHealth(1);

				sound->PlaySound();
		}

		if (SphereToSphereCollision(cAI[i], cPlayer, 4.0f, 4.0f))
		{
				cAI[i]->SetMovementSpeed(-10);
				cAI[i]->MoveBeforeCollision();
				cPlayer->SetMovementSpeed(10);
				//cPlayer->DecreaseHealth(1);

				sound->PlaySound();
		}
	}
	// Collision with AI to AI
	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			if (j != i)
			{
				if (SphereToSphereCollision(cAI[j], cAI[i], 4.0f, 4.0f))
				{
					cAI[i]->SetMovementSpeed(-2);
					cAI[i]->MoveBeforeCollision();
					//cPlayer->DecreaseHealth(1);

					sound->PlaySound();

				}
			}
		}
	}
}

//-- SPHERE TO SPHERE COLLISION --//
template <class T, class S> bool CTrack::SphereToSphereCollision(T* cType1, S* cType2, float radius1, float radius2)
{
	float distX = cType1->GetX() - cType2->GetX();
	float distZ = cType1->GetZ() - cType2->GetZ();
	
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
					itemHeld = false;
					ItemShow = "";
				}
			}
		}
	}
}
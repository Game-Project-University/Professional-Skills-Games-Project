#include "Track.h"

IMesh* CTrack::HeartMsh = nullptr;
IMesh* CTrack::SpeedMsh = nullptr;
IMesh* CTrack::SheildMsh = nullptr;
ISprite* isprite;

CTrack::CTrack()
{
	//-- checkpoints and laps variables to show on interface and track players progress
	
	itemHeld = false;

	font = myEngine->LoadFont("Comic Sans MS", 36.0f);

	playerAi = false;
	aiPlayer = false;
	//-- creation of objects (x, y, z, width, height)
	//-- i will make this read in from a file eventually
	courseObjects[70] = new CSkyScraper(-40.0f, 0.0f, -120.0f, 52.0f, 54.0f);
	courseObjects[69] = new CSkyScraper(40.0f, 0.0f, -120.0f, 52.0f, 54.0f);
	courseObjects[68] = new CSkyScraper(-40.0f, 0.0f, -60.0f, 52.0f, 54.0f);
	courseObjects[67] = new CSkyScraper(40.0f, 0.0f, -60.0f, 52.0f, 54.0f);
	courseObjects[0]  = new CSkyScraper(-40.0f,0.0f,60.0f, 52.0f, 54.0f);
	courseObjects[1]  = new CSkyScraper(40.0f, 0.0f, 60.0f, 52.0f, 54.0f);
	courseObjects[2]  = new CSkyScraper(-40.0f, 0.0f, 0.0f, 52.0f, 54.0f);
	courseObjects[3]  = new CSkyScraper(40.0f, 0.0f, 0.0f, 52.0f, 54.0f);
	courseObjects[4]  = new CSkyScraper(-40.0f, 0.0f, 120.0f, 52.0f, 54.0f);
	courseObjects[5]  = new CSkyScraper(40.0f, 0.0f, 120.0f, 52.0f, 54.0f);
	courseObjects[6]  = new CBlockBuilding(36.0f, 0.0f, 170.0f, 40.0f, 54.0f);
	courseObjects[7]  = new CBlockBuilding(0.0f, 0.0f, 210.0f, 40.0f, 54.0f);
	courseObjects[8]  = new CBlockBuilding(-30.0f, 0.0f, 210.0f, 30.0f, 54.0f);
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

	courseObjects[47] = new CWall(440.0f, 0.0f, 210.0f, 10.0f, 18.0f, true);
	courseObjects[48] = new CWall(400.0f, 0.0f, 210.0f, 10.0f, 18.0f, true);
	courseObjects[49] = new CWall(448.0f, 0.0f, -600.0f, 10.0f, 18.0f, true);
	courseObjects[50] = new CWall(392.0f, 0.0f, -600.0f, 10.0f, 18.0f, true);
	courseObjects[51] = new CWall(462.0f, 0.0f, -600.0f, 10.0f, 18.0f, true);
	courseObjects[52] = new CWall(378.0f, 0.0f, -600.0f, 10.0f, 18.0f, true);
	courseObjects[53] = new CWall(476.0f, 0.0f, -600.0f, 10.0f, 18.0f, true);
	courseObjects[54] = new CWall(364.0f, 0.0f, -600.0f, 10.0f, 18.0f, true);

	courseObjects[55] = new CWall(-20.0f, 0.0f, -300.0f, 10.0f, 18.0f, false);
	courseObjects[56] = new CWall(20.0f, 0.0f, -300.0f, 10.0f, 18.0f, false);
	courseObjects[57] = new CWall(-20.0f, 0.0f, -280.0f, 10.0f, 18.0f, false);
	courseObjects[58] = new CWall(20.0f, 0.0f, -280.0f, 10.0f, 18.0f, false);
	courseObjects[59] = new CWall(-20.0f, 0.0f, -260.0f, 10.0f, 18.0f, false);
	courseObjects[60] = new CWall(20.0f, 0.0f, -260.0f, 10.0f, 18.0f, false);
	courseObjects[61] = new CWall(-20.0f, 0.0f, -340.0f, 10.0f, 18.0f, false);
	courseObjects[62] = new CWall(20.0f, 0.0f, -340.0f, 10.0f, 18.0f, false);
	courseObjects[63] = new CWall(-20.0f, 0.0f, -320.0f, 10.0f, 18.0f, false);
	courseObjects[64] = new CWall(20.0f, 0.0f, -320.0f, 10.0f, 18.0f, false);
	courseObjects[65] = new CWall(-20.0f, 0.0f, -300.0f, 10.0f, 18.0f, false);
	courseObjects[66] = new CWall(20.0f, 0.0f, -300.0f, 10.0f, 18.0f, false);

	courseObjects[67] = new CWall(-20.0f, 0.0f, -280.0f, 10.0f, 18.0f, false);
	courseObjects[68] = new CWall(20.0f, 0.0f, -280.0f, 10.0f, 18.0f, false);
	courseObjects[69] = new CWall(-20.0f, 0.0f, -260.0f, 10.0f, 18.0f, false);
	courseObjects[70] = new CWall(20.0f, 0.0f, -260.0f, 10.0f, 18.0f, false);
	courseObjects[71] = new CWall(-20.0f, 0.0f, -240.0f, 10.0f, 18.0f, false);
	courseObjects[72] = new CWall(20.0f, 0.0f, -240.0f, 10.0f, 18.0f, false);
	courseObjects[73] = new CWall(-20.0f, 0.0f, -220.0f, 10.0f, 18.0f, false);
	courseObjects[74] = new CWall(20.0f, 0.0f, -220.0f, 10.0f, 18.0f, false);
	courseObjects[75] = new CWall(-20.0f, 0.0f, -200.0f, 10.0f, 18.0f, false);
	courseObjects[76] = new CWall(20.0f, 0.0f, -200.0f, 10.0f, 18.0f, false);
	courseObjects[77] = new CWall(-20.0f, 0.0f, -180.0f, 10.0f, 18.0f, false);
	courseObjects[78] = new CWall(20.0f, 0.0f, -180.0f, 10.0f, 18.0f, false);
	courseObjects[77] = new CWall(-20.0f, 0.0f, -160.0f, 10.0f, 18.0f, false);
	courseObjects[78] = new CWall(20.0f, 0.0f, -160.0f, 10.0f, 18.0f, false);
	courseObjects[79] = new CWall(-20.0f, 0.0f, -140.0f, 10.0f, 18.0f, false);
	courseObjects[80] = new CWall(20.0f, 0.0f, -140.0f, 10.0f, 18.0f, false);

	courseObjects[81] = new CWall(448, 0, -180, 10.0f, 18.0f, true);
	courseObjects[82] = new CWall(392, 0, -180, 10.0f, 18.0f, true);
	courseObjects[83] = new CWall(463, 0, -180, 10.0f, 18.0f, true);
	courseObjects[84] = new CWall(378, 0, -180, 10.0f, 18.0f, true);
	courseObjects[85] = new CWall(476, 0, -180, 10.0f, 18.0f, true);
	courseObjects[86] = new CWall(364, 0, -180, 10.0f, 18.0f, true);

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
	courseCheckpoints[6] = new CCheckpoint(420, 0, -600, false);

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

	//-- models to fix players direction on respawn

	/*FixLookObjects[0] = HeartMsh->CreateModel(0, 0, 10);
	FixLookObjects[0]->Scale(0.2);
	FixLookObjects[1] = HeartMsh->CreateModel(0, 0, 130);
	FixLookObjects[1]->Scale(0.2);
	FixLookObjects[2] = HeartMsh->CreateModel(-10, 0, 260);
	FixLookObjects[2]->Scale(0.2);
	FixLookObjects[3] = HeartMsh->CreateModel(80, 0, 260);
	FixLookObjects[3]->Scale(0.2);
	FixLookObjects[4] = HeartMsh->CreateModel(420, 0, 190);
	FixLookObjects[4]->Scale(0.2);
	FixLookObjects[5] = HeartMsh->CreateModel(420, 0, -190);
	FixLookObjects[5]->Scale(0.2);*/
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

void CTrack::ResetPlayerPosition(CBasePlayer* cPlayer)
{
	// if the checkpoint is = to 0 eg the starting checkpoint then when the car blows up reset the cars position to this checkpoint 
	if (cPlayer->GetCheckpoint() == 0)
	{
		cPlayer->GetModel()->SetPosition(courseCheckpoints[0]->GetX(), 0.0f, courseCheckpoints[0]->GetZ());


	}
	// set the cars position to the last checkpoint that the player drove through 
	else
	{
		cPlayer->GetModel()->SetPosition(courseCheckpoints[cPlayer->GetCheckpoint()-1]->GetX(), 0.0f, courseCheckpoints[cPlayer->GetCheckpoint() - 1]->GetZ());
	}
}

//-- CHECKPOINT COLLISION --//
void CTrack::CheckPointCollision(CBasePlayer* cPlayer, CAI* cAI[])
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
					courseItems[6] = new CHealth(HeartMsh, 90, 420, 0, -220, "health");
				}
				if (courseItems[7] == nullptr)
				{
					courseItems[7] = new CShield(SheildMsh, 90, 440, 0, -220, "Shield");
				}
				if (courseItems[8] == nullptr)
				{
					courseItems[8] = new CSpeed(SpeedMsh, 90, 400, 0, -220, "Speed");
				}
			}
		}
	}

	for (int i = 0; i < NUMBER_OF_CHECKPOINTS; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (SphereToSphereCollision(cAI[j], courseCheckpoints[i], 10.0f, 60.0f))
			{
				if (cAI[j]->GetCheckpoint() == i)
				{
					cAI[j]->IncrementCheckpoint();
				}

				if (cAI[j]->GetCheckpoint() == NUMBER_OF_CHECKPOINTS && SphereToSphereCollision(cAI[j], courseCheckpoints[0], 10.0f, 60.0f))
				{
					cAI[j]->ResetCheckpoint();
					cAI[j]->IncrementLap();
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
						isprite = myEngine->CreateSprite("ShieldPick.png");
						isprite->SetPosition(20, 20);
						isprite->SetZ(0);
					}
					else if (courseItems[i]->type == "Speed")
					{
						isprite = myEngine->CreateSprite("SpeedPick.png");
						isprite->SetPosition(20, 20);
						isprite->SetZ(0);
					}
					else
					{
						isprite = myEngine->CreateSprite("dummy.png");
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

void CTrack::RacePosition(CPlayer* cPlayer, CAI* cAI[])
{
	// Test Players position against AI
	for (int i = 0; i < 4; i++)
	{
		// If player is on the same lap as the AI
		if (cPlayer->GetLap() == cAI[i]->GetLap())
		{
			// And heading towards the same checkpoint
			if (cPlayer->GetCheckpoint() == cAI[i]->GetCheckpoint())
			{
				float playerDist = 0;
				float aiDist = 0;

				// Calculate whos closer to the checkpoint
				if (cPlayer->GetCheckpoint() != 7)
				{
					playerDist = distance(cPlayer, courseCheckpoints[cPlayer->GetCheckpoint()]);
				}
				else
				{
					playerDist = distance(cPlayer, courseCheckpoints[0]);
				}

				if (cAI[i]->GetCheckpoint() != 7)
				{
					aiDist = distance(cAI[i], courseCheckpoints[cAI[i]->GetCheckpoint()]);
				}
				else
				{
					aiDist = distance(cAI[i], courseCheckpoints[0]);
				}

				// Store the race positions
				int playerPos = cPlayer->GetPosition();
				int aiPos = cAI[i]->GetPosition();
				
				// If the Ai is closer to the checkpoint
				if (playerDist > aiDist)
				{
					// Test if the players position is better than the AI's
					if (playerPos < aiPos)
					{
						// If so swap them around as the AI is closer 
						cPlayer->SetPosition(aiPos);
						cAI[i]->SetPosition(playerPos);
					}
					// Else positions are correct
				}
				// If the player is closer to the checkpoint
				else if (playerDist < aiDist)
				{
					// Test if the AI's position is better than the players
					if (playerPos > aiPos)
					{
						// If so swap them around as the player is closer 
						cPlayer->SetPosition(aiPos);
						cAI[i]->SetPosition(playerPos);
					}
					// Else positions are correct
				}
			}
			// And player is heading towards a further along checkpoint than the AI
			else if (cPlayer->GetCheckpoint() > cAI[i]->GetCheckpoint() && cPlayer->GetLap() == cAI[i]->GetLap())//|| cPlayer->GetCheckpoint() == 0 && cAI[i]->GetCheckpoint() > 0)
			{
				// Position of players
				//int playerPos = cPlayer->GetPosition();
				//int aiPos = cAI[i]->GetPosition();

				// If AI's position is better than the players swap them around
				if (cPlayer->GetPosition() > cAI[i]->GetPosition())
				{
					cPlayer->SetPosition(cAI[i]->GetPosition());
					cAI[i]->SetPosition(cPlayer->GetPosition());
				}
				// Else positions are correct
			}
			// And AI is heading towards a further along checkpoint than the player
			else if (cPlayer->GetCheckpoint() < cAI[i]->GetCheckpoint() && cPlayer->GetLap() == cAI[i]->GetLap())// || cAI[i]->GetCheckpoint() == 0 && cPlayer->GetCheckpoint() > 0)
			{
				// Position of players
				//int playerPos = cPlayer->GetPosition();
				//int aiPos = cAI[i]->GetPosition();

				// If Players position is better than the AI's swap them around
				if (cAI[i]->GetPosition() > cPlayer->GetPosition())
				{
					cPlayer->SetPosition(cAI[i]->GetPosition());
					cAI[i]->SetPosition(cPlayer->GetPosition());
				}
				// Else positions are correct
			}
		}
	}

	// Test AI's position against other AI
	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			if (j != i)
			{
				// If AI-i is on the same lap as the AI-j
				if (cAI[i]->GetLap() == cAI[j]->GetLap())
				{
					// And heading towards the same checkpoint
					if (cAI[i]->GetCheckpoint() == cAI[j]->GetCheckpoint())
					{
						float aiDisti = 0;
						float aiDistj = 0;
						// Calculate whos closer to the checkpoint
						if (cAI[i]->GetCheckpoint() != 7)
						{
							aiDisti = distance(cAI[i], courseCheckpoints[cAI[i]->GetCheckpoint()]);
						}
						else
						{
							aiDisti = distance(cAI[i], courseCheckpoints[0]);
						}

						if (cAI[j]->GetCheckpoint() != 7)
						{
							aiDistj = distance(cAI[j], courseCheckpoints[cAI[j]->GetCheckpoint()]);
						}
						else
						{
							aiDistj = distance(cAI[j], courseCheckpoints[0]);
						}

						// Store the race positions
						int aiPosi = cAI[i]->GetPosition();
						int aiPosj = cAI[j]->GetPosition();

						// If the AI-j is closer to the checkpoint
						if (aiDisti > aiDistj)
						{
							// Test if the AI-i position is better than the AI-j
							if (aiPosi < aiPosj)
							{
								// If so swap them around as the AI-j is closer 
								cAI[i]->SetPosition(aiPosj);
								cAI[j]->SetPosition(aiPosi);
							}
							// Else positions are correct
						}
						// If the AI-i is closer to the checkpoint
						else if (aiDisti < aiDistj)
						{
							// Test if the AI-j position is better than the AI-i
							if (aiPosi > aiPosj)
							{
								// If so swap them around as the AI-i is closer 
								cAI[i]->SetPosition(aiPosj);
								cAI[j]->SetPosition(aiPosi);
							}
							// Else positions are correct
						}
					}
				}
				// And AI-i is heading towards a further along checkpoint than the AI
				else if (cAI[i]->GetCheckpoint() > cAI[j]->GetCheckpoint() && cAI[i]->GetLap() == cAI[j]->GetLap())
				{
					// Position of players
					int aiPosi = cAI[i]->GetPosition();
					int aiPosj = cAI[j]->GetPosition(); 

					// If AI-j position is better than the AI-i swap them around
					if (aiPosi > aiPosj)
					{
						cAI[i]->SetPosition(aiPosj);
						cAI[j]->SetPosition(aiPosi);
					}
					// Else positions are correct
				}
				// And AI-j is heading towards a further along checkpoint than the AI-i
				else if (cAI[i]->GetCheckpoint() < cAI[j]->GetCheckpoint() && cAI[i]->GetLap() == cAI[j]->GetLap())
				{
					// Position of players
					int aiPosi = cAI[i]->GetPosition();
					int aiPosj = cAI[j]->GetPosition();

					// If AI-i position is better than the AI-j swap them around
					if (aiPosi < aiPosj)
					{
						cAI[i]->SetPosition(aiPosj);
						cAI[j]->SetPosition(aiPosi);
					}
					// Else positions are correct
				}
			}
		}
	}
}


//-- ITEM COLLISION --//
void CTrack::AICollision(CPlayer* cPlayer, CAI* cAI[], CSound* sound)
{
	
	
	// Collision with player to AI
	for (int i = 0; i < 4; i++)
	{
		if (SphereToSphereCollision(cPlayer, cAI[i], 4.0f, 4.0f))
		{
			if (dotProduct(cPlayer, cAI[i]) < 0.0f) // infront of the ai collided with
			{
				cPlayer->MoveBeforeCollision();
				cPlayer->SetMovementSpeed(40);
				cAI[i]->SetMovementSpeed(-240);
				cPlayer->DecreaseHealth(5);
				cAI[i]->DecreaseHealth(100);
			}
			else 
			{
				cPlayer->SetMovementSpeed(-10);
				cPlayer->MoveBeforeCollision();
				cPlayer->DecreaseHealth(20);

				cAI[i]->SetMovementSpeed(20);
				cAI[i]->DecreaseHealth(50);
			}
				sound->PlaySound();
		}
	}

	// Collision with AI to AI
	//for (int j = 0; j < 4; j++)
	//{
	//	for (int i = 0; i < 4; i++)
	//	{
	//		if (j != i)
	//		{
	//			if (SphereToSphereCollision(cAI[j], cAI[i], 4.0f, 4.0f)) 
	//			{
	//				if (dotProduct(cAI[j], cAI[i]) < 0.0f) // if the J ai is infront of the i ai 
	//				{
	//					cAI[j]->MoveBeforeCollision();
	//					cAI[j]->SetMovementSpeed(10);
	//					cAI[j]->DecreaseHealth(50);

	//					cAI[i]->MoveBeforeCollision();
	//					cAI[i]->SetMovementSpeed(-10);
	//					cAI[i]->DecreaseHealth(100);
	//				}
	//				else  // if the J ai is infront of the i ai 
	//				{
	//					cAI[j]->MoveBeforeCollision();
	//					cAI[j]->SetMovementSpeed(-10);
	//					cAI[j]->DecreaseHealth(100);

	//					cAI[i]->MoveBeforeCollision();
	//					cAI[i]->SetMovementSpeed(10);
	//					cAI[i]->DecreaseHealth(100);
	//				}
	//				sound->PlaySound();
	//			}
	//		}
	//	}
	//}
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
					isprite->SetPosition(2000, 2000);
				}
			}
		}
	}
}

template <class T, class S> float CTrack::dotProduct(T* mdl1, S* mdl2)
{
	float distanceX = mdl2->GetX() - mdl1->GetX();
	float distanceZ = mdl2->GetZ() - mdl1->GetZ();

	float modelXfacingV = mdl1->GetFacingVector().x;
	float modelZfacingV = mdl1->GetFacingVector().z;

	return (modelXfacingV * distanceX) + (modelZfacingV * distanceZ);
}

template <class T, class S> float CTrack::distance(T* mdl1, S* mdl2)
{
	float distanceX = mdl2->GetX() - mdl1->GetX();
	float distanceZ = mdl2->GetZ() - mdl1->GetZ();

	distanceX = distanceX * distanceX;
	distanceZ = distanceZ * distanceZ;

	return distanceX + distanceZ;
}
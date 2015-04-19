#include "Player.h"

///////////////////
//--CONTRUCTORS--//
CPlayer::CPlayer(IMesh* playerMsh) : CBasePlayer()
{

	// create player model
	playerMdl = playerMsh->CreateModel(0.0f, 0.0f, -14.0f);
	//- Camera Attachment to player
	myCamera = myEngine->CreateCamera(kManual, 0.0f, 0.0f, 0.0f); // create camera
	myCamera->SetPosition(0.0f, 3.0f, -12.0f); // set camera position
	myCamera->AttachToParent(playerMdl);// attach camera to the players car

	//--Camera Clipping--//
	myCamera->SetFarClip(10000.0f);
	myCamera->SetNearClip(0.1f);

	//-- Camera Variables intialisation
	camerRotationS = 0.001; // speed of the rotation of the camera
	cameraMaxX = 5.0; // max amount the camera can move to the right
	cameraCounter = 0.0f; // counter used to track how much the camera has moved
}

//////////////////
//--DESTRUCTOR--//
CPlayer::~CPlayer()
{

}

//////////////////////
//--PLAYERMOVEMENT--//

void CPlayer::ForwardReverseMovement(float frameTime) 
{
	if (myEngine->KeyHeld(FORWARD) && playerMovementS < playerMaxSpeed)
	{
		IncreaseAccelration();
	}
	else if (myEngine->KeyHeld(REVERSE) && playerMovementS > -playerReverseMaxSpeed)
	{
		DecreaseAccelration();
	}
	else if (playerMovementS > 0)
	{
		playerMovementS -= playerAccelrationS;
	}
	else if (playerMovementS < 0)
	{
		playerMovementS += playerAccelrationS;
	}
}

void CPlayer::RightLeftMovement(float frameTime)
{
	//- if the Keyhit D then enter statment 
	if (myEngine->KeyHeld(RIGHT))
	{
		playerMdl->RotateLocalY(frameTime* playerRotationS);

		//- statement to make the camera move offset to the car
		if (cameraCounter < cameraMaxX)
		{
			myCamera->MoveLocalX(camerRotationS);
			cameraCounter += 0.001;
		}
		
	}
	//- if the camera has been moved and the player is no longer turning slowly reset the position of the camera
	else if (cameraCounter > 0)
	{
		myCamera->MoveLocalX(-0.002);
		cameraCounter -= 0.002;
	}

	if (myEngine->KeyHeld(LEFT))
	{
		playerMdl->RotateLocalY(-frameTime* playerRotationS);

		if (cameraCounter > -cameraMaxX)
		{
			myCamera->MoveLocalX(-camerRotationS);
			cameraCounter -= 0.001;
		}
	}
	else if (cameraCounter < 0)
	{
		myCamera->MoveLocalX(0.002);
		cameraCounter += 0.002;
	}
}

/////////////////////////
//--PLAYER ACTIVATIONS--//

void CPlayer::ActivateItem(CBaseItem* itemOwned)
{
    if (myEngine->KeyHit(ACTIVATE) && itemOwned->GetUsed() == false && GetPlayerHealth() != 100)
	{
			itemOwned->Activate();
	}
}
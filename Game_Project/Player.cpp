#include "Player.h"

///////////////////
//--CONTRUCTORS--//
CPlayer::CPlayer(IMesh* playerMsh, int pos) : CBasePlayer()
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
	amountRotated = 0.0f;
	TurningActive = false;
	timer = 0;

	playerAccelrationS = 0.9;

	position = pos;
	gun = new CGun();
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
		playerMdl->RotateY(frameTime* playerRotationS);

		if (amountRotated > -25.0f)
		{
			playerMdl->RotateLocalZ(-playerRotationS * frameTime);
			amountRotated -= playerRotationS * frameTime;
		}
	}
	else if(amountRotated < 0)
	{
			playerMdl->RotateLocalZ(playerRotationS * frameTime);
			amountRotated += playerRotationS * frameTime;
	}

	//- if the camera has been moved and the player is no longer turning slowly reset the position of the camera

	if (myEngine->KeyHeld(LEFT))
	{
		playerMdl->RotateY(-frameTime* playerRotationS);

		if (amountRotated < 25.0f)
		{
			playerMdl->RotateLocalZ(playerRotationS * frameTime);
			amountRotated += playerRotationS * frameTime;
		}
	}
	else if(amountRotated > 0)
	{
		playerMdl->RotateLocalZ(-playerRotationS * frameTime);
		amountRotated -= playerRotationS * frameTime;
	}
}

/////////////////////////
//--PLAYER ACTIVATIONS--//

void CPlayer::ActivateItem(CBaseItem* itemOwned)
{
	if (itemOwned->GetUsable() == true)
	{
		if (myEngine->KeyHit(ACTIVATE) && itemOwned->GetUsed() == false)
		{
			itemOwned->Activate();
		}
	}
	else if (itemOwned->GetUsable() == false)
	{ 
		if ( itemOwned->GetUsed() == false)
		{
				itemOwned->Activate();
		}
	}
}

// gun stuff


void CPlayer::PlayerUpdate(float frametime)
{
	if (myEngine->KeyHit(Key_F))
	{
		gun->setfacing(GetFacingVectorX(), GetFacingVectorZ());
		gun->SetShooting(true);
	}

	if (gun->ReturnShooting() == true)
	{
		if (gun->ReturnBulletCreated() == false)
		{
			gun->CreateBullet(playerMdl->GetX(), playerMdl->GetY(), playerMdl->GetZ());
		}

		if (gun->ReturnBulletCreated() == true)
		{
			timer += 2 * frametime;
			if (timer < 2)
			{
				gun->MoveBullet(frametime);
			}
			else
			{
				gun->RemoveModel();
				timer = 0;
				gun->SetShooting(false);
				gun->SetCreatedBullet(false);
			}
		}
	}
}

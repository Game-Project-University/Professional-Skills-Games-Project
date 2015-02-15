#include "Player.h"

///////////////////
//--CONTRUCTORS--//
CPlayer::CPlayer(IMesh* playerMsh)
{
	//- set the player movement speed
	playerMovementS = 0.0f;
	//- set the player rotation speed
	playerRotationS = 100.0f;
	//- set the speed that the player accelrates
	playerAccelrationS = 0.005;
	//- set the max player speed
	playerMaxSpeed = 100.0f;
	//- set the max reverse player speed
	playerReverseMaxSpeed = 30.0f;
	//- set the angle of the sinewave to start at 0
	sineWaveAngle = 0;
	sineWaveValue = 0;
	
	// create player model
	playerMdl = playerMsh->CreateModel(0.0f, 1.0f, 0.0f);
	
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

///////////////
//--GETTERS--//
IModel* CPlayer::GetModel()
{
	return playerMdl;
}

float CPlayer::GetPlayerS()
{
	return playerMovementS;
}

float CPlayer::GetPlayerRotationS()
{
	return playerRotationS;
}

///////////////
//--SETTERS--//
void CPlayer::IncreaseAccelration()
{
	playerMovementS+= playerAccelrationS;
}

void CPlayer::DecreaseAccelration()
{
	playerMovementS -= playerAccelrationS*2;
}

//////////////////////
//--PLAYERMOVEMENT--//
void CPlayer::SinHoverMovement(float frameTime)
{
	sineWaveAngle += frameTime;
	sineWaveValue = sin(sineWaveAngle + 1.0f);
		
	playerMdl->SetY(sineWaveValue + 1.0f);

	if (sineWaveAngle >= 360.0f)
	{
		sineWaveAngle = 0.0f;
	}
}

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
void CPlayer::PullHandbrake()
{
		if (playerMovementS > 0)
		{
			playerMovementS -= 0.008f;
		}

		if (playerMovementS < -1)
		{
			playerMovementS += 0.008f;
		}
}
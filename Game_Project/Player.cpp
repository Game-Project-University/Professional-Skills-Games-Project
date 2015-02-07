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
	playerMaxSpeed = 60.0f;
	//- set the max reverse player speed
	playerReverseMaxSpeed = 30.0f;

	playerMdl = playerMsh->CreateModel(0.0f, 1.0f, 0.0f);
	playerMdl->Scale(3);

	vechArray[0] = "hmmwv.x";
	vechArray[1] = "HoverTank01.x";
	vechArray[2] = "4x4jeep.x";
	vechArray[3] = "amartin.x";
	vechArray[4] = "GMC.x";
	vechArray[5] = "volvo_nh12.x";

	//- Camera Attachment to player
	myCamera = myEngine->CreateCamera(kManual, 0.0f, 0.0f, 0.0f); // create camera
	myCamera->SetPosition(0.0f, 3.0f, -10.0f); // set camera position
	myCamera->AttachToParent(playerMdl);// attach camera to the players car

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
void CPlayer::ForwardReverseMovement(float frameTime) 
{
	if (myEngine->KeyHeld(FORWARD) && playerMovementS < playerMaxSpeed)
	{
		playerMdl->GetNode(3)->RotateLocalX(frameTime * 800);
		playerMdl->GetNode(4)->RotateLocalX(frameTime * 800);
		playerMdl->GetNode(6)->RotateLocalX(frameTime * 800);
		playerMdl->GetNode(7)->RotateLocalX(frameTime * 800);

			IncreaseAccelration();
	}
	else if (myEngine->KeyHeld(REVERSE) && playerMovementS > -playerReverseMaxSpeed)
	{
		playerMdl->GetNode(3)->RotateLocalX(-frameTime * 800);
		playerMdl->GetNode(4)->RotateLocalX(-frameTime * 800);
		playerMdl->GetNode(6)->RotateLocalX(-frameTime * 800);
		playerMdl->GetNode(7)->RotateLocalX(-frameTime * 800);

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
		//- rotate the model right
		if (playerMovementS > 1)
		{
			playerMdl->RotateLocalY(frameTime* playerRotationS);


			//- statement to make the camera move offset to the car
			if (cameraCounter < cameraMaxX)
			{
				myCamera->MoveLocalX(camerRotationS);
				cameraCounter += 0.001;
			}
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
		if (playerMovementS > 1)
		{
			playerMdl->RotateLocalY(-frameTime* playerRotationS);

			if (cameraCounter > -cameraMaxX)
			{
				myCamera->MoveLocalX(-camerRotationS);
				cameraCounter -= 0.001;
			}
		}
	}
	else if (cameraCounter < 0)
	{
		myCamera->MoveLocalX(0.002);
		cameraCounter += 0.002;
	}
}

/////////////////////////
//--PLAYER ATIVATIONS--//
void CPlayer::PullHandbrake()
{
	if (playerMovementS > 0)
	{
		playerMovementS -= 0.008f;
		if (myEngine->KeyHeld(LEFT) || myEngine->KeyHeld(RIGHT))
		{
			playerMdl->RotateLocalY(0.005);
		}
	}
}
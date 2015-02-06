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
	playerMaxSpeed = 30.0f;
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
//--PlayerMovement--//
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
	if (myEngine->KeyHeld(RIGHT))
	{
		//playerMdl->GetNode(3)->RotateY(frameTime * 900);
		//playerMdl->GetNode(4)->RotateY(frameTime * 900);
		playerMdl->RotateLocalY(frameTime* playerRotationS);
	}
	if (myEngine->KeyHeld(LEFT))
	{
		playerMdl->RotateLocalY(-frameTime* playerRotationS);
	}
}
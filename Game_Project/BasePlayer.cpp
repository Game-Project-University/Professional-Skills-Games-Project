#include "BasePlayer.h"

CBasePlayer::CBasePlayer()
{
	health = 100;
	shield = 0;
	//- set the player movement speed
	playerMovementS = 0.0f;
	//- set the player rotation speed
	playerRotationS = 100.0f;
	//- set the speed that the player accelrates
	playerAccelrationS = 0.05;
	//- set the max player speed
	playerMaxSpeed = 70.0f;
	//- set the max reverse player speed
	playerReverseMaxSpeed = 30.0f;
	//- set the angle of the sinewave to start at 0
	sineWaveAngle = 0;
	sineWaveValue = 0;
	//currentItem = NULL;
}

CBasePlayer::~CBasePlayer()
{
}

///////////////
//--SETTERS--//
void CBasePlayer::IncreaseAccelration()
{
	playerMovementS += playerAccelrationS;
}

void CBasePlayer::DecreaseAccelration()
{
	playerMovementS -= playerAccelrationS * 2;
}

void CBasePlayer::SetMovementSpeed(float value)
{
	playerMovementS = value;
}

void CBasePlayer::IncreaseHealth(int value)
{
	if (health < 100)
	{
		health += value;

		if (health > 100)
		{
			health = 100;
		}
	}
}

void CBasePlayer::DecreaseHealth(int value)
{
	if (health > 0)
	{
		health -= value;
		if (health < 0)
		{
			health = 0;
		}
	}
}

void CBasePlayer::ResetPlayerHealth()
{
	health = 100;
}

void CBasePlayer::SetPlayerPos(float x, float y, float z)
{
	playerMdl->SetPosition(x, y, z);
}

void CBasePlayer::UpdatePlayerPos()
{
	playerPos.posX = playerMdl->GetX();
	playerPos.posY = playerMdl->GetY();
	playerPos.posZ = playerMdl->GetZ();
}

void CBasePlayer::UpdatePreviousPos()
{
	playerPrevPos.posX = playerMdl->GetX();
	playerPrevPos.posY = playerMdl->GetY();
	playerPrevPos.posZ = playerMdl->GetZ();
}

void CBasePlayer::MoveBeforeCollision()
{
	playerMdl->SetPosition(playerPrevPos.posX, playerPrevPos.posY, playerPrevPos.posZ);
}

//////////////////////
//--PLAYERMOVEMENT--//
void CBasePlayer::SinHoverMovement(float frameTime)
{
	sineWaveAngle += frameTime;
	sineWaveValue = sin(sineWaveAngle + 1.0f);

	playerMdl->SetY(sineWaveValue + 1.0f);

	if (sineWaveAngle >= 360.0f)
	{
		sineWaveAngle = 0.0f;
	}
}
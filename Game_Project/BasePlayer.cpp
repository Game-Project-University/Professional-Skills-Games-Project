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
	playerAccelrationS = 0.05f;
	//- set the max player speed
	playerMaxSpeed = 70.5f;
	//- set the max reverse player speed
	playerReverseMaxSpeed = 30.0f;
	//- set the angle of the sinewave to start at 0
	sineWaveAngle = 0;
	sineWaveValue = 0;
	//currentItem = NULL;

	checkPoint = 0;
	lap = 0;
	time = 0;
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

void CBasePlayer::IncreaseShield(int value)
{
	if (shield < 200)
	{
		shield += value;

		if (shield > 200)
		{
			shield = 200;
		}
	}
}

void CBasePlayer::DecreaseHealth(int value)
{
	if (shield > 0)
	{
		shield -= value;

		if (shield < 0)
		{
			health += shield;
			shield = 0;

			if (health < 0)
			{
				health = 0;
			}
		}
	}
	else if (health > 0)
	{
		health -= value;
		if (health < 0)
		{
			health = 0;
		}
	}
}

void CBasePlayer::RemoveShield()
{
	shield = 0;
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

void CBasePlayer::IncrementLap()
{
	lap++;
}
void CBasePlayer::IncrementCheckpoint()
{
	checkPoint++;
}

void CBasePlayer::ResetCheckpoint()
{
	checkPoint = 0;
}

void CBasePlayer::SetPosition(int value)
{
	position = value;
}

void CBasePlayer::SetLap(int value)
{
	lap = value;
}

void CBasePlayer::SetTime(int value)
{
	time = value;
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

///

Vector3 CBasePlayer::GetFacingVector()
{
	float matrix[4][4];
	playerMdl->GetMatrix(&matrix[0][0]);

	playerFacingV.x = matrix[2][0];
	playerFacingV.y = matrix[2][1];
	playerFacingV.z = matrix[2][2];

	return playerFacingV;
}

////// gun stuff

float CBasePlayer::GetFacingVectorX()
{
	float matrix[4][4];
	playerMdl->GetMatrix(&matrix[0][0]);

	playerFacingV.x = matrix[2][0];

	return playerFacingV.x;
}
float CBasePlayer::GetFacingVectorY()
{
	float matrix[4][4];
	playerMdl->GetMatrix(&matrix[0][0]);

	playerFacingV.y = matrix[2][1];

	return playerFacingV.y;
}
float CBasePlayer::GetFacingVectorZ()
{
	float matrix[4][4];
	playerMdl->GetMatrix(&matrix[0][0]);

	playerFacingV.z = matrix[2][2];

	return playerFacingV.z;
}

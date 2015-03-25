#include "BasePlayer.h"

CBasePlayer::CBasePlayer()
{
	//- set the player movement speed
	playerMovementS = 0.0f;
	//- set the player rotation speed
	playerRotationS = 100.0f;
	//- set the speed that the player accelrates
	playerAccelrationS = 0.05;
	//- set the max player speed
	playerMaxSpeed = 100.0f;
	//- set the max reverse player speed
	playerReverseMaxSpeed = 30.0f;
	//- set the angle of the sinewave to start at 0
	sineWaveAngle = 0;
	sineWaveValue = 0;
}

CBasePlayer::~CBasePlayer()
{
}
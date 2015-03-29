#pragma once
#include "Global.h"

class CBasePlayer
{
public:
	CBasePlayer();
	~CBasePlayer();

private:

protected:
	//- set the player movement speed
	float playerMovementS;
	//- set the player rotation speed
	float playerRotationS;
	//- set the speed that the player accelrates
	float playerAccelrationS;
	//- set the max player speed
	float playerMaxSpeed;
	//- set the max reverse player speed
	float playerReverseMaxSpeed;
	//- set the angle of the sinewave to start at 0
	float sineWaveAngle;
	float sineWaveValue;

};
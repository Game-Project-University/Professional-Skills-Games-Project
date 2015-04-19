#pragma once
#include "Global.h"
//#include "BaseItem.h"

class CBasePlayer
{
protected:
	IModel* playerMdl;
	//CBaseItem* currentItem;
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
	int health;
	int shield;

public:
	CBasePlayer();
	~CBasePlayer();

	///////////////
	//--GETTERS--//
	inline IModel* GetModel(){ return playerMdl; };
	inline float GetPlayerS(){ return playerMovementS; };
	inline int GetPlayerHealth(){ return health; };

	//////////////
	//--SETTERS--//
	void SetMovementSpeed(float value);
	void IncreaseHealth(int value);
	void DecreaseHealth(int value);
	void ResetPlayerHealth();
	void SetPlayerPos(float x, float y, float z);

	////////////////
	//--MOVEMENT--//
	void IncreaseAccelration();
	void DecreaseAccelration();
	void SinHoverMovement(float frameTime);

	void ActivateItem();
};
#pragma once
#include "Global.h"

struct SPlayerPos
{
	float posX;
	float posY;
	float posZ;
};

class CBasePlayer
{
protected:
	IModel* playerMdl;

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


	//-- player pos accessor --//
	SPlayerPos playerPos;
	SPlayerPos playerPrevPos;

public:
	CBasePlayer();
	~CBasePlayer();

	// returns the playerpos
	inline SPlayerPos GetPlayerPos(){ return playerPos; };

	///////////////
	//--SETTERS--//
	// update the players pos
	void UpdatePlayerPos();
	// update to contain the position the player in the previous frame
	void UpdatePreviousPos();
	// set the position of the vech just before the collision so the player doesnt get stuck in the AABB
	void MoveBeforeCollision();

	///////////////
	//--GETTERS--//
	inline IModel* GetModel(){ return playerMdl; };
	inline float GetPlayerS(){ return playerMovementS; };
	inline int GetPlayerHealth(){ return health; };
	inline float GetPlayerX(){ return playerPos.posX; };
	inline float GetPlayerY(){ return playerPos.posY; };
	inline float GetPlayerZ(){ return playerPos.posZ; };

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
};
#pragma once
#include "Global.h"

struct SPlayerPos
{
	float posX;
	float posY;
	float posZ;
};

struct Vector3
{
	float x;
	float y;
	float z;
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
	int checkPoint;
	int lap;

	//-- player pos accessor --//
	SPlayerPos playerPos;
	SPlayerPos playerPrevPos;

	Vector3 playerFacingV;

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
	inline int GetPlayerShield(){ return shield; };
	inline float GetX(){ return playerPos.posX; };
	inline float GetY(){ return playerPos.posY; };
	inline float GetZ(){ return playerPos.posZ; };
	int GetCheckpoint(){ return checkPoint; };
	inline int GetLap(){ return lap; };

	//////////////
	//--SETTERS--//
	void SetMovementSpeed(float value);

	void IncreaseHealth(int value);

	void IncreaseShield(int value);

	void DecreaseHealth(int value);

	void ResetPlayerHealth();
	void SetPlayerPos(float x, float y, float z);

	void IncrementLap();
	void IncrementCheckpoint();
	void ResetCheckpoint();

	void RemoveShield();

	////////////////
	//--MOVEMENT--//
	void IncreaseAccelration();
	void DecreaseAccelration();
	void SinHoverMovement(float frameTime);

	// facing vector //

	Vector3 GetFacingVector();
};
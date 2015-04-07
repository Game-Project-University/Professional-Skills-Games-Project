#pragma once
#include "BasePlayer.h"

////////////////
//--CONSTANTS-//

/* KeyCodes*/
const EKeyCode EXIT = Key_Escape;
const EKeyCode FORWARD = Key_W;
const EKeyCode REVERSE = Key_S;
const EKeyCode LEFT = Key_A;
const EKeyCode RIGHT = Key_D;
const EKeyCode HANDBRAKE = Key_Space;

struct SPlayerPos
{
	float posX;
	float posY;
	float posZ;
};

class CPlayer : public CBasePlayer
{
private:
	ICamera* myCamera;
	
	//////////////////////////////////
	//--CAMERA MOVEMENTS VARIABLES--//
	float camerRotationS;
	float cameraMaxX;
	float cameraCounter;

	//-- player pos accessor --//
	SPlayerPos playerPos;
	SPlayerPos playerPrevPos;

public:
	CPlayer(IMesh* playerMsh);
	~CPlayer();
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

	/////////////////
	//-- GETTERS --//
	inline float GetPlayerX(){ return playerPos.posX; };
	inline float GetPlayerZ(){ return playerPos.posZ; };

	////////////////
	//--Movement--//
	void ForwardReverseMovement(float frameTime);
	void RightLeftMovement(float frameTime);	
};
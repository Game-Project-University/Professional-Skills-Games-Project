#pragma once
#include "BasePlayer.h"
#include "Global.h"

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

public:
	CPlayer(IMesh* playerMsh);
	~CPlayer();

	inline SPlayerPos GetPlayerPos(){ return playerPos; };

	///////////////
	//--SETTERS--//
	void UpdatePlayerPos();

	////////////////
	//--Movement--//
	void ForwardReverseMovement(float frameTime);
	void RightLeftMovement(float frameTime);	
};
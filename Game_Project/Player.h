#pragma once
#include "BasePlayer.h"
#include "BaseItem.h"

////////////////
//--CONSTANTS-//

/* KeyCodes*/
const EKeyCode EXIT = Key_Escape;
const EKeyCode FORWARD = Key_W;
const EKeyCode REVERSE = Key_S;
const EKeyCode LEFT = Key_A;
const EKeyCode RIGHT = Key_D;
const EKeyCode ACTIVATE = Key_Space;

class CPlayer : public CBasePlayer
{
private:
	ICamera* myCamera;

	//////////////////////////////////
	//--CAMERA MOVEMENTS VARIABLES--//
	float camerRotationS;
	float cameraMaxX;
	float cameraCounter;

public:
	CPlayer(IMesh* playerMsh);
	~CPlayer();

	inline ICamera* GetCamera(){ return myCamera; };

	////////////////
	//--Movement--//
	void ForwardReverseMovement(float frameTime);
	void RightLeftMovement(float frameTime);	
	
	///////////////////
	// activate item //
	void ActivateItem(CBaseItem* itemOwned);
};
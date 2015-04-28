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
	CGun* gun;

	//////////////////////////////////
	//--CAMERA MOVEMENTS VARIABLES--//
	float camerRotationS;
	float cameraMaxX;
	float cameraCounter;
	float timer;

	float amountRotated;
	bool TurningActive;

public:
	CPlayer(IMesh* playerMsh, int pos);
	~CPlayer();

	inline ICamera* GetCamera(){ return myCamera; };

	CGun* GetGun(){ return gun; };

	////////////////
	//--Movement--//
	void ForwardReverseMovement(float frameTime);
	void RightLeftMovement(float frameTime);	
	
	///////////////////
	// activate item //
	void ActivateItem(CBaseItem* itemOwned);

	void PlayerUpdate(float frametime);

};
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

class CPlayer : public CBasePlayer
{
private:
	IModel* playerMdl;
	ICamera* myCamera;

	//////////////////////////
	//--MOVEMENT VARIABLES--//
	//float playerMovementS;
	//float playerRotationS;
	//float playerAccelrationS;
	//float playerMaxSpeed;
	//float playerReverseMaxSpeed;

	//float sineWaveAngle;
    //float sineWaveValue;
	
	//////////////////////////////////
	//--CAMERA MOVEMENTS VARIABLES--//
	float camerRotationS;
	float cameraMaxX;
	float cameraCounter;


	//////////////////
	//--VECH ARRAY--//

public:
	CPlayer(IMesh* playerMsh);
	~CPlayer();

	///////////////
	//--GETTERS--//
	// returns the players model
	IModel* GetModel(); 

	float GetPlayerS();

	///////////////
	//--SETTERS--//
	void IncreaseAccelration();
	void DecreaseAccelration();

	////////////////
	//--Movement--//
	void ForwardReverseMovement(float frameTime);
	void RightLeftMovement(float frameTime);	

	void SinHoverMovement(float frameTime);
};
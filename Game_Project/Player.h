#pragma once
#include "Global.h"

using namespace tle;

////////////////
//--CONSTANTS-//

/* KeyCodes*/
const EKeyCode EXIT = Key_Escape;
const EKeyCode FORWARD = Key_W;
const EKeyCode REVERSE = Key_S;
const EKeyCode LEFT = Key_A;
const EKeyCode RIGHT = Key_D;

class CPlayer
{
private:
	IModel* playerMdl;

	//////////////////////////
	//--MOVEMENT VARIABLES--//
	float playerMovementS;
	float playerRotationS;
	float playerAccelrationS;
	float playerMaxSpeed;
	float playerReverseMaxSpeed;

	//////////////////
	//--VECH ARRAY--//
	std::string vechArray[6];

public:
	CPlayer(IMesh* playerMsh);
	~CPlayer();

	///////////////
	//--GETTERS--//
	// returns the players model
	IModel* GetModel(); 

	float GetPlayerS();
	float GetPlayerRotationS();

	///////////////
	//--SETTERS--//
	void IncreaseAccelration();
	void DecreaseAccelration();

	////////////////
	//--Movement--//
	void ForwardReverseMovement(float frameTime);
	void RightLeftMovement(float frameTime);	
};
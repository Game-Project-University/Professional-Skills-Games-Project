#pragma once
#include "TL-Engine.h"

using namespace tle;

class CPlayer
{
private:
	IModel* playerMdl;

	float playerMovementS;
	float playerRotationS;
	float playerAccelrationS;

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
	
};
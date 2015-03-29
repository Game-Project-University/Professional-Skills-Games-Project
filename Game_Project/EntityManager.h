#pragma once
#include "Player.h"
#include "AI.h"
#include "Global.h"

// - This class is used to store the instance of the player class and the player is created when the EntityManager is created
class CEntityManager
{
public:
	// The selected vech gets passed into this constructor
	CEntityManager(IMesh* modelMsh);
	~CEntityManager();
	
	// returns the instance of the class
	CPlayer* GetPlayerInstance(){ return mPlayer; };

private:
	// pointer to the place class
	CPlayer* mPlayer;
	

};
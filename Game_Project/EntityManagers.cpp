#include "EntityManager.h"

CEntityManager::CEntityManager(IMesh* modelMsh)
{
	// create an instance of the player class and send over the selected vechicle 
	mPlayer = new CPlayer(modelMsh);
}

CEntityManager::~CEntityManager()
{
}
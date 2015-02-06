#include "Player.h"

///////////////////
//--CONTRUCTORS--//
CPlayer::CPlayer(IMesh* playerMsh)
{
	//- set the player movement speed
	playerMovementS = 0.0f;
	//- set the player rotation speed
	playerRotationS = 100.0f;
	//- set the speed that the player accelrates
	playerAccelrationS = 0.005;

	playerMdl = playerMsh->CreateModel(0.0f, 1.0f, 0.0f);
	playerMdl->Scale(3);
}

//////////////////
//--DESTRUCTOR--//
CPlayer::~CPlayer()
{

}

///////////////
//--GETTERS--//
IModel* CPlayer::GetModel()
{
	return playerMdl;
}

float CPlayer::GetPlayerS()
{
	return playerMovementS;
}

float CPlayer::GetPlayerRotationS()
{
	return playerRotationS;
}

//////////////////
//--SETTERS--//
void CPlayer::IncreaseAccelration()
{
	playerMovementS+= playerAccelrationS;
}

void CPlayer::DecreaseAccelration()
{
	playerMovementS -= playerAccelrationS*2;
}
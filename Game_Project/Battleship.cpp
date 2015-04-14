#include "Battleship.h"
IMesh* CBattleShip::battleShipMsh = nullptr;

CBattleShip::CBattleShip(float x, float y, float z, float width, float length) : CObject(x, y, z, width, length)
{
	//-- ship in course we can do somthing with --//
	objectMdl = battleShipMsh->CreateModel(x, y, z);
	objectMdl->Scale(4);
}

CBattleShip::~CBattleShip()
{
}
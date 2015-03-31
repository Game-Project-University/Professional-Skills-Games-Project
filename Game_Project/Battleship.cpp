#include "Battleship.h"

CBattleShip::CBattleShip(float x, float y, float z, float width, float length) : CObject(x, y, z, width, length)
{
	//-- ship in course we can do somthing with --//
	battleShipMsh = myEngine->LoadMesh("Spaceship01Battlecruiser.x");
	objectMdl = battleShipMsh->CreateModel(x, y, z);
	objectMdl->Scale(4);
}

CBattleShip::~CBattleShip()
{
}
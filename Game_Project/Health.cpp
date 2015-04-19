#include "Health.h"

// Constructor
CHealth::CHealth(IMesh* itemMsh, float sine, float x, float y, float z)
{
	itemMdl = itemMsh->CreateModel(x, y, z);
	itemMdl->Scale(0.2);
	itemPos.posX = x;
	itemPos.posX = y;
	itemPos.posX = z;
	pickedUp = false;

	sineWaveAngle = sine;
	sineWaveValue = 0;
}
// Destructor
CHealth::~CHealth()
{
}

void CHealth::Activate(CBasePlayer* currentPlayer)
{
	currentPlayer->IncreaseHealth(50);
}
#include "Health.h"

// Constructor
CHealth::CHealth(IMesh* itemMsh, float sine, float x, float y, float z)
{
	itemMdl = itemMsh->CreateModel(x, y, z);
	itemMdl->Scale(0.1);
	itemPos.posX = x;
	itemPos.posX = y;
	itemPos.posX = z;
	pickedUp = false;
	used = false;
	usable = false;
	sineWaveAngle = sine;
	sineWaveValue = 0;
}
// Destructor
CHealth::~CHealth()
{
}

void CHealth::Activate()
{
	mOwner->IncreaseHealth(50);
	used = true;
}
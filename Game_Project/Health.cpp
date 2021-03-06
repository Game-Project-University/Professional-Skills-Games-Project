#include "Health.h"

// Constructor
CHealth::CHealth(IMesh* itemMsh, float sine, float x, float y, float z, string itemtype) : CBaseItem(itemtype)
{
	itemMdl = itemMsh->CreateModel(x, y, z);
	itemMdl->Scale(0.04);
	itemMdl->RotateLocalX(180);
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
	mOwner->IncreaseHealth(20);
	used = true;
}
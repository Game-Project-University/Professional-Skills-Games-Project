#include "Speed.h"

// Constructor
CSpeed::CSpeed(IMesh* itemMsh, float sine, float x, float y, float z, string itemtype) : CBaseItem(itemtype)
{
	itemMdl = itemMsh->CreateModel(x, y, z);
	itemMdl->Scale(3);
	itemPos.posX = x;
	itemPos.posX = y;
	itemPos.posX = z;
	pickedUp = false;
	used = false;
	usable = true;
	sineWaveAngle = sine;
	sineWaveValue = 0;
}
// Destructor
CSpeed::~CSpeed()
{
}

void CSpeed::Activate()
{
	mOwner->SetMovementSpeed(mOwner->GetPlayerS()+100);
	used = true;
}
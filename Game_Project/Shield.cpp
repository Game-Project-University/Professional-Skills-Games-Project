#include "Shield.h"

// Constructor
CShield::CShield(IMesh* itemMsh, float sine, float x, float y, float z, string itemtype) : CBaseItem(itemtype)
{
	itemMdl = itemMsh->CreateModel(x, y, z);
	itemMdl->Scale(0.15);
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
CShield::~CShield()
{
}

void CShield::Activate()
{
	mOwner->IncreaseShield(50);
	used = true;
}
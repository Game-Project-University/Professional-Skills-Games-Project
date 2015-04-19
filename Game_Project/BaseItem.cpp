#include "BaseItem.h"

CBaseItem::CBaseItem()
{
	mOwner = nullptr;
}

CBaseItem::~CBaseItem()
{
}

void CBaseItem::Activate()
{
}

////////////////
//--MOVEMENT--//
void CBaseItem::SinHoverMovement(float frameTime)
{
	sineWaveAngle += frameTime * 3;
	sineWaveValue = sin(sineWaveAngle + 1.0f);

	itemMdl->SetY(sineWaveValue + 1.0f);

	itemMdl->RotateLocalY(0.02);

	if (sineWaveAngle >= 360.0f)
	{
		sineWaveAngle = 0.0f;
	}
}


void CBaseItem::Collide()
{
	while(pickedUp == false)
	{
		itemMdl->Scale(0.0002);
		pickedUp = true;
	}
}
#include "BaseItem.h"

CBaseItem::CBaseItem(IMesh* itemMsh, float sine, float x, float y, float z)
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

CBaseItem::CBaseItem()
{

}

CBaseItem::~CBaseItem()
{
}

void CBaseItem::Activate(CBasePlayer* currentPlayer)
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
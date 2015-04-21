#pragma once
#include "Global.h"
#include "BaseItem.h"
#include "BasePlayer.h"

class CSpeed : public CBaseItem
{
	// Public Member Functions
public:
	CSpeed(IMesh* itemMsh, float sine, float x, float y, float z, string itemtype);
	~CSpeed();
	void Activate();
};
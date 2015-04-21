#pragma once
#include "Global.h"
#include "BaseItem.h"
#include "BasePlayer.h"

class CHealth : public CBaseItem
{
	// Public Member Functions
public:
	CHealth(IMesh* itemMsh, float sine, float x, float y, float z, string itemtype);
	~CHealth();
	void Activate();
};
#pragma once
#include "Global.h"
#include "BaseItem.h"
#include "BasePlayer.h"

class CShield : public CBaseItem
{
	// Public Member Functions
public:
	CShield(IMesh* itemMsh, float sine, float x, float y, float z, string itemtype);
	~CShield();
	void Activate();
};
#pragma once
#include "Global.h"
#include "BasePlayer.h"

struct SItemPos
{
	float posX;
	float posY;
	float posZ;
};

class CBaseItem
{
protected:
	// store who owns the item
	CBasePlayer* mOwner;

	IModel* itemMdl;
	SItemPos itemPos;
	float sineWaveAngle;
	float sineWaveValue;
	bool pickedUp;
	bool used;
	bool usable;

public:
	CBaseItem();
	virtual ~CBaseItem();

	// Activates item
	// set the owner of the item
	void SetOwner(CBasePlayer* owner){ mOwner = owner; };
	CBasePlayer* GetOwner(){ return mOwner; };

	virtual void Activate() = 0;

	///////////////
	//--GETTERS--//
	inline IModel* GetModel(){ return itemMdl; };
	inline bool GetState(){ return pickedUp; };
	inline bool GetUsed(){ return used; };
	inline bool GetUsable(){ return usable; };

	////////////////
	//--MOVEMENT--//
	void SinHoverMovement(float frameTime);

	void Collide();

	inline float GetX(){ return itemMdl->GetX(); };
	inline float GetZ(){ return itemMdl->GetZ(); };
};
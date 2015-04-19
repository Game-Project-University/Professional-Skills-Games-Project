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
	IModel* itemMdl;
	SItemPos itemPos;
	float sineWaveAngle;
	float sineWaveValue;
	bool pickedUp;

public:
	CBaseItem(IMesh* itemMsh, float sine, float x, float y, float z);
	CBaseItem();
	virtual ~CBaseItem();

	// Activates item
	virtual void Activate(CBasePlayer* currentPlayer) = 0;

	///////////////
	//--GETTERS--//
	inline IModel* GetModel(){ return itemMdl; };
	inline bool GetState(){ return pickedUp; };
	
	////////////////
	//--MOVEMENT--//
	void SinHoverMovement(float frameTime);

	void Collide();

	inline float GetX(){ return itemMdl->GetX(); };
	inline float GetZ(){ return itemMdl->GetZ(); };
};
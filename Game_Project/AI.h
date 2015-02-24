#pragma once
#include "Global.h"

using namespace tle;

class CAI
{
private:
	IModel* aiMdl;
	int aiCurrentWaypoint;

	//////////////////////////
	//--MOVEMENT VARIABLES--//
	float aiMovementS;
	float aiAccelrationS;
	float aiMaxSpeed;
	float sineWaveAngle;
	float sineWaveValue;

	float wayVectorX;
	float wayVectorZ;
	float distance;

public:
	CAI(IMesh* aiMsh);
	~CAI();

	///////////////
	//--GETTERS--//
	// returns the AIs model
	IModel* GetModel();
	float GetAIS();

	///////////////
	//--SETTERS--//
	void IncreaseAccelration();
	void DecreaseAccelration();
	void SetSpeed(float speed);
	void SetSine(float sine);
	void SetLocation(float x, float y, float z);

	////////////////
	//--Movement--//
	void MoveToWaypoint(float frameTime, IModel* waypoints[]);
	void SinHoverMovement(float frameTime);
	void MoveToWaypoint(float frameTime);
};
#pragma once
#include "BasePlayer.h"
#include "Global.h"

using namespace tle;

class CAI : public CBasePlayer
{
private:
	int aiCurrentWaypoint;

	float wayVectorX;
	float wayVectorZ;
	float distance;

public:
	CAI(IMesh* aiMsh, float speed, float sine, float x, float y, float z);
	~CAI();

	////////////////
	//--Movement--//
	void MoveToWaypoint(float frameTime, IModel* waypoints[]);
};
#pragma once
#include "BasePlayer.h"
#include "Global.h"

using namespace tle;

class CAI : public CBasePlayer
{
private:
	int aiCurrentWaypoint;
	int aiCurrentLane;

	float wayVectorX;
	float wayVectorZ;
	float distance;

public:
	CAI(IMesh* aiMsh, float x, float y, float z, int lane);
	~CAI();

	////////////////
	//--Movement--//
	void MoveToWaypoint(float frameTime, IModel* waypoints[][MAX_WAYPOINTS]);
	void IncreaseWaypoint();
};
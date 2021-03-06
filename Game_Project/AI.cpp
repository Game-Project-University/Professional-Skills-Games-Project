#include "AI.h"

void GetVector(IModel* model1, IModel* model2, float &vectorX, float &vectorZ)
{
	//Gets the vector between two models by subtracting the X and Z values 
	vectorX = model1->GetX() - model2->GetX();
	vectorZ = model1->GetZ() - model2->GetZ();
}

float GetDistance(float X, float Z)
{
	//Returns the distance between the two positions by squaring both X and Z and then adding them together
	float distanceX;
	float distanceZ;

	distanceX = X*X;
	distanceZ = Z*Z;

	return distanceX + distanceZ;
}

///////////////////
//--CONTRUCTORS--//
CAI::CAI(IMesh* aiMsh, float x, float y, float z, int lane, int pos)
{
	//- set the ai movement speed
	playerMovementS = 0.0f;
	//- set the speed that the ai accelrates
	playerAccelrationS = 1.03f;
	//- set the max ai speed
	playerMaxSpeed = 76.0f;
	//- set the angle of the sinewave to start at 0
	sineWaveAngle = rand() % 300;
	sineWaveValue = 0;

	// create AI model
	playerMdl = aiMsh->CreateModel(x, y, z);

	wayVectorX = 0.0f;
	wayVectorZ = 0.0f;
	distance = 0.0f;

	aiCurrentWaypoint = 0;
	aiCurrentLane = lane;

	deathTimer = 0;

	position = pos;
}

//////////////////
//--DESTRUCTOR--//
CAI::~CAI()
{

}


//////////////////////
//--PLAYERMOVEMENT--//

void CAI::MoveToWaypoint(float frameTime, IModel* waypoints[][MAX_WAYPOINTS])
{
	GetVector(waypoints[aiCurrentLane][aiCurrentWaypoint], playerMdl, wayVectorX, wayVectorZ);
	distance = GetDistance(wayVectorX, wayVectorZ);

	if (distance > 0.5)
	{
		playerMdl->LookAt(waypoints[aiCurrentLane][aiCurrentWaypoint]->GetX(), playerMdl->GetY(), waypoints[aiCurrentLane][aiCurrentWaypoint]->GetZ());
	}
	else
	{
		IncreaseWaypoint();
	}
	playerMdl->MoveLocalZ(frameTime* playerMovementS);
	
	if (aiCurrentWaypoint == 4 || aiCurrentWaypoint == 5 || aiCurrentWaypoint == 7 || aiCurrentWaypoint == 8 || aiCurrentWaypoint == 11 || aiCurrentWaypoint == 12 || aiCurrentWaypoint == 21 || aiCurrentWaypoint == 22)
	{
		if (playerMovementS >= 46)
		{ 
			DecreaseAccelration();
		}
	}
	else if (playerMovementS < playerMaxSpeed)
	{
		IncreaseAccelration();
	}
}

void CAI::IncreaseWaypoint()
{
	if (aiCurrentWaypoint == MAX_WAYPOINTS - 1)
	{
		aiCurrentWaypoint = 0;
	}
	else
	{
		aiCurrentWaypoint++;
	}
}

void CAI::MoveAIBack(float value)
{
	playerMdl->MoveLocalZ(value);
}
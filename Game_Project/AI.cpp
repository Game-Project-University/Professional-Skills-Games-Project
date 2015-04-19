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
CAI::CAI(IMesh* aiMsh, float speed, float sine, float x, float y, float z)
{
	//- set the ai movement speed
	playerMovementS = speed;
	//- set the speed that the ai accelrates
	playerAccelrationS = 0.005;
	//- set the max ai speed
	playerMaxSpeed = 100.0f;
	//- set the angle of the sinewave to start at 0
	sineWaveAngle = sine;
	sineWaveValue = 0;

	// create AI model
	playerMdl = aiMsh->CreateModel(x, y, z);

	wayVectorX = 0.0f;
	wayVectorZ = 0.0f;
	distance = 0.0f;

	aiCurrentWaypoint = 0;
}

//////////////////
//--DESTRUCTOR--//
CAI::~CAI()
{

}


//////////////////////
//--PLAYERMOVEMENT--//

void CAI::MoveToWaypoint(float frameTime, IModel* waypoints[])
{
	GetVector(waypoints[aiCurrentWaypoint], playerMdl, wayVectorX, wayVectorZ);
	distance = GetDistance(wayVectorX, wayVectorZ);

	if (distance > 0.5)
	{
		playerMdl->LookAt(waypoints[aiCurrentWaypoint]->GetX(), playerMdl->GetY(), waypoints[aiCurrentWaypoint]->GetZ());
	}
	else
	{
		IncreaseWaypoint();
	}
	playerMdl->MoveLocalZ(frameTime* playerMovementS);
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
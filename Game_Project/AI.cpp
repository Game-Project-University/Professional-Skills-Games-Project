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
CAI::CAI(IMesh* aiMsh)
{
	//- set the ai movement speed
	aiMovementS = 0.0f;
	//- set the speed that the ai accelrates
	aiAccelrationS = 0.005;
	//- set the max ai speed
	aiMaxSpeed = 100.0f;
	//- set the angle of the sinewave to start at 0
	sineWaveAngle = 0;
	sineWaveValue = 0;

	// create AI model
	aiMdl = aiMsh->CreateModel(0.0f, 1.0f, 0.0f);

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

///////////////
//--GETTERS--//
IModel* CAI::GetModel()
{
	return aiMdl;
}

float CAI::GetAIS()
{
	return aiMovementS;
}

///////////////
//--SETTERS--//
void CAI::IncreaseAccelration()
{
	aiMovementS += aiAccelrationS;
}

void CAI::DecreaseAccelration()
{
	aiMovementS -= aiAccelrationS * 2;
}

void CAI::SetLocation(float x, float y, float z)
{
	aiMdl->SetPosition(x, y, z);
}

void CAI::SetSine(float sine)
{
	sineWaveAngle = sine;
}


void CAI::SetSpeed(float speed)
{
	aiMovementS = speed;
}


//////////////////////
//--PLAYERMOVEMENT--//
void CAI::SinHoverMovement(float frameTime)
{
	sineWaveAngle += frameTime;
	sineWaveValue = sin(sineWaveAngle + 1.0f);

	aiMdl->SetY(sineWaveValue + 1.0f);

	if (sineWaveAngle >= 360.0f)
	{
		sineWaveAngle = 0.0f;
	}
}

void CAI::MoveToWaypoint(float frameTime, IModel* waypoints[])
{
	GetVector(waypoints[aiCurrentWaypoint], aiMdl, wayVectorX, wayVectorZ);
	distance = GetDistance(wayVectorX, wayVectorZ);



	if (distance > 0.5)
	{
		aiMdl->LookAt(waypoints[aiCurrentWaypoint]->GetX(), aiMdl->GetY(), waypoints[aiCurrentWaypoint]->GetZ());
	}
	else
	{
		if (aiCurrentWaypoint == 4)
		{
			aiCurrentWaypoint = 0;
		}
		else
		{
			aiCurrentWaypoint++;
		}
	}
	aiMdl->MoveLocalZ(frameTime* aiMovementS);
}
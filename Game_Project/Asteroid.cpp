#include "Asteroid.h"

IMesh* CAsteroid::asteroidMsh = nullptr;
IMesh* CAsteroid::outerMsh = nullptr;

CAsteroid::CAsteroid()
{
	asteroidMdl = asteroidMsh->CreateModel(0, -200, 0);
	asteroidMdl->Scale(0.5f);
	asteroidPositionReset = false;
	outerMdl = outerMsh->CreateModel(0, 0, 0);
	outerMdl->AttachToParent(asteroidMdl);
	outerMdl->SetSkin("Fire2_tlxadd.jpg");
	outerMdl->Scale(1.3f);
	outerMdl->ScaleX(1.6f);
	asteroidMdl->RotateLocalZ(90);
	assFire = new CAsteroidFireSystem();
}

CAsteroid::~CAsteroid()
{

}

float CAsteroid::GenerateRandomFloat(float rangeMin, float rangeMax)
{
	float result = (float)rand() / (float)(RAND_MAX + 1);
	result *= (float)(rangeMax - rangeMin);
	result += rangeMin;
	return result;
}

void CAsteroid::MoveOffTheTrack()
{
	asteroidMdl->SetPosition(0, -200, 0);
	assFire->MoveOffTheTrack();
}

void CAsteroid::ResetAsteroidPosition()
{
	asteroidMdl->SetPosition(GenerateRandomFloat(-120.0f, 500.0f), GenerateRandomFloat(200.0f, 500.0f), GenerateRandomFloat(-700.0f, 350.0f));
	//asteroidMdl->SetPosition(GenerateRandomFloat(-50.0f, 50.0f), GenerateRandomFloat(200.0f, 500.0f), GenerateRandomFloat(-100.0f, 100.0f));
	fallSpeed = GenerateRandomFloat(150.0f, 200.0f);
	asteroidMdl->RotateZ(GenerateRandomFloat(-10.0f, 10.0f));
}

void CAsteroid::Update(float frameTime, CPlayer* playerPtr, CSound* asteroidHit)
{
	if (asteroidPositionReset == false)
	{
		ResetAsteroidPosition();
		asteroidPositionReset = true;
	}

	asteroidMdl->MoveY(-(fallSpeed * frameTime));
	outerMdl->RotateY(500.0f * frameTime);
	assFire->update(frameTime, asteroidMdl, playerPtr);

	if (asteroidMdl->GetY() <= 0.0f)
	{
		float x = asteroidMdl->GetLocalX() - playerPtr->GetModel()->GetLocalX();
		float z = asteroidMdl->GetLocalZ() - playerPtr->GetModel()->GetLocalZ();
		float collisionDist = sqrt(x*x + z*z);
		if (collisionDist < 65.0f)
		{
			asteroidHit->PlaySound();
		}
		asteroidPositionReset = false;
	}
}

IModel* CAsteroid::GetModel()
{
	return asteroidMdl;
}



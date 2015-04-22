#include "SmokeSystem.h"

IMesh* CSmokeSystem::particleMsh = nullptr;

CSmokeSystem::CSmokeSystem() : CBaseParticle()
{
	for (int i = 0; i < AMOUNT_OF_PARTICLES; i++)
	{
		particleArray[i].mPartMdl = particleMsh->CreateModel(0, 0, 0);
		particleArray[i].mVelocity = 70.0f;
		particleArray[i].mLifeTime = 0.0f;
		particleArray[i].mlifeSpan = random(2.0f, 9.0f);
		particleArray[i].mPartMdl->Scale(0.1);
	}
}

CSmokeSystem::~CSmokeSystem()
{
	for (int i = 0; i < AMOUNT_OF_PARTICLES; i++)
	{
		IMesh* pMesh = particleArray[i].mPartMdl->GetMesh();
		pMesh->RemoveModel(particleArray[i].mPartMdl);
	}
	
}

void CSmokeSystem::update(float frametime, CPlayer* playerPtr)
{
	for (int i = 0; i < AMOUNT_OF_PARTICLES; i++)
	{
		if (particleArray[i].mLifeTime > particleArray[i].mlifeSpan)
		{
			particleArray[i].mPartMdl->SetPosition(playerPtr->GetX(), playerPtr->GetY(), playerPtr->GetZ());
			particleArray[i].mDirX = random(-5, 5);
			particleArray[i].mVelocity = random(5, 7);
			particleArray[i].mLifeTime = 0.0f * frametime;	
		}
		else
		{
			particleArray[i].mPartMdl->MoveX(particleArray[i].mDirX * frametime);
			particleArray[i].mPartMdl->MoveY(particleArray[i].mVelocity * frametime);
			particleArray[i].mLifeTime += 2 * frametime;
			particleArray[i].mPartMdl->LookAt(playerPtr->GetCamera());
			particleArray[i].mPartMdl->Scale(0.3);
		}
	}
}
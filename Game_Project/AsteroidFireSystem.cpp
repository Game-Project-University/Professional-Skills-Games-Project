#include "AsteroidFireSystem.h"

IMesh* CAsteroidFireSystem::assFireParticleMsh = nullptr;

CAsteroidFireSystem::CAsteroidFireSystem() : CBaseParticle()
{
	for (int i = 0; i < AMOUNT_OF_ASS_FIRE; i++)
	{
		assFireParticleArray[i].mPartMdl = assFireParticleMsh->CreateModel(0, -200, 0);
		assFireParticleArray[i].mVelocity = 200.0f;
		assFireParticleArray[i].mLifeTime = 0.0f;
		assFireParticleArray[i].mlifeSpan = random(0.5f, 1.0f);
		assFireParticleArray[i].mPartMdl->Scale(0.075f);
		assFireParticleArray[i].mPartMdl->SetSkin("Fire2_tlxadd.jpg");
	}
}

CAsteroidFireSystem::~CAsteroidFireSystem()
{
	for (int i = 0; i < AMOUNT_OF_ASS_FIRE; i++)
	{
		IMesh* pMesh = assFireParticleArray[i].mPartMdl->GetMesh();
		pMesh->RemoveModel(assFireParticleArray[i].mPartMdl);
	}

}

void CAsteroidFireSystem::update(float frametime, IModel* ass, CPlayer* playerPtr)
{
	for (int i = 0; i < AMOUNT_OF_ASS_FIRE; i++)
	{
		if (assFireParticleArray[i].mLifeTime > assFireParticleArray[i].mlifeSpan)
		{
			assFireParticleArray[i].mPartMdl->SetPosition(random(ass->GetX() - 2, ass->GetX() + 2), ass->GetY(), random(ass->GetZ() - 2, ass->GetZ() + 2));
			assFireParticleArray[i].mDirX = random(-5, 5);
			assFireParticleArray[i].mVelocity = random(50, 100);
			assFireParticleArray[i].mLifeTime = 0.0f * frametime;
		}
		else
		{
			assFireParticleArray[i].mPartMdl->MoveX(assFireParticleArray[i].mDirX * frametime);
			assFireParticleArray[i].mPartMdl->MoveY(assFireParticleArray[i].mVelocity * frametime);
			assFireParticleArray[i].mLifeTime += 2 * frametime;
			assFireParticleArray[i].mPartMdl->LookAt(playerPtr->GetCamera());
			assFireParticleArray[i].mPartMdl->Scale(0.075f);
		}
	}
}

void CAsteroidFireSystem::MoveOffTheTrack()
{
	for (int i = 0; i < AMOUNT_OF_ASS_FIRE; i++)
	{
		assFireParticleArray[i].mPartMdl->SetPosition(0, -200, 0);
	}
}
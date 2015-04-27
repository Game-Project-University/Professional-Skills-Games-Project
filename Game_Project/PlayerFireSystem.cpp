#include "PlayerFireSystem.h"

IMesh* CFireSystem::particleMsh = nullptr;

CFireSystem::CFireSystem() : CBaseParticle()
{
	for (int i = 0; i < fireNo; i++)
	{
		particleArray[i].mPartMdl = particleMsh->CreateModel(0, 0, 0);
		particleArray[i].mVelocity = 70.0f;
		particleArray[i].mLifeTime = 0.0f;
		particleArray[i].mlifeSpan = random(0.2f, 3.0);
		particleArray[i].mPartMdl->Scale(0.05);
		particleArray[i].mPartMdl->SetSkin("blockhole.jpg");
	}
}

CFireSystem::~CFireSystem()
{
	for (int i = 0; i < fireNo; i++)
	{
		IMesh* pMesh = particleArray[i].mPartMdl->GetMesh();
		pMesh->RemoveModel(particleArray[i].mPartMdl);
	}

}

void CFireSystem::update(float frametime, CPlayer* playerPtr)
{
	int speed = 0;
	if (playerPtr->GetPlayerS() >= 0)
		speed = (int)(playerPtr->GetPlayerS() + 0.5);
	else
		speed = (int)(playerPtr->GetPlayerS() - 0.5);


	for (int i = 0; i < fireNo; i++)
	{
		//if (i < speed)
		//{
			if (particleArray[i].mLifeTime > particleArray[i].mlifeSpan)
			{
				particleArray[i].mPartMdl->SetPosition(playerPtr->GetX(), random(playerPtr->GetY()- 0.5f, playerPtr->GetY() + 0.5f), playerPtr->GetZ());
				particleArray[i].mDirX = random(-400, 400);
				particleArray[i].mDirY = random(-400, 0);
				particleArray[i].mDirZ = random(1000, 2000);
				particleArray[i].mLifeTime = 0.0f;
				particleArray[i].mPartMdl->LookAt(playerPtr->GetCamera());
				particleArray[i].mPartMdl->Scale(0.03);
			}
			else
			{
				//particleArray[i].mPartMdl->RotateLocalX(random(-500, 500) * frametime);
				//particleArray[i].mPartMdl->RotateLocalY(random(-250, 250) * frametime);
				particleArray[i].mPartMdl->MoveLocalZ(particleArray[i].mDirZ * frametime);
				particleArray[i].mPartMdl->MoveLocalY(particleArray[i].mDirY * frametime);
				particleArray[i].mPartMdl->MoveLocalX(particleArray[i].mDirX * frametime);
				//particleArray[i].mPartMdl->MoveY(particleArray[i].mVelocity * frametime);
				particleArray[i].mLifeTime += 10 * frametime;
				
				//particleArray[i].mPartMdl->Scale(0.055);
				//particleArray[i].mPartMdl->RotateLocalX(random(-500, 500) * frametime);
				//particleArray[i].mPartMdl->RotateLocalY(random(-250, 250) * frametime);
			}
		//}
		//else
		//	particleArray[i].mPartMdl->SetPosition(playerPtr->GetX(), playerPtr->GetY(), playerPtr->GetZ());
	}
}






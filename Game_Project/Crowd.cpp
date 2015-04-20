#include "Crowd.h"

IMesh* CCrowd::crowdMsh = nullptr;

CCrowd::CCrowd(float x, float y, float z)
{
	crowdMdl[0] = crowdMsh->CreateModel(x, y, z);
	crowdMdl[0]->Scale(1.5f);
	crowdMdl[1] = crowdMsh->CreateModel(x + 2.2f, y, z - 2.0f);
	crowdMdl[1]->Scale(1.5f);
	crowdMdl[2] = crowdMsh->CreateModel(x + 1.8f, y, z + 2.5f);
	crowdMdl[2]->Scale(1.5f);
	crowdMdl[3] = crowdMsh->CreateModel(x - 1.5f, y, z + 1.5f);
	crowdMdl[3]->Scale(1.5f);
	originX = x;
	originY = y;
	originZ = z;
}

CCrowd::~CCrowd()
{

}

void CCrowd::update(float frametime, CPlayer* playerPtr)
{
	for (int i = 0; i < 4; i++)
	{
		crowdMdl[i]->LookAt(playerPtr->GetModel());
		crowdMdl[i]->Scale(1.5f);
	}
	float x = crowdMdl[0]->GetLocalX() - playerPtr->GetModel()->GetLocalX();
	float y = crowdMdl[0]->GetLocalY() - playerPtr->GetModel()->GetLocalY();
	float z = crowdMdl[0]->GetLocalZ() - playerPtr->GetModel()->GetLocalZ();
	float collisionDist = sqrt(x*x + y*y + z*z);
	if (collisionDist < 10.0f)
	{
		// Collision occurred
		for (int i = 0; i < 4; i++)
		{
			crowdMdl[i]->MoveLocalZ(-(5.0f * frametime));
			if (crowdMdl[i]->GetY() > 0.25)
			{
				crowdMdl[i]->MoveY(-5.0f * frametime);
			}
			if (crowdMdl[i]->GetY() < -0.25)
			{
				crowdMdl[i]->MoveY(5.0f * frametime);
			}
		}
	}
	else
	{
		if (crowdMdl[0]->GetLocalX() < (originX - 0.2f))
			crowdMdl[0]->MoveX(5.0f * frametime);
		if (crowdMdl[0]->GetLocalX() > (originX + 0.2f))
			crowdMdl[0]->MoveX(-(5.0f * frametime));
		if (crowdMdl[0]->GetLocalZ() < (originZ - 0.2f))
			crowdMdl[0]->MoveZ(5.0f * frametime);
		if (crowdMdl[0]->GetLocalZ() > (originZ + 0.2f))
			crowdMdl[0]->MoveZ(-(5.0f * frametime));

		if (crowdMdl[1]->GetLocalX() < (originX - 1.2f))
			crowdMdl[1]->MoveX(5.0f * frametime);
		if (crowdMdl[1]->GetLocalX() > (originX - 0.2f))
			crowdMdl[1]->MoveX(-(5.0f * frametime));
		if (crowdMdl[1]->GetLocalZ() < (originZ - 1.2f))
			crowdMdl[1]->MoveZ(5.0f * frametime);
		if (crowdMdl[1]->GetLocalZ() > (originZ - 0.2f))
			crowdMdl[1]->MoveZ(-(5.0f * frametime));

		if (crowdMdl[2]->GetLocalX() < (originX - 1.2f))
			crowdMdl[2]->MoveX(5.0f * frametime);
		if (crowdMdl[2]->GetLocalX() > (originX - 0.2f))
			crowdMdl[2]->MoveX(-(5.0f * frametime));
		if (crowdMdl[2]->GetLocalZ() < (originZ - 0.2f))
			crowdMdl[2]->MoveZ(5.0f * frametime);
		if (crowdMdl[2]->GetLocalZ() > (originZ + 0.2f))
			crowdMdl[2]->MoveZ(-(5.0f * frametime));

		if (crowdMdl[3]->GetLocalX() < (originX - 0.2f))
			crowdMdl[3]->MoveX(5.0f * frametime);
		if (crowdMdl[3]->GetLocalX() > (originX + 0.2f))
			crowdMdl[3]->MoveX(-(5.0f * frametime));
		if (crowdMdl[3]->GetLocalZ() < (originZ - 1.2f))
			crowdMdl[3]->MoveZ(5.0f * frametime);
		if (crowdMdl[3]->GetLocalZ() > (originZ - 0.2f))
			crowdMdl[3]->MoveZ(-(5.0f * frametime));

		/*for (int i = 0; i < 4; i++)
		{
		if (crowdMdl[0]->GetLocalX() < (originX - 0.2f))
		crowdMdl[i]->MoveX(0.02f);
		if (crowdMdl[0]->GetLocalX() > (originX + 0.2f))
		crowdMdl[i]->MoveX(-(5.0f * frametime));
		if (crowdMdl[0]->GetLocalZ() < (originZ - 0.2f))
		crowdMdl[i]->MoveZ(0.02f);
		if (crowdMdl[0]->GetLocalZ() > (originZ + 0.2f))
		crowdMdl[i]->MoveZ(-(5.0f * frametime));
		}*/
	}

	for (int i = 0; i < 4; i++)
	{
		if (crowdMdl[i]->GetY() > 1)
		{
			crowdMdl[i]->MoveY(-(5.0f * frametime));
		}
		if (crowdMdl[i]->GetY() < -1)
		{
			crowdMdl[i]->MoveY(5.0f * frametime);
		}
	}

	for (int i = 0; i < 4; i++)
	{
		if (crowdMdl[i]->GetY() > 0.25)
		{
			crowdMdl[i]->MoveY(-5.0f * frametime);
		}
		if (crowdMdl[i]->GetY() < -0.25)
		{
			crowdMdl[i]->MoveY(5.0f * frametime);
		}
	}
}
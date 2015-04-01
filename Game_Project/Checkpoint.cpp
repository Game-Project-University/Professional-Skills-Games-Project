#include "Checkpoint.h"

CCheckpoint::CCheckpoint(float x, float y, float z, bool rotated)
{
	checkpointMsh = myEngine->LoadMesh("Checkpoint.x");
	checkpointMdl = checkpointMsh->CreateModel(x,y,z);
	checkpointMdl->Scale(2);

	if (rotated)
	{
		// rotate the checkpoint and give it AABB boundaries
		checkpointMdl->RotateLocalY(90);
		// left side of checkpoint
		leftPillar.minX = checkpointMdl->GetX() - 4;
		leftPillar.maxX = checkpointMdl->GetX() + 4;
		leftPillar.minZ = checkpointMdl->GetZ() - 22;
		leftPillar.maxZ = checkpointMdl->GetZ() - 13;
		// right side of checkpoint
		rightPillar.minX = checkpointMdl->GetX() - 4;
		rightPillar.maxX = checkpointMdl->GetX() + 4;
		rightPillar.minZ = checkpointMdl->GetZ() + 13;
		rightPillar.maxZ = checkpointMdl->GetZ() + 22;

	}
	else
	{
		// A none rotated checkpoint and give it AABB boundaries
		// left side of checkpoint
		leftPillar.minX = checkpointMdl->GetX() - 22;
		leftPillar.maxX = checkpointMdl->GetX() - 13;
		leftPillar.minZ = checkpointMdl->GetZ() - 4;
		leftPillar.maxZ = checkpointMdl->GetZ() + 4;

		// right side of checkpoint
		rightPillar.minX = checkpointMdl->GetX() + 13;
		rightPillar.maxX = checkpointMdl->GetX() + 22;
		rightPillar.minZ = checkpointMdl->GetZ() - 4;
		rightPillar.maxZ = checkpointMdl->GetZ() + 4;
	}
}

CCheckpoint::~CCheckpoint()
{
}
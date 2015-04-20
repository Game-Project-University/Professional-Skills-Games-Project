#include "CrowdBarrier.h"

IMesh* CCrowdBarrier::crowdBarrierMsh = nullptr;

CCrowdBarrier::CCrowdBarrier(float x, float y, float z, float width, float length, bool rotated) : CObject(x, y, z, width, length)
{
	objectMdl = crowdBarrierMsh->CreateModel(x, y, z);
	objectMdl->ScaleY(0.2f);
	objectMdl->ScaleX(0.25);
	objectMdl->ScaleZ(0.3f);
	objectMdl->SetSkin("heli.jpg");
	if (rotated)
		objectMdl->RotateLocalY(180);
}

CCrowdBarrier::~CCrowdBarrier()
{
}
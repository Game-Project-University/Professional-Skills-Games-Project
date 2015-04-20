#include "CrowdWall.h"

IMesh* CCrowdWall::crowdWallMsh = nullptr;

CCrowdWall::CCrowdWall(float x, float y, float z, float width, float length, bool rotated) : CObject(x, y, z, width, length)
{
	objectMdl = crowdWallMsh->CreateModel(x, y, z);
	objectMdl->SetSkin("ccBar.bmp");
	if (rotated)
		objectMdl->RotateLocalY(90);
}

CCrowdWall::~CCrowdWall()
{
}
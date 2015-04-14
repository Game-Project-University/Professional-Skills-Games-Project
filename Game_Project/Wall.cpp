#include "Wallh.h"

IMesh* CWall::wallIsle = nullptr;
IMesh* CWall::wallMsh  = nullptr;

CWall::CWall(float x, float y, float z, float width, float length, bool rotated) : CObject(x, y, z, width, length)
{
	objectMdl = wallMsh->CreateModel(x, y, z);

	if (rotated)
	{
		objectMdl->RotateY(90);
		wallside1 = wallIsle->CreateModel(x - 5,y,z);
		wallside2 = wallIsle->CreateModel(x + 5,y,z);
	}
	else
	{
		wallside1 = wallIsle->CreateModel(x , y, z - 5);
		wallside2 = wallIsle->CreateModel(x , y, z + 5);
	}
	
}

CWall::~CWall()
{
}
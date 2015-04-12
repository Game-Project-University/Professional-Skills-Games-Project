#include "Wallh.h"

CWall::CWall(float x, float y, float z, float width, float length, bool rotated) : CObject(x, y, z, width, length)
{
	wallMsh = myEngine->LoadMesh("Wall.x");
	wallIsle = myEngine->LoadMesh("IsleStraight.x");

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
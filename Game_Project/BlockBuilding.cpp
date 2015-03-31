#include "BlockBuilding.h"


CBlockBuilding::CBlockBuilding(float x, float y, float z, float width, float length) : CObject(x, y, z, width, length)
{
	blockBuildingMsh = myEngine->LoadMesh("Building07.x");

	objectMdl = blockBuildingMsh->CreateModel(x, y, z);
}

CBlockBuilding::~CBlockBuilding()
{
}
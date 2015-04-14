#include "BlockBuilding.h"

IMesh* CBlockBuilding::blockBuildingMsh = nullptr;

CBlockBuilding::CBlockBuilding(float x, float y, float z, float width, float length) : CObject(x, y, z, width, length)
{
	objectMdl = blockBuildingMsh->CreateModel(x, y, z);
}

CBlockBuilding::~CBlockBuilding()
{
}
#include "PadBuilding.h"


CPadBuilding::CPadBuilding(float x, float y, float z, float width, float length) : CObject(x, y, z, width, length)
{
	padBuildingMsh = myEngine->LoadMesh("Building08.x");

	objectMdl = padBuildingMsh->CreateModel(x, y, z);
	objectMdl->RotateY(90);
}

CPadBuilding::~CPadBuilding()
{
}
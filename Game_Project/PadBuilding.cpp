#include "PadBuilding.h"

IMesh* CPadBuilding::padBuildingMsh = nullptr;

CPadBuilding::CPadBuilding(float x, float y, float z, float width, float length) : CObject(x, y, z, width, length)
{
	objectMdl = padBuildingMsh->CreateModel(x, y, z);
	objectMdl->RotateY(90);
}

CPadBuilding::~CPadBuilding()
{
}
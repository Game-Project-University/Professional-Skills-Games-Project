#include "Object.h"

CObject::CObject(float x, float y, float z)
{
	objectPosition.x = x;
	objectPosition.y = y;
	objectPosition.z = z;
}

CObject::~CObject()
{
}

void CObject::scaleModel(float value)
{
	objectMdl->Scale(value);
}
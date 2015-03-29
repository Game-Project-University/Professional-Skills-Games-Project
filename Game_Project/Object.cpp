#include "Object.h"

CObject::CObject(float posX, float posY, float posZ, float width, float length)
{
	// Halfs the width and length to get the max and min boundaries 
	float objectWidth  = width / 2;
	float objectLength = length / 2;
	// set the positions of the object
	objectPosition.x = posX;
	objectPosition.y = posY;
	objectPosition.z = posZ;
	// set the bounding boxes
	objectBoundaries.minX = objectPosition.x - objectWidth;
	objectBoundaries.maxX = objectPosition.x + objectWidth;

	objectBoundaries.minZ = objectPosition.z - objectLength;
	objectBoundaries.maxZ = objectPosition.z + objectLength;

}

CObject::~CObject()
{
}

void CObject::scaleModel(float value)
{
	objectMdl->Scale(value);
}
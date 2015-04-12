#pragma once

#include "Object.h"

class CWall : public CObject
{
public:
	CWall(float x, float y, float z, float width, float length, bool rotated);
	~CWall();

private: 
	IMesh* wallMsh;
	IMesh* wallIsle;

	IModel* wallside1;
	IModel* wallside2;
};
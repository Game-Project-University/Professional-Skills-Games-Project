#pragma once

#include "Object.h"

class CArrow
{
public:
	CArrow(float x, float y, float z, float rotation);
	~CArrow();
	static IMesh* arrowMsh;
	void update(float frametime);
	float lifeTime;
	float xPos;
	float yPos;
	float zPos;
	float direction;
private:
	IModel* arrowMdl[4];
};
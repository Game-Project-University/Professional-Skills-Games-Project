#pragma once
#include "Global.h"

class CVortex
{
public:
	CVortex(float x, float y, float z);
	~CVortex();

	//-- GETTER FUNCTIONS
	float GetX(){ return vortexMdl->GetX(); };
	float GetY(){ return vortexMdl->GetY(); };
	float GetZ(){ return vortexMdl->GetZ(); };

	void RotateVortex(float frametime);

private:
	IMesh* vortexMsh;
	IModel* vortexMdl;
};
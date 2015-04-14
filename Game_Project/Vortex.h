#pragma once
#include "Global.h"

class CVortex
{
public:
	CVortex(float x, float y, float z, bool rotated);
	~CVortex();

	//-- GETTER FUNCTIONS
	float GetX(){ return vortexMdl->GetX(); };
	float GetY(){ return vortexMdl->GetY(); };
	float GetZ(){ return vortexMdl->GetZ(); };

	void RotateVortex(float frametime);
	void Scale(float value){ vortexMdl->Scale(value); };

	static IMesh* vortexMsh;

private:
	
	IModel* vortexMdl;
};
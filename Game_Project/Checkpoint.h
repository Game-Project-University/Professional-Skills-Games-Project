#pragma once
#include "Global.h"

class CCheckpoint 
{
public:
	CCheckpoint(float x, float y, float z, bool rotated);
	~CCheckpoint();

	struct AABB
	{
		float minX;
		float maxX;
		float minZ;
		float maxZ;
	};
	
	inline AABB GetLBoundarie(){ return leftPillar; };
	inline AABB GetRBoundarie(){ return rightPillar; };

private:
	IModel* checkpointMdl;
	IMesh* checkpointMsh;

	

	AABB leftPillar;
	AABB rightPillar;
};
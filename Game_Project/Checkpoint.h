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

	IModel* GetModel(){ return checkpointMdl; };

	inline AABB GetLBoundarie(){ return leftPillar; };
	inline AABB GetRBoundarie(){ return rightPillar; };

	inline float GetX(){ return checkpointMdl->GetX(); };
	inline float GetZ(){ return checkpointMdl->GetZ(); };

	bool IsRotated(){ return rotatedCheckpoint; };

private:
	IModel* checkpointMdl;
	IMesh* checkpointMsh;

	AABB leftPillar;
	AABB rightPillar;

	bool rotatedCheckpoint;
};
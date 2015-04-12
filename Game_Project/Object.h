#pragma once

#include "Global.h"

class CObject
{
public:
	//**** STRUCT TO STORE THE POS OF THE OBJECT  ****//
	//-------------------------------------------------- 
	struct objectPos
	{
		float x;
		float y;
		float z;
	};

	//**** STRUCT TO STORE THE AABB OF THE OBJECT ****//
	//--------------------------------------------------
	struct AABB
	{
		int minX;
		int maxX;
		int minZ;
		int maxZ;
	};

	//-- the constructor sets the positions and the AABB for object being created
	CObject(float posX, float posY, float posZ, float width, float length);
	~CObject();

	//-- used to scale the model
	void scaleModel(float value);
	// returns the boundaries of the object
	inline AABB GetBoundaries(){ return objectBoundaries; };

	void ScaleX(float value){ objectMdl->ScaleX(value); };
	void ScaleZ(float value){ objectMdl->ScaleZ(value); };
	void ScaleY(float value){ objectMdl->ScaleY(value); };

private:
	

protected:
	// model for each object 
	IModel* objectMdl;
	// accessor for the poss struct
	objectPos objectPosition;
	// accessor for the AABB struct
	AABB objectBoundaries;
	
	

};
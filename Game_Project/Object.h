#pragma once

#include "Global.h"

class CObject
{
public:
	CObject(float x, float y, float z);
	~CObject();

	void scaleModel(float value);

private:
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

protected:
	// model for each object 
	IModel* objectMdl;
	// accessor for the struct
	objectPos objectPosition;
	
	

};
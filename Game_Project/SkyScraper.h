#pragma once

#include "Object.h"

class CSkyScraper : public CObject
{
public:
	//**** CONSTRUCTOR ****//
	//-----------------------
	// recieve positions for the obejct and assign them to the struct in the CObject class
	CSkyScraper(float x, float y, float z, float width, float length);
	~CSkyScraper();

	static IMesh* skyScraperMsh;
private:
	
};
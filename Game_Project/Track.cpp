#include "Track.h"

CTrack::CTrack()
{
	//-- creation of objects (x, y, z, width, height)
	//-- i will make this read in from a file eventually
	courseObjects[0] = new CSkyScraper(-40.0f,0.0f,60.0f, 48.0f, 46.0f);
	courseObjects[1] = new CSkyScraper(40.0f, 0.0f, 60.0f, 48.0f, 46.0f);
	courseObjects[2] = new CSkyScraper(-40.0f, 0.0f, 0.0f, 48.0f, 46.0f);
	courseObjects[3] = new CSkyScraper(40.0f, 0.0f, 0.0f, 48.0f, 46.0f);
}

CTrack::~CTrack()
{
	// delte the course objects
	for (int i = 0; i < NUMBER_OF_OBJECTS; i++)
	{
		delete(courseObjects[i]);
	}
	
}

void CTrack::Collision(CPlayer* cPlayer)
{
	// check for collision using AABB
	// count through and array of objects
	for (int i = 0; i < NUMBER_OF_OBJECTS; i++)
	{
		if (cPlayer->GetPlayerPos().posX > courseObjects[i]->GetBoundaries().minX && cPlayer->GetPlayerPos().posX < courseObjects[i]->GetBoundaries().maxX &&cPlayer->GetPlayerPos().posZ > courseObjects[i]->GetBoundaries().minZ && cPlayer->GetPlayerPos().posZ < courseObjects[i]->GetBoundaries().maxZ)
		{
			cout << "IN THE BOX" << endl;
		}
	}
}
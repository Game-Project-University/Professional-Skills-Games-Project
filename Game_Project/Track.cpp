#include "Track.h"

CTrack::CTrack()
{
	courseObjects[0] = new CSkyScraper(-40.0f,0.0f,60.0f);
	courseObjects[1] = new CSkyScraper(40.0f, 0.0f, 60.0f);
	courseObjects[2] = new CSkyScraper(-40.0f, 0.0f, 0.0f);
	courseObjects[3] = new CSkyScraper(40.0f, 0.0f, 0.0f);
}

CTrack::~CTrack()
{
	for (int i = 0; i < NUMBER_OF_OBJECTS; i++)
	{
		delete(courseObjects[i]);
	}
	
}
#include "SkyScraper.h"

CSkyScraper::CSkyScraper(float x, float y, float z) : CObject(x, y, z)
{
	skyScraperMsh = myEngine->LoadMesh("Building03.x");

	objectMdl = skyScraperMsh->CreateModel(objectPosition.x, objectPosition.y, objectPosition.z);
}

CSkyScraper::~CSkyScraper()
{
}
#include "SkyScraper.h"

CSkyScraper::CSkyScraper(float x, float y, float z, float width, float length) : CObject(x, y, z, width, length)
{
	skyScraperMsh = myEngine->LoadMesh("Building03.x");

	objectMdl = skyScraperMsh->CreateModel(x, y, z);
}

CSkyScraper::~CSkyScraper()
{
}
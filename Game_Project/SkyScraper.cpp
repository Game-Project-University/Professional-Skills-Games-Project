#include "SkyScraper.h"

IMesh* CSkyScraper::skyScraperMsh = nullptr;

CSkyScraper::CSkyScraper(float x, float y, float z, float width, float length) : CObject(x, y, z, width, length)
{
	objectMdl = skyScraperMsh->CreateModel(x, y, z);
}

CSkyScraper::~CSkyScraper()
{
}
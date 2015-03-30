#pragma once
#include "Object.h"
#include "SkyScraper.h"
#include "Player.h"
#include "Global.h"

const int NUMBER_OF_OBJECTS = 6;
class CTrack
{
public:
	CTrack();
	~CTrack();

	void Collision(CPlayer* cPlayer);
private:
	CObject* courseObjects[NUMBER_OF_OBJECTS];


};
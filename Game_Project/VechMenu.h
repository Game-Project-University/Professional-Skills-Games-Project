#pragma once
#include "Global.h"

using namespace tle;

struct sVechicle
{
	IMesh* vechMsh;
	IModel* vechMdl;
	bool selected;
};

class CVechMenu
{
private:
	IMesh* DummyMsh;
	IModel* centreDummy;

	int highLighted;
	float sineWaveAngle;
	float sineWaveValue;

	sVechicle vechArray[4];
public:
	CVechMenu();
	~CVechMenu();

	IModel* GetDummy(){ return centreDummy; };

	void VechSinMovements(float frametime);

};
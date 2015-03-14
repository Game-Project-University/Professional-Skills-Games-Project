#pragma once
#include "Global.h"

using namespace tle;

struct sVechicle
{
	IMesh* vechMsh;
	IModel* vechMdl;
};

class CVechMenu
{
private:
	IMesh* DummyMsh;
	IModel* centreDummy;

	int selected;
	float sineWaveAngle;
	float sineWaveValue;

	sVechicle vechArray[4];
public:
	CVechMenu();
	~CVechMenu();

	//-- GETTER FUNCTIONS --//
	//-----------------------
	IModel* GetDummy(){ return centreDummy; };
	IMesh*  GetSelected(){ return vechArray[selected].vechMsh; };

	void VechSinMovements(float frametime);
	void SetRightSelected();
	void SetLeftSelected();
};
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

	int highLighted = 0;

	sVechicle vechArray[4];
public:
	CVechMenu();
	~CVechMenu();

};
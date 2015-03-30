#include "VechMenu.h"

CVechMenu::CVechMenu()
{
	sineWaveAngle = 0;
	sineWaveValue = 0;

	DummyMsh = myEngine->LoadMesh("dummy.x");
	centreDummy = DummyMsh->CreateModel(0.0f, 0.0f, 25.0f);

	vechArray[0].vechMsh = myEngine->LoadMesh("HeliScouFighter.x");
	vechArray[1].vechMsh = myEngine->LoadMesh("HawkStarfighter.x");
	vechArray[2].vechMsh = myEngine->LoadMesh("SciFiBattleship01.x");
	vechArray[3].vechMsh = myEngine->LoadMesh("SciFiBattleship02.x");


	vechArray[0].vechMdl = vechArray[0].vechMsh->CreateModel();
	vechArray[0].vechMdl->AttachToParent(centreDummy);
	vechArray[0].vechMdl->MoveZ(-20.0f);
	vechArray[0].vechMdl->RotateLocalY(180);
	


	vechArray[1].vechMdl = vechArray[1].vechMsh->CreateModel(15.0f, 0.0f, 20.0f);
	vechArray[1].vechMdl->AttachToParent(centreDummy);
	vechArray[1].vechMdl->MoveZ(-20.0f);
	vechArray[1].vechMdl->MoveX(5.0f);
	vechArray[1].vechMdl->RotateLocalY(90);


	vechArray[2].vechMdl = vechArray[2].vechMsh->CreateModel(0.0f, 0.0f, 45.0f);
	vechArray[2].vechMdl->AttachToParent(centreDummy);
	vechArray[2].vechMdl->MoveZ(-25.0f);



	vechArray[3].vechMdl = vechArray[3].vechMsh->CreateModel(-15.0f, 0.0f, 20.0f);
	vechArray[3].vechMdl->AttachToParent(centreDummy);
	vechArray[3].vechMdl->RotateLocalY(-90);
	vechArray[3].vechMdl->MoveZ(-20.0f);

	selected = 0;
}

CVechMenu::~CVechMenu()
{
	for (int i = 0; i < 4; i++)
	{
		vechArray[i].vechMsh->RemoveModel(vechArray[i].vechMdl);
	}

}

void CVechMenu::VechSinMovements(float frameTime)
{
	sineWaveAngle += frameTime;
	sineWaveValue = sin(sineWaveAngle + 1.0f);

	for (int i = 0; i < 4; i++)
	{
		vechArray[i].vechMdl->SetY(sineWaveValue + 1.0f);
	}

	if (sineWaveAngle >= 360.0f)
	{
		sineWaveAngle = 0.0f;
	}
}

void CVechMenu::SetRightSelected()
{

	if (selected < 3)
	{
		selected++;
	}
	else
	{
		selected = 0;
	}
}

void CVechMenu::SetLeftSelected()
{
	if (selected > 0)
	{
		selected--;
	}
	else
	{
		selected = 3;
	}
}

void CVechMenu::RotateSelected(float frameTime)
{
	amountRotated = 80 * frameTime;
	vechArray[selected].vechMdl->RotateY(amountRotated);
}
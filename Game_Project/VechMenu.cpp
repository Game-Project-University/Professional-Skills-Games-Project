#include "VechMenu.h"

CVechMenu::CVechMenu()
{
	DummyMsh = myEngine->LoadMesh("dummy.x");
	centreDummy = DummyMsh->CreateModel(0.0f, 0.0f, 25.0f);

	for (int i = 0; i < 4; i++)
	{
		vechArray[i].selected = false;
	}

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
	vechArray[1].vechMdl->MoveX(15.0f);
	vechArray[1].vechMdl->MoveZ(-10.0f);
	vechArray[1].vechMdl->RotateLocalY(180);


	vechArray[2].vechMdl = vechArray[2].vechMsh->CreateModel(0.0f, 0.0f, 45.0f);
	vechArray[2].vechMdl->RotateLocalY(180);


	vechArray[3].vechMdl = vechArray[3].vechMsh->CreateModel(-15.0f, 0.0f, 20.0f);
	vechArray[3].vechMdl->RotateLocalY(180);

	highLighted = 0;
}

CVechMenu::~CVechMenu()
{
	for (int i = 0; i < 4; i++)
	{
		vechArray[i].vechMsh->RemoveModel(vechArray[i].vechMdl);
	}

}
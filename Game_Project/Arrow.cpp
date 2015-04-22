#include "Arrow.h"

IMesh* CArrow::arrowMsh = nullptr;

CArrow::CArrow(float x, float y, float z, float rotation)
{
	lifeTime = 0.0f;
	xPos = x;
	yPos = y;
	zPos = z;
	direction = rotation;

	/*arrowMdl[0] = arrowMsh->CreateModel(x, y, z);
	arrowMdl[0]->Scale(0.5f);
	arrowMdl[0]->ScaleX(0.2f);
	arrowMdl[0]->SetSkin("glass_red.jpg");
	arrowMdl[0]->RotateLocalY(rotation);

	arrowMdl[1] = arrowMsh->CreateModel(x - 2.0f, y, z + 0.2f);
	arrowMdl[1]->Scale(0.5f);
	arrowMdl[1]->ScaleX(0.2f);
	arrowMdl[1]->Scale(1.25f);
	arrowMdl[1]->ScaleX(0.2f);
	arrowMdl[1]->RotateLocalY(rotation);
	arrowMdl[1]->SetSkin("glass_green.jpg");

	arrowMdl[2] = arrowMsh->CreateModel(x - 4.0f, y, z + 0.4f);
	arrowMdl[2]->Scale(0.5f);
	arrowMdl[2]->ScaleX(0.2f);
	arrowMdl[2]->Scale(1.5f);
	arrowMdl[2]->ScaleX(0.2f);
	arrowMdl[2]->SetSkin("glass_blue.jpg");
	arrowMdl[2]->RotateLocalY(rotation);*/

	arrowMdl[0] = arrowMsh->CreateModel(x, y, z);
	arrowMdl[0]->ScaleX(0.05f);
	arrowMdl[0]->SetSkin("TribuneSeats.tga");
	arrowMdl[0]->RotateLocalY(rotation);

	if (rotation == 0.0f)
	{
		arrowMdl[1] = arrowMsh->CreateModel(x + 1.0f, y, z - 2.5f);
		arrowMdl[2] = arrowMsh->CreateModel(x + 1.0f, y, z );
		arrowMdl[3] = arrowMsh->CreateModel(x + 1.0f, y, z + 2.5f);
	}

	if (rotation == 90.0f)
	{
		arrowMdl[1] = arrowMsh->CreateModel(x - 2.5f, y, z - 1.0f);
		arrowMdl[2] = arrowMsh->CreateModel(x, y, z - 1.0f);
		arrowMdl[3] = arrowMsh->CreateModel(x + 2.5f, y, z - 1.0f);
	}

	if (rotation == 180.0f)
	{
		arrowMdl[1] = arrowMsh->CreateModel(x - 1.0f, y, z + 2.5f);
		arrowMdl[2] = arrowMsh->CreateModel(x - 1.0f, y, z );
		arrowMdl[3] = arrowMsh->CreateModel(x - 1.0f, y, z - 2.5f);
	}

	if (rotation == 270.0f)
	{
		arrowMdl[1] = arrowMsh->CreateModel(x + 2.5f, y, z - 1.0f);
		arrowMdl[2] = arrowMsh->CreateModel(x, y, z - 1.0f);
		arrowMdl[3] = arrowMsh->CreateModel(x - 2.5f, y, z - 1.0f);
	}

	arrowMdl[1]->Scale(0.25f);
	arrowMdl[1]->ScaleX(0.2f);
	arrowMdl[1]->RotateLocalY(rotation);
	arrowMdl[1]->SetSkin("glass_red.jpg");

	arrowMdl[2]->Scale(0.25f);
	arrowMdl[2]->ScaleX(0.2f);
	arrowMdl[2]->RotateLocalY(rotation);
	arrowMdl[2]->SetSkin("glass_blue.jpg");

	arrowMdl[3]->Scale(0.25f);
	arrowMdl[3]->ScaleX(0.2f);
	arrowMdl[3]->RotateLocalY(rotation);
	arrowMdl[3]->SetSkin("glass_green.jpg");
}

CArrow::~CArrow()
{

}

void CArrow::update(float frametime)
{
	lifeTime += 750.0f * frametime;

	if (direction == 0.0f)
	{
		if (lifeTime <= 100.0f)
		{
			arrowMdl[1]->SetLocalX(xPos + 0.2f);
		}
		if (lifeTime > 100.0f && lifeTime <= 200.0f)
		{
			arrowMdl[1]->SetLocalX(xPos - 0.2f);
			arrowMdl[2]->SetLocalX(xPos + 0.2f);
		}
		if (lifeTime > 200.0f && lifeTime <= 300.0f)
		{
			arrowMdl[2]->SetLocalX(xPos - 0.2f);
			arrowMdl[3]->SetLocalX(xPos + 0.2f);
		}
		if (lifeTime > 300.0f)
		{
			arrowMdl[3]->SetLocalX(xPos - 0.2f);
			lifeTime = 0.0f;
		}
	}

	if (direction == 180.0f)
	{
		if (lifeTime <= 100.0f)
		{
			arrowMdl[1]->SetLocalX(xPos - 0.2f);
		}
		if (lifeTime > 100.0f && lifeTime <= 200.0f)
		{
			arrowMdl[1]->SetLocalX(xPos + 0.2f);
			arrowMdl[2]->SetLocalX(xPos - 0.2f);
		}
		if (lifeTime > 200.0f && lifeTime <= 300.0f)
		{
			arrowMdl[2]->SetLocalX(xPos + 0.2f);
			arrowMdl[3]->SetLocalX(xPos - 0.2f);
		}
		if (lifeTime > 300.0f)
		{
			arrowMdl[3]->SetLocalX(xPos + 0.2f);
			lifeTime = 0.0f;
		}
	}

	if (direction == 270.0f || direction == 90.0f)
	{
		if (lifeTime <= 100.0f)
		{
			arrowMdl[1]->SetLocalZ(zPos - 0.2f);
		}
		if (lifeTime > 100.0f && lifeTime <= 200.0f)
		{
			arrowMdl[1]->SetLocalZ(zPos + 0.2f);
			arrowMdl[2]->SetLocalZ(zPos - 0.2f);
		}
		if (lifeTime > 200.0f && lifeTime <= 300.0f)
		{
			arrowMdl[2]->SetLocalZ(zPos + 0.2f);
			arrowMdl[3]->SetLocalZ(zPos - 0.2f);
		}
		if (lifeTime > 300.0f)
		{
			arrowMdl[3]->SetLocalZ(zPos + 0.2f);
			lifeTime = 0.0f;
		}
	}

	//lifeTime += 100.0f * frametime;
	//if (lifeTime <= 100.0f)
	//{
	//	arrowMdl[0]->SetSkin("glass_red.jpg");
	//}
	//if (lifeTime > 100.0f && lifeTime <= 200.0f)
	//{
	//	arrowMdl[0]->SetSkin("BlackBall.jpg");
	//	arrowMdl[1]->SetSkin("glass_green.jpg");	//Eats up framerate
	//}
	//if (lifeTime > 200.0f && lifeTime <= 300.0f)
	//{
	//	arrowMdl[1]->SetSkin("BlackBall.jpg");
	//	arrowMdl[2]->SetSkin("glass_blue.jpg");
	//}
	//if (lifeTime > 300.0f)
	//{
	//	arrowMdl[2]->SetSkin("BlackBall.jpg");
	//	lifeTime = 0.0f;
	//}
}
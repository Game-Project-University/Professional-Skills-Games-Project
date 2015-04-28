#include "gun.h"

IMesh* CGun::bulletMsh = nullptr;

CGun::CGun()
{
	shooting = false;
	bulletCreated = false;
	bulletSpeed = 200;

	facingX = 0;
	facingZ = 0;
}

CGun::~CGun()
{
}


void CGun::CreateBullet(float x, float y, float z)
{
	bullet = bulletMsh->CreateModel(x, y, z);
	bullet->Scale(0.08);

	bulletCreated = true;
}

void CGun::MoveBullet(float frametime)
{
	bullet->MoveX(facingX * bulletSpeed * frametime);
	bullet->MoveZ(facingZ * bulletSpeed * frametime);
}

void CGun::RemoveModel()
{
	bulletMsh->RemoveModel(bullet);
	bullet = nullptr;
}
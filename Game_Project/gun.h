#pragma once
#include "Global.h"

class CGun
{
	
public:

	static IMesh* bulletMsh;
	CGun();
	~CGun();

	bool ReturnShooting(){ return shooting; };
	bool ReturnBulletCreated(){ return bulletCreated; };

	void SetShooting(bool value){ shooting = value; };
	void SetCreatedBullet(bool value2){ bulletCreated = value2; };

	void CreateBullet(float x, float y, float z);
	void MoveBullet(float frametime);

	void RemoveModel();

	void setfacing(float x, float z){ facingX = x; facingZ = z; };

private:
	bool shooting;
	bool bulletCreated;
	float bulletSpeed;

	float facingX;
	float facingZ;

	IModel* bullet;

};
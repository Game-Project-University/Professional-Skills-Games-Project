#include "Vortex.h"

IMesh* CVortex::vortexMsh = nullptr;

CVortex::CVortex(float x, float y, float z, bool rotated)
{
	vortexMdl = vortexMsh->CreateModel(x, y, z);
	vortexMdl->SetSkin("blackhole.png");
	vortexMdl->Scale(2);
	
	//if (rotated)
	//{
	//	vortexMdl->RotateLocalY(90);
	//}
	
}

CVortex::~CVortex()
{
}

void CVortex::RotateVortex(float frametime)
{
	vortexMdl->RotateLocalZ(6.0f * frametime);
	
}

void CVortex::RotateLocalVortex(float value)
{
	vortexMdl->RotateLocalY(value);

}
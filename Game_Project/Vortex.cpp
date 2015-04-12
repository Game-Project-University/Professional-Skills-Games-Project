#include "Vortex.h"


CVortex::CVortex(float x, float y, float z, bool rotated)
{
	vortexMsh = myEngine->LoadMesh("sphere.x");

	vortexMdl = vortexMsh->CreateModel(x, y, z);
	vortexMdl->SetSkin("blockhole.jpg");
	vortexMdl->Scale(2);
	
	if (rotated)
	{
		vortexMdl->RotateLocalY(90);
	}
	
}

CVortex::~CVortex()
{
}

void CVortex::RotateVortex(float frametime)
{
	vortexMdl->RotateLocalX(300.0f * frametime);
	
}
//*************** MAIN FILE ******************//

//*******************
//  *DEVELOPERS
// - James Gregory
// -
// -
//*******************

#include <TL-Engine.h>	// TL-Engine include file and namespace

//--USING NAMESPACES--//
using namespace tle;

//--MAIN FUNCTION--//
void main()
{
	//--TL:ENGINE INITIALISATION--//
	// Create a 3D engine (using TLX engine here) and open a window for it
	I3DEngine* myEngine = New3DEngine( kTLX );
	// Create window can alter the size 
	myEngine->StartWindowed();

	//--MEDIA FILE DIRECTORIES--//
	// Add default folder for meshes and other media
	myEngine->AddMediaFolder( "C:\\ProgramData\\TL-Engine\\Media" );

	//--SCENE SETUP--//


	//--MAIN GAME LOOP--//
	while (myEngine->IsRunning())
	{
		//--DRAWN SCENE--//
		myEngine->DrawScene();

		

	}
	//--ENGINE DELETION--//
	myEngine->Delete();
}

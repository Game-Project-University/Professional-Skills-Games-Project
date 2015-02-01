//*************** MAIN FILE ******************//

//*******************
//  *DEVELOPERS
// - James Gregory
// -
// -
//*******************

//--INCLUDES--//
#include <TL-Engine.h>	// TL-Engine include file and namespace
#include <sstream>

//--USING NAMESPACES--//
using namespace tle;

//--COSTANT GLOBAL VARIABLES--//
/* KeyCodes*/
const EKeyCode EXIT = Key_Escape;
/*Font Variables*/
// Positions of the FPS Text
const float FontFpsX = 40.0f;
const float FontFpsY = 0.0f;

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
	myEngine->AddMediaFolder(".\\Media");

	//****--SCENE SETUP--****//
	//--CAMERA CREATION--//
	ICamera* myCamera = myEngine->CreateCamera(kFPS); //Creation of kFPS camera

	//--LOAD FONT--///
	stringstream interfaceText;
	IFont* MyFont = myEngine->LoadFont("Comic Sans MS", 36.0f);

	//--LOAD MESH--//

	//--FRAMETIME VARIABLE--//
	float frameTime;

	//--MAIN GAME LOOP--//
	while (myEngine->IsRunning())
	{
		//--TIMER INTIALISING--//
		frameTime = myEngine->Timer();

		//--STATS INTERFACE--//
		interfaceText << "FPS: " << 1/frameTime;
		MyFont->Draw(interfaceText.str(), FontFpsX, FontFpsY);
		interfaceText.str("");





		//--DRAWN SCENE--//
		myEngine->DrawScene();

		//--Exit Statement--//
		if (myEngine->KeyHit(EXIT))
		{
			myEngine->Stop();
		}
	}
	//--ENGINE DELETION--//
	myEngine->Delete();
}

//*************** MAIN FILE ******************//

//*******************
//  *DEVELOPERS
// - James Gregory
// - Matthew Cross
// - Michael Byrne
//*******************

// DEBUGGING //

// problem:
// file location:
// Extra info:
//*******************

//--Main Tasks--//
//- interface(Game menu / starting menu)
//- Track with vech( laps, visual map etc)

//--Extra features--//
//- Weapons
//- spped ups
//- change vechs
//- partical effect
//-
//-
//-
//-

//--Team Programming Convention--//
// any desires write below
//- 
//-
//-
//-

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
	myEngine->StartWindowed(1280, 900);

	//--MEDIA FILE DIRECTORIES--//
	// Add default folder for meshes and other media
	myEngine->AddMediaFolder( "C:\\ProgramData\\TL-Engine\\Media" );
	myEngine->AddMediaFolder(".\\Media");

	//****--SCENE SETUP--****//
	//--CAMERA CREATION--//
	ICamera* myCamera = myEngine->CreateCamera(kManual); //Creation of kFPS camera

	//--LOAD FONT--///
	stringstream interfaceText;
	IFont* MyFont = myEngine->LoadFont("Comic Sans MS", 36.0f);

	ISprite* sprite = myEngine->CreateSprite("lol.png");

	sprite->SetZ(0);

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

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
using namespace tle;

////////////////////////
//--GLOBAL VARIABLES--//

I3DEngine* myEngine;
IFont* MyFont;
ISprite* sprite;
ICamera* myCamera;

////////////////
//--CONSTANTS-//

/* KeyCodes*/
const EKeyCode EXIT = Key_Escape;

/*Font Variables*/
// Positions of the FPS Text
const float FontFpsX = 40.0f;
const float FontFpsY = 0.0f;

//////////////////////////////
//--PROGRAM SETUP/SHUTDOWN--//
bool ProgramSetup()
{
	//--TL:ENGINE INITIALISATION--//
	// Create a 3D engine (using TLX engine here) and open a window for it
	myEngine = New3DEngine(kTLX);
	// Create window can alter the size 
	if (!myEngine)
	{
		return false;
	}
	myEngine->StartWindowed(1280, 900);
	
	//--MEDIA FILE DIRECTORIES--//
	// Add default folder for meshes and other media
	myEngine->AddMediaFolder("C:\\ProgramData\\TL-Engine\\Media");
	myEngine->AddMediaFolder(".\\Media");

	return true;
}

// Shutdown for the whole program
void ProgramShutdown()
{
	//--ENGINE DELETION--//
	myEngine->Delete();
}

////////////////////////////////
//--FRONT END SETUP/SHUTDOWN--//
void FrontEndSetup()
{

}

void FrontEndUpdate()
{

}

void FrontEndShutdown()
{

}

///////////////////////////
//--GAME SETUP/SHUTDOWN--//
void GameSetup()
{
	//--LOAD MESH/SPRITES--//
	sprite = myEngine->CreateSprite("lol.png");
	sprite->SetZ(0);
	
	//--CREATE SCENE--//


	//--CAMERA CREATION--//
	myCamera = myEngine->CreateCamera(kManual); //Creation of kFPS camera

	//--LOAD FONT--///
	MyFont = myEngine->LoadFont("Comic Sans MS", 36.0f);
}

void GameUpdate()
{
	//--FRAMETIME VARIABLE--//
	float frameTime;
	//--TIMER INTIALISING--//
	frameTime = myEngine->Timer();

	//--STATS INTERFACE--//
	stringstream interfaceText;
	interfaceText << "FPS: " << 1 / frameTime;
	MyFont->Draw(interfaceText.str(), FontFpsX, FontFpsY);
	interfaceText.str("");
}

void GameShutdown()
{
	myEngine->RemoveFont(MyFont);
	myEngine->RemoveCamera(myCamera);
	myEngine->RemoveSprite(sprite);
}

//--MAIN FUNCTION--//
void main()
{
	ProgramSetup();
	
	GameSetup();

	//--MAIN GAME LOOP--//
	while (myEngine->IsRunning())
	{
		//--DRAWN SCENE--//
		myEngine->DrawScene();

		GameUpdate();

		//--Exit Statement--//
		if (myEngine->KeyHit(EXIT))
		{
			myEngine->Stop();
		}
	}

	GameShutdown();
	ProgramShutdown();
}

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
IFont* frontFont;
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
	//--LOAD MESH/SPRITES--//
	sprite = myEngine->CreateSprite("StarClouds.jpg");
	sprite->SetZ(0);

	//--LOAD FONT--///
	frontFont = myEngine->LoadFont("Comic Sans MS", 36.0f);

	//--CREATE SCENE--//

	//--CAMERA CREATION--//
	myCamera = myEngine->CreateCamera(kManual, 0.0f, 0.0f, 0.0f);
}

void FrontEndUpdate()
{
	//Draw Text
	frontFont->Draw("P to Play", 200, 200);
	frontFont->Draw("Q to Quit", 200, 250);

	//Any movements on Front End modles goes here
}

void FrontEndShutdown()
{
	//Remove everything in the setup
	myEngine->RemoveFont(frontFont);
	myEngine->RemoveSprite(sprite);
}

///////////////////////////
//--GAME SETUP/SHUTDOWN--//
void GameSetup()
{
	//--LOAD MESH/SPRITES--//
	sprite = myEngine->CreateSprite("lol.png");
	sprite->SetZ(0);

	//--LOAD FONT--///
	MyFont = myEngine->LoadFont("Comic Sans MS", 36.0f);
	
	//--CREATE SCENE--//


	//--CAMERA CREATION--//
	myCamera = myEngine->CreateCamera(kManual); //Creation of kFPS camera

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
	//Remove everything in the setup
	myEngine->RemoveFont(MyFont);
	myEngine->RemoveCamera(myCamera);
	myEngine->RemoveSprite(sprite);
}

//--MAIN FUNCTION--//
void main()
{
	ProgramSetup();
	FrontEndSetup();

	while (!myEngine->KeyHit(Key_P))
	{
		// Draw the scene
		myEngine->DrawScene();

		FrontEndUpdate();

		// Program exit
		if (myEngine->KeyHit(Key_Q) || !myEngine->IsRunning())
		{
			ProgramShutdown();
			return;
		}
	}

	FrontEndShutdown();

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

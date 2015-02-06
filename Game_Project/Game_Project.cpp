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
//- class names in format  CClassname
//- private then public in class declaration 
//-
//-

//--INCLUDES--//
#include <TL-Engine.h>	// TL-Engine include file and namespace
#include <sstream>
#include <iostream>
//- local
#include "Player.h"


using namespace tle;

////////////////////////
//--GLOBAL VARIABLES--//
I3DEngine* myEngine;
IFont* MyFont;
IFont* frontFont;
ISprite* sprite;
ICamera* myCamera;

///////////////
//--OBJECTS--//
CPlayer* cPlayer;


////////////////////
//--LOAD MESHSES--//
IMesh* playerMsh;

////////////////
//--CONSTANTS-//

/* KeyCodes*/
const EKeyCode EXIT    = Key_Escape;
const EKeyCode FORWARD = Key_W;
const EKeyCode REVERSE = Key_S;
const EKeyCode LEFT    = Key_A;
const EKeyCode RIGHT   = Key_D;

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
	myEngine->AddMediaFolder(".\\Media\\Vechs");

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
	sprite = myEngine->CreateSprite("MainMenuPic.jpg"); // random image that i had, can use this for now *** CHANGE IMAGE WE NEED A NAME ***
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
	frontFont->Draw("P to Play", 400, 400, kWhite);
	frontFont->Draw("Q to Quit", 400, 450, kWhite);

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
	// - hmmwv.x
	// - HoverTank01.x
	// - 4x4jeep.x
	// - amartin.x
	// - GMC.x
	// - volvo_nh12.x

	std::string vechName = "hmmwv.x";
	playerMsh = myEngine->LoadMesh(vechName);

	///////////////////////////////////////////////////
	IMesh* ss = myEngine->LoadMesh("skybox.X");
	IModel* jj = ss->CreateModel();
	jj->Scale(3);

	IMesh* tt = myEngine->LoadMesh("floor.x");		// THIS WILL BE REMOVED CHECKING OUT SKYMAPS
	IModel* ff = tt->CreateModel(0.0f,1.0f,0.0f);
	ff->SetSkin("ground_07.jpg");
	/////////////////////////////////////////////////////

	//--LOAD FONT--///
	MyFont = myEngine->LoadFont("Comic Sans MS", 36.0f);
	
	//--CREATE SCENE--//
	cPlayer = new CPlayer(playerMsh); // interface to playerclass // constructor creates player vech

	//--CAMERA CREATION--//
	myCamera = myEngine->CreateCamera(kFPS); //Creation of kFPS camera

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

	//--Player movement--//
	///////////////////////
	//- player movement direction dependent on what key is hit
	if (myEngine->KeyHeld(FORWARD))
	{
		cPlayer->GetModel()->MoveLocalZ(frameTime* cPlayer->GetPlayerS());
	}

	if (myEngine->KeyHeld(REVERSE))
	{
		cPlayer->GetModel()->MoveLocalZ(-frameTime* cPlayer->GetPlayerS());
	}

	if (myEngine->KeyHeld(RIGHT))
	{
		cPlayer->GetModel()->RotateLocalY(frameTime* cPlayer->GetPlayerRotationS());
	}

	if (myEngine->KeyHeld(LEFT))
	{
		cPlayer->GetModel()->RotateLocalY(-frameTime* cPlayer->GetPlayerRotationS());
	}
	

}

void GameShutdown()
{
	//Remove everything in the setup
	//- Tl Engine related
	myEngine->RemoveFont(MyFont);
	myEngine->RemoveCamera(myCamera);
	myEngine->RemoveMesh(playerMsh);
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

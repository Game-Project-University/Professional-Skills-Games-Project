////--INCLUDES--//
#include "Global.h"

//////////////////////////
////--GLOBAL VARIABLES--//
//I3DEngine* myEngine;
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
	//- Add folders for meshes and other media
	//- ALL MEDIA MUST BE LOCAL TO PROJECT NOT LINKED TO TL-FOLDER ON YOUR MACHINE
	myEngine->AddMediaFolder(".\\Media");
	myEngine->AddMediaFolder(".\\Media\\Vechs");
	myEngine->AddMediaFolder(".\\Media\\Skybox");
	myEngine->AddMediaFolder(".\\Media\\InterfaceDesigns");

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
	sprite = myEngine->CreateSprite("FrontMenu.jpg"); // random image that i had, can use this for now *** CHANGE IMAGE WE NEED A NAME ***
	sprite->SetZ(0);

	//--LOAD FONT--///
	frontFont = myEngine->LoadFont("Comic Sans MS", 36.0f);

	//--CREATE SCENE--//

	//--CAMERA CREATION--//
	myCamera = myEngine->CreateCamera(kFPS, 0.0f, 0.0f, 0.0f);

	//--SOUND--//
	CSound* MainMenuSound = new CSound(1);
	//-- source properties --//
	MainMenuSound->SetSourcePos(0.0f, 0.0f, 0.0f);
	MainMenuSound->SetSourceVel(0.0f, 0.0f, 0.0f);

	//-- listenerpos --//
	MainMenuSound->SetListenerPos(0.0f, 0.0f, 0.0f);
	MainMenuSound->SetListenerVel(0.0f, 0.0f, 0.0f);
	MainMenuSound->SetListenerOrientation(0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f);

	MainMenuSound->PlaySound();
}

void FrontEndUpdate()
{
	//Any movements on Front End modles goes here
}

void FrontEndShutdown()
{
	//Remove everything in the setup
	myEngine->RemoveFont(frontFont);
	myEngine->RemoveSprite(sprite);
	myEngine->RemoveCamera(myCamera);
}

///////////////////////////
//--GAME SETUP/SHUTDOWN--//
void GameSetup()
{
	//--LOAD MESH/SPRITES--//
	// - HeliScouFighter.x
	// - HawkStarfighter.x
	// - 
	// - 
	// - 
	// - 

	std::string vechName = "HawkStarfighter.x";
	playerMsh = myEngine->LoadMesh(vechName);

	//--CREATE SCENE--//
	cPlayer = new CPlayer(playerMsh); // interface to playerclass // constructor creates player vech // Camera creation and attachment

	///////////////////////////////////////////////////
	IMesh* ss = myEngine->LoadMesh("Skybox.x");
	IModel* jj = ss->CreateModel(0.0f,-1600.0f,0.0f);
	jj->Scale(2);
	/////////////////////////////////////////////////////

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
	MyFont->Draw(interfaceText.str(), FontFpsX, FontFpsY, kWhite);
	interfaceText.str("");

	//--Player movement--//
	///////////////////////
	//- player movement direction dependent on what key is hit
	cPlayer->GetModel()->MoveLocalZ(frameTime* cPlayer->GetPlayerS());

	if (myEngine->KeyHeld(Key_Space))
	{
		cPlayer->PullHandbrake();
	}
	else
	{
		cPlayer->ForwardReverseMovement(frameTime);
	}
	cPlayer->RightLeftMovement(frameTime);
}

void GameShutdown()
{
	//Remove everything in the setup
	//- Tl Engine related
	myEngine->RemoveFont(MyFont);
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
		if (myEngine->KeyHit(Key_Escape) || !myEngine->IsRunning())
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

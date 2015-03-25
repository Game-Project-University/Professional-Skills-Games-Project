////--INCLUDES--//
#include "Global.h"

//- local
#include "Player.h"
#include "AI.h"
#include "Sound.h"
#include "VechMenu.h"

/*-----------------------------------------------------------------------------------------
Havok include and library files
-----------------------------------------------------------------------------------------*/

//#define HK_PLATFORM_SIM // *Must* define before the includes if using the SIMD version of Havok (SIMD are advanced CPU instructions supported by all modern PCs)

// Havok has many include files - the more functions and classes you use, the more files you need to include
// Although intially less convenient, this reduces compile times over using a single catch-all include file
//#include <Common/Base/hkBase.h>
//#include <Common/Base/Memory/System/Util/hkMemoryInitUtil.h>
//#include <Common/Base/Memory/Allocator/Malloc/hkMallocAllocator.h>
//#include <Common/Base/Fwd/hkcstdio.h>
//#include <Physics2012/Dynamics/World/hkpWorld.h>
//#include <Physics2012/Collide/Dispatch/hkpAgentRegisterUtil.h>
//#include <Physics2012/Dynamics/Entity/hkpRigidBody.h>
//#include <Physics2012/Collide/Shape/Convex/Box/hkpBoxShape.h>
//#include <Common/Base/System/Init/PlatformInit.cxx>

// We "undefine" or exclude any Havok features we're not using. Havok's linking system is over-complex, these must be correct to avoid errors
//#include <Common/Base/keycode.cxx>
//#undef HK_FEATURE_PRODUCT_AI
//#undef HK_FEATURE_PRODUCT_ANIMATION
//#undef HK_FEATURE_PRODUCT_CLOTH
//#undef HK_FEATURE_PRODUCT_DESTRUCTION_2012
//#undef HK_FEATURE_PRODUCT_DESTRUCTION
//#undef HK_FEATURE_PRODUCT_BEHAVIOR
//#undef HK_FEATURE_PRODUCT_MILSIM
//#undef HK_FEATURE_PRODUCT_PHYSICS
//#define HK_EXCLUDE_FEATURE_SerializeDeprecatedPre700
//#define HK_EXCLUDE_FEATURE_RegisterVersionPatches
//#define HK_EXCLUDE_FEATURE_MemoryTracker
//#include <Common/Base/Config/hkProductFeatures.cxx>

// These are the Havok libraries that are to be linked (the Havok code basically). It is more usual to put library names in the project settings so we don't
// normally see them in the code like this - they are not needed for compiling our source, only for the link stage. However, this is a Microsoft-specific
// pragma that allows us to add libraries in a similar way to header files. It's quite convinient and especially useful for Havok with it's complex requirements
//#pragma comment(lib, "hkBase.lib")
//#pragma comment(lib, "hkSceneData.lib")
//#pragma comment(lib, "hkVisualize.lib")
//#pragma comment(lib, "hkInternal.lib")
//#pragma comment(lib, "hkSerialize.lib")
//#pragma comment(lib, "hkGeometryUtilities.lib")
//#pragma comment(lib, "hkcdInternal.lib")
//#pragma comment(lib, "hkcdCollide.lib")
//#pragma comment(lib, "hkpCollide.lib")
//#pragma comment(lib, "hkpConstraint.lib")
//#pragma comment(lib, "hkpConstraintSolver.lib")
//#pragma comment(lib, "hkpDynamics.lib")
//#pragma comment(lib, "hkpInternal.lib")
//#pragma comment(lib, "hkpUtilities.lib")
//#pragma comment(lib, "hkpVehicle.lib")

////////////////////////
//--GLOBAL VARIABLES--//
IFont* ComicSans;
IFont* frontFont;
ISprite* sprite;
ICamera* myCamera;

IModel* waypoints[5];

///////////////
//--OBJECTS--//
CPlayer* cPlayer;
CAI* cAI[4];
CVechMenu* cVMenu;

//////////////////
//-GAME STATES--//
enum GAMESTATES
{
	MAINMENU, VECHMENU, INGAME
};

GAMESTATES GAMESTATE = MAINMENU;
bool setup = false;

//////////////////////////
//--FRAMETIME VARIABLE--//
float frameTime;

////////////////////
//--LOAD MESHSES--//
IMesh* playerMsh;
IMesh* aiMsh;
IMesh* stateMsh;

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

	//-- CREATE A SKYBOX FOR THE WORLD --//
	IMesh* skyboxMsh = myEngine->LoadMesh("Skybox.x");
	IModel* skyBox = skyboxMsh->CreateModel(0.0f, -1600.0f, 0.0f);
	skyBox->Scale(2);

	return true;
}

///////////////////////
//-- MAIN SHUTDOWN --//
void ProgramShutdown()
{
	//--ENGINE DELETION--//
	myEngine->Delete();
}

/////////////////////////
//-- FRONT END SETUP --//

void FrontEndSetup()
{
	//--LOAD MESH/SPRITES--//
	sprite = myEngine->CreateSprite("Main_Menu.jpg"); // random image that i had, can use this for now *** CHANGE IMAGE WE NEED A NAME ***
	sprite->SetZ(0);

	//--LOAD FONT--///
	frontFont = myEngine->LoadFont("Comic Sans MS", 36.0f);

	//--CAMERA CREATION--//
	myCamera = myEngine->CreateCamera(kFPS, 0.0f, 0.0f, 0.0f);

	//--SOUND--//
	//CSound* MainMenuSound = new CSound(1);
	//-- source properties --//
	//MainMenuSound->SetSourcePos(0.0f, 0.0f, 0.0f);
	//MainMenuSound->SetSourceVel(0.0f, 0.0f, 0.0f);

	//-- listenerpos --//
	//MainMenuSound->SetListenerPos(0.0f, 0.0f, 0.0f);
	//MainMenuSound->SetListenerVel(0.0f, 0.0f, 0.0f);
	//MainMenuSound->SetListenerOrientation(0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f);

	//MainMenuSound->PlaySound();
}

///////////////////////////
//-- FRONTEND SHUTDOWN --//
void FrontEndShutdown()
{
	//-- Remove everything in the setup --//
	myEngine->RemoveFont(frontFont);
	myEngine->RemoveSprite(sprite);
	myEngine->RemoveCamera(myCamera);
}

/////////////////////////
//-- VECH MENU SETUP --//
void VechMenuSetup()
{
	myCamera = myEngine->CreateCamera(kManual, 0.0f, 2.0f, -10.0f);
	//- create an instance of the vech menu
	cVMenu = new CVechMenu();
}

//////////////////////////
//-- VECH MENU UPDATE --//
void VechMenuUpdate()
{
	// move all of the vechs in a wavey motion
	cVMenu->VechSinMovements(frameTime);

	// rotate to the next selectable vechicle 
	// and set the vechicle to being selected
	if (myEngine->KeyHit(Key_Right))
	{
		cVMenu->GetDummy()->RotateY(90);
		cVMenu->SetRightSelected();
	}
	if (myEngine->KeyHit(Key_Left))
	{
		cVMenu->GetDummy()->RotateY(-90);
		cVMenu->SetLeftSelected();
	}
}

////////////////////////////
//-- VECH MENU SHUTDOWN --//
void VechMenuShutdown()
{
}

////////////////////
//-- GAME SETUP --//
void GameSetup()
{
	std::string vechName = "HawkStarfighter.x";
	playerMsh = myEngine->LoadMesh(vechName);

	aiMsh = myEngine->LoadMesh(vechName);

	//-- CREATE SCENE --//
	cPlayer = new CPlayer(cVMenu->GetSelected()); // interface to playerclass // constructor creates player vech // Camera creation and attachment

	// -- Delete the Vmenu Object after the selected mesh has been passed to the player -- //
	delete(cVMenu);
	cVMenu = NULL;

	for (int i = 0; i < 4; i++)
	{
		cAI[i] = new CAI(aiMsh);
		cAI[i]->SetLocation(i, i, 1);
		cAI[i]->SetSine(rand()%300);
		cAI[i]->SetSpeed(i + 5);
	}

	stateMsh = myEngine->LoadMesh("state.x");

	float pos[2][5] = { { 0, -5, 5, 15, 10 }, { 0, 10, 15, 10, 0 } };

	for (int i = 0; i < 5; i++)
	{
		waypoints[i] = stateMsh->CreateModel(pos[0][i], 0, pos[1][i]);
	}

	//-- LOAD FONT --///
	ComicSans = myEngine->LoadFont("Comic Sans MS", 36.0f);
}

////////////////////
//-- GAMEUPDATE --//
void GameUpdate()
{	
	//-- STATS INTERFACE --//
	stringstream interfaceText;
	interfaceText << "FPS: " << 1 / frameTime;
	ComicSans->Draw(interfaceText.str(), FontFpsX, FontFpsY, kWhite);
	interfaceText.str("");

	//-- Player movement --//
	cPlayer->SinHoverMovement(frameTime);

	//- player movement direction dependent on what key is hit
	cPlayer->GetModel()->MoveLocalZ(frameTime* cPlayer->GetPlayerS());

	cPlayer->ForwardReverseMovement(frameTime);
	
	// the player can always move left or right
	cPlayer->RightLeftMovement(frameTime);

	//-- AI --//
	for (int i = 0; i < 4; i++)
	{
		cAI[i]->SinHoverMovement(frameTime);
		cAI[i]->MoveToWaypoint(frameTime, waypoints);
	}
}

///////////////////////
//-- GAME SHUTDOWN --//
void GameShutdown()
{
	//Remove everything in the setup
	//- Tl Engine related
	myEngine->RemoveFont(ComicSans);
	myEngine->RemoveMesh(playerMsh);
	myEngine->RemoveMesh(aiMsh);

	delete(cPlayer);
	cPlayer = NULL;

	for (int i = 0; i < 4; i++)
	{
		delete(cAI[i]);
	}
}

///////////////////////
//-- MAIN FUNCTION --//
void main()
{
	//-- SETUP THE TL-ENGINE AND THE INCLUDE FILES --//
	ProgramSetup();
	//-- MAIN GAME LOOP --//
	while (myEngine->IsRunning())
	{	
		//--TIMER INTIALISING--//
		frameTime = myEngine->Timer();

		//-- THE MAIN MENU STATE --//
		if (GAMESTATE == MAINMENU)
		{
			// set up the main menu
			if (setup == false)
			{
				//-- SET THE SCENE ONCE --//
				FrontEndSetup();
				// change the setup bool to show the scene has been set
				setup = true;
			}
			//-- DRAWN SCENE --//
			myEngine->DrawScene();

			// if the key P gets pressed then change to VECH SELECTION MENU
			if (myEngine->KeyHit(Key_P))
			{
				GAMESTATE = VECHMENU;
				setup = false;
				// shut down the main menu 
				FrontEndShutdown();
			}
		}
		//-- VECH MENU STATE --//
		else if (GAMESTATE == VECHMENU)
		{
			// set up the main menu
			if (setup == false)
			{
				//-- SET THE SCENE ONCE --//
				VechMenuSetup();
				// change the setup bool to show the scene has been set
				setup = true;
			}
			//-- DRAWN SCENE --//
			myEngine->DrawScene();

			VechMenuUpdate();

			// if the key P gets pressed then change to VECH SELECTION MENU
			if (myEngine->KeyHit(Key_Space))
			{
				GAMESTATE = INGAME;
				setup = false;
				// shut down the main menu 
				VechMenuShutdown();
			}
		}
		//-- IN GAME STATE --//
		else if (GAMESTATE == INGAME)
		{
			//-- SET THE SCENE ONCE --//
			if (setup == false)
			{
				GameSetup();
				// change the setup bool to show the scene has been set
				setup = true;
			}
			//--DRAWN SCENE--//
			myEngine->DrawScene();
			// update the game e.g play the game
			GameUpdate();
			// if the key 1 is pressed go back to the main menu 
			if (myEngine->KeyHit(Key_1))
			{
				GAMESTATE = MAINMENU;
				setup = false;
				// shut down the game 
				GameShutdown();
			}
		}
			
		//--Exit Statement--//
		if (myEngine->KeyHit(EXIT))
		{
			myEngine->Stop();
		}
	}
	// shut down the Tl-Engine
	ProgramShutdown();
}

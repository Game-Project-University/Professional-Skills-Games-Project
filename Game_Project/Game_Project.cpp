////--INCLUDES--//
#include "Global.h"

//- local
#include "Player.h"
#include "AI.h"
#include "Sound.h"
#include "VechMenu.h"
#include "EntityManager.h"
#include "Track.h"
#include "BaseItem.h"
#include "SmokeSystem.h"
#include "PlayerFireSystem.h"
#include "gun.h"

//gj
/*-----------------------------------------------------------------------------------------
Havok include and library files
-----------------------------------------------------------------------------------------*/
//
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
IFont* CentGoth;
IFont* CentGothMed;
IFont* CentGothLarge;
IFont* frontFont;
IFont* RaceStartFont;
ISprite* sprite;
ICamera* myCamera;
ISprite* speedSprites[200];

IModel* waypoints[MAX_LANES][MAX_WAYPOINTS];
IModel* testMdl;
IMesh* testMsh;

IModel* floorMdl;
IMesh* floorMsh;

///////////////
//--OBJECTS--//
CTrack* cTrack;
CEntityManager* cEManager;
CPlayer* cPlayer;
CAI* cAI[4];
CVechMenu* cVMenu;

//--SOUNDS--//
CSound* MainMenuSound;
CSound* SmashingSound;
CSound* ExplostionSound;
CSound* PickupSound;
CSound* CrowdSound;
bool crowdCheering = false;
float cheerTimer = 0.0f;

//-- PARTICLES --//
CFireSystem* cFire;
CSmokeSystem* cSmoke;

CFireSystem* cFire2;
CFireSystem* cFire3;
CFireSystem* cFire4;
CFireSystem* cFire5;


bool smokeActivated = false;
bool createSmoke = false;
bool shieldActivated = false;
bool createShield = false;
///////////////
//--INTERFACE--//
stringstream interfaceText;
float startingCounter = 0;
float DelayCounter = 0;
int speed = 0;

//////////////////
//-GAME STATES--//
enum GAMESTATES
{
	MAINMENU, VECHMENU, INGAME
};

enum PLAYERSTATES
{
	STARTRACE, ALIVE, DEAD, ENDRACE
};

enum RACESTATES
{
	GO, STOP
};

////////////////////
//--DEAD COUNTER--//
float deadCounter = 0;

GAMESTATES GAMESTATE = MAINMENU;
PLAYERSTATES PLAYERSTATE = STARTRACE;
RACESTATES RACESTATE = STOP;

bool setup = false;

//////////////////////////
//--FRAMETIME VARIABLE--//
float frameTime;

////////////////////
//--LOAD MESHSES--//
IMesh* playerMsh;
IMesh* aiMsh;
IMesh* stateMsh;
IMesh* shieldMsh;

/*Font Variables*/
// Positions of the FPS Text
const float FontFpsX = 15.0f;
const float FontFpsY = 5.0f;
float FontStartRaceX = 510;
float FontStartRaceY = 200;

bool wreckedText = false;

float sheildTimer = 0;
float aiDeathTimer = 0;
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
	myEngine->AddMediaFolder(".\\Media\\CourseObjects");
	myEngine->AddMediaFolder(".\\Media\\Items");

	// LOAD MESHES
	CPadBuilding::padBuildingMsh = myEngine->LoadMesh("Building08.x");
	CSkyScraper::skyScraperMsh = myEngine->LoadMesh("Building03.x");
	CVortex::vortexMsh = myEngine->LoadMesh("sphere.x");
	CWall::wallMsh = myEngine->LoadMesh("Wall.x");
	CWall::wallIsle = myEngine->LoadMesh("IsleStraight.x");
	CBlockBuilding::blockBuildingMsh = myEngine->LoadMesh("Building07.x");
	CBattleShip::battleShipMsh = myEngine->LoadMesh("Spaceship01Battlecruiser.x");
	CCrowd::crowdMsh = myEngine->LoadMesh("sierra.x");
	CCrowdBarrier::crowdBarrierMsh = myEngine->LoadMesh("Cue.x");
	CCrowdWall::crowdWallMsh = myEngine->LoadMesh("Barrier.x");
	CArrow::arrowMsh = myEngine->LoadMesh("Arrow.x");

	CFireSystem::particleMsh = myEngine->LoadMesh("Smoke2.x");
	//
	CSmokeSystem::particleMsh = myEngine->LoadMesh("Smoke.x");
	//
	CTrack::HeartMsh = myEngine->LoadMesh("heart.x");
	CTrack::SpeedMsh = myEngine->LoadMesh("PlasticDrum1.x");
	CTrack::SheildMsh = myEngine->LoadMesh("shield.x");

	CGun::bulletMsh = myEngine->LoadMesh("Bullet.x");


	
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
	frontFont = myEngine->LoadFont("arial", 36.0f);
	RaceStartFont = myEngine->LoadFont("arial", 500.0f);

	//--CAMERA CREATION--//
	myCamera = myEngine->CreateCamera(kFPS, 0.0f, 0.0f, 0.0f);

	//--SOUND--//
	MainMenuSound = new CSound(1,0.04f);
	//-- source properties --//
	MainMenuSound->SetSourcePos(0.0f, 0.0f, 0.0f);
	MainMenuSound->SetSourceVel(0.0f, 0.0f, 0.0f);

	//-- listenerpos --//
	MainMenuSound->SetListenerPos(0.0f, 0.0f, 0.0f);
	MainMenuSound->SetListenerVel(0.0f, 0.0f, 0.0f);
	MainMenuSound->SetListenerOrientation(0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f);

	MainMenuSound->PlaySound();
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

	sprite = myEngine->CreateSprite("vehicle select.png");
}

//////////////////////////
//-- VECH MENU UPDATE --//
void VechMenuUpdate()
{
	// move all of the vechs in a wavey motion
	cVMenu->VechSinMovements(frameTime);

	cVMenu->RotateSelected(frameTime);
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
	delete(sprite);
}

////////////////////
//-- GAME SETUP --//
void GameSetup()
{
	/////////////////////////////
	//--TEST THAT MODELS WORK--//
	floorMsh = myEngine->LoadMesh("Tile.x");
	floorMdl = floorMsh->CreateModel(0, -5, 0);
	floorMdl->SetSkin("Fire2_tlxadd.jpg");
	floorMdl->Scale(200);

	//////////////////////////
	//-- INGAME INTERFACE --//

	// Sheild
	sprite = myEngine->CreateSprite("Health.png");
	sprite->SetPosition(210, 735);
	sprite->SetZ(0);
	// Health
	sprite = myEngine->CreateSprite("Shield.png");
	sprite->SetPosition(210, 785);
	sprite->SetZ(0);
	// BackGround
	sprite = myEngine->CreateSprite("BigBoxLined.png");
	sprite->SetPosition(20, 670);
	sprite->SetZ(0.1);
	sprite = myEngine->CreateSprite("BigBoxLined.png");
	sprite->SetPosition(860, 20);
	sprite->SetZ(0.1);
	sprite = myEngine->CreateSprite("SpeedBackground.png");
	sprite->SetPosition(995, 801);
	sprite->SetZ(0.1);
	sprite = myEngine->CreateSprite("SpeedoBackground.png");
	sprite->SetPosition(1175, 625);
	sprite->SetZ(0.1);

	//speedSprites[i]->SetPosition(1185, 850 - (2 * i));

	// Item
	sprite = myEngine->CreateSprite("ItemSlotLarge.png");
	sprite->SetPosition(20, 20);
	sprite->SetZ(0.1);

	for (int i = 0; i < 101; i++)
	{
		speedSprites[i] = myEngine->CreateSprite("SpeedBar.png");
	}

	for (int i = 101; i < 201; i++)
	{
		speedSprites[i] = myEngine->CreateSprite("SpeedBar.png");
	}

	////////////////////////
	// -- CREATE COURSE --//
	cTrack = new CTrack();

	std::string vechName = "HawkStarfighter.x";
	aiMsh = myEngine->LoadMesh(vechName);

	//////////////////////
	//-- CREATE SCENE --//
	//Get the instance of the class from the manager class
	cPlayer = cEManager->GetPlayerInstance();

	// -- Delete the Vmenu Object after the selected mesh has been passed to the player -- //
	delete(cVMenu);
	cVMenu = NULL;

	/*for (int i = 0; i < 4; i++)
	{
		cAI[i] = new CAI(aiMsh, i + 0, rand() % 300, 0, 1, -20 );
	}*/

	cAI[0] = new CAI(aiMsh, -10, 1, -20, rand() % 4, 2);
	cAI[1] = new CAI(aiMsh,   0, 1, -30, rand() % 4, 3);
	cAI[2] = new CAI(aiMsh, -10, 1, -40, rand() % 4, 4);
	cAI[3] = new CAI(aiMsh,   0, 1, -50, rand() % 4, 5);

	stateMsh = myEngine->LoadMesh("state.x");
	//stateMsh = myEngine->LoadMesh("dummy.x");

	//Player Fire System
	cFire = new CFireSystem();

	cFire2 = new CFireSystem();
	cFire3 = new CFireSystem();
	cFire4 = new CFireSystem();
	cFire5 = new CFireSystem();

	// This will read in from file eventually
	float pos1[2][MAX_WAYPOINTS] = { {-8, -8, -8,  -8,  -8, -10, -40, -65, -88, -88, -88, -88, -78, -60, -40, -20,   0,  40,  80, 300, 340, 380, 428, 412, 412, 412, 412, 412, 412, 412, 412,  412,  412,  412,  412,  412,  412,  412,  412,  412,  412,  412,  412,  412,  420,   0,    -8,   -8,   -8,   -8,   -8,  -8,  -8, },
									 { 0, 40, 80, 120, 150, 157, 157, 162, 180, 190, 205, 220, 235, 242, 252, 252, 252, 252, 252, 252, 252, 252, 268, 220, 180, 140, 100,  60,  20, -20, -60, -100, -140, -180, -220, -260, -300, -340, -380, -420, -460, -500, -540, -580, -625, -300, -260, -220, -180, -140, -100, -60, -40 } };

	float pos2[2][MAX_WAYPOINTS] = { { 0,  0,  0,   0,   0, -10, -40, -65, -80, -80, -80, -80, -70, -60, -40, -20,   0,  40,  80, 300, 340, 380, 420, 420, 420, 420, 420, 420, 420, 420, 420,  420,  420,  420,  420,  420,  420,  420,  420,  420,  420,  420,  420,  420,  420,    0,    0,    0,    0,    0,    0,   0,   0, },
									 { 0, 40, 80, 120, 160, 165, 165, 170, 180, 190, 205, 220, 235, 250, 260, 260, 260, 260, 260, 260, 260, 260, 260, 220, 180, 140, 100,  60,  20, -20, -60, -100, -140, -180, -220, -260, -300, -340, -380, -420, -460, -500, -540, -580, -625, -300, -260, -220, -180, -140, -100, -60, -40 } };

	float pos3[2][MAX_WAYPOINTS] = { { 8,  8,  8,   8,   8, -10, -40, -65, -72, -72, -72, -72, -62, -60, -40, -20,   0,  40,  80, 300, 340, 380, 412, 428, 428, 428, 428, 428, 428, 428, 428,  428,  428,  428,  428,  428,  428,  428,  428,  428,  428,  428,  428,  428,  420,    0,    8,    8,    8,    8,    8,   8,   8, },
									 { 0, 40, 80, 120, 170, 172, 172, 178, 180, 190, 205, 220, 235, 258, 268, 268, 268, 268, 268, 268, 268, 268, 252, 220, 180, 140, 100,  60,  20, -20, -60, -100, -140, -180, -220, -260, -300, -340, -380, -420, -460, -500, -540, -580, -625, -300, -260, -220, -180, -140, -100, -60, -40 } };
	
	for (int i = 0; i < MAX_WAYPOINTS; i++)
	{
		waypoints[0][i] = stateMsh->CreateModel(pos1[0][i], 0, pos1[1][i]);
	}
	
	for (int i = 0; i < MAX_WAYPOINTS; i++)
	{
		waypoints[1][i] = stateMsh->CreateModel(pos2[0][i], 0, pos2[1][i]);
	}

	for (int i = 0; i < MAX_WAYPOINTS; i++)
	{
		waypoints[2][i] = stateMsh->CreateModel(pos3[0][i], 0, pos3[1][i]);
	}

	/////////////////
	//-- SOOUNDS --//
	SmashingSound = new CSound(2, 0.07f);
	ExplostionSound = new CSound(3, 1.0f);
	PickupSound = new CSound(4, 0.07f);
	CrowdSound = new CSound(5, 0.1f);

	//-- LOAD FONT --///
	CentGoth = myEngine->LoadFont("Century Gothic", 36.0f);
	CentGothMed = myEngine->LoadFont("Century Gothic", 64.0f);
	CentGothLarge = myEngine->LoadFont("Century Gothic", 220.0f);
}

////////////////////
//-- GAMEUPDATE --//
void GameUpdate()
{	
	floorMdl->RotateLocalY(0.3);

	if (cPlayer->GetPlayerHealth() == 0)
	{
		PLAYERSTATE = DEAD;
	}

	// Player Position
	interfaceText << cPlayer->GetPosition();
	CentGothLarge->Draw(interfaceText.str(), 60, 660, kWhite);
	interfaceText.str("");

	if (cPlayer->GetPosition() == 1)
	{ 
		interfaceText << "ST";
		CentGoth->Draw(interfaceText.str(), 130, 700, kWhite);
	}
	else if (cPlayer->GetPosition() == 2)
	{
		interfaceText << "ND";
		CentGoth->Draw(interfaceText.str(), 160, 700, kWhite);
	}
	else if (cPlayer->GetPosition() == 3)
	{
		interfaceText << "RD";
		CentGoth->Draw(interfaceText.str(), 160, 700, kWhite);
	}
	else 
	{
		interfaceText << "TH";
		CentGoth->Draw(interfaceText.str(), 160, 700, kWhite);
	}
	interfaceText.str("");

	// Health
	interfaceText << cPlayer->GetPlayerHealth();
	CentGoth->Draw(interfaceText.str(), 270, 740, kWhite);
	interfaceText.str("");
	// Shield 
	interfaceText << cPlayer->GetPlayerShield();
	CentGoth->Draw(interfaceText.str(), 270, 790, kWhite);
	interfaceText.str("");

	// Time
	interfaceText << "Time  " /* Put time here */;
	CentGothMed->Draw(interfaceText.str(), 910, 50, kWhite);
	interfaceText.str("");
	// Lap
	interfaceText << "Lap  " << cPlayer->GetLap() << "/" << MAXLAPS;
	CentGothMed->Draw(interfaceText.str(), 910, 110, kWhite);
	interfaceText.str("");

	//Player Speed
	interfaceText << abs((int)cPlayer->GetPlayerS());
	CentGothMed->Draw(interfaceText.str(), 1015, 801, kWhite);
	interfaceText.str("");


	float speedf = cPlayer->GetPlayerS();

	speed = (int)speedf;


	for (int i = 0; i < 200; i++)
	{
		if (i < speed)
		{ 
				speedSprites[i]->SetPosition(1185, 848 - (1 * i));
		}
		else
		{ 
			speedSprites[i]->SetPosition(-250.0f, -250.0f);
		}
	}


	//for (int i = 0; i < 4; i++)
	//{
	//	// ai number
	//	interfaceText << "AI: " << i+1;
	//	CentGoth->Draw(interfaceText.str(), 600, 360 + (i * 25), kWhite);
	//	interfaceText.str("");
	//	
	//	// current checkpoint
	//	interfaceText << "Checkpoint: " << cAI[i]->GetCheckpoint();
	//	CentGoth->Draw(interfaceText.str(), 680, 360 + (i * 25), kWhite);
	//	interfaceText.str("");

	//	// current lap
	//	interfaceText << "Lap: " << cAI[i]->GetLap();
	//	CentGoth->Draw(interfaceText.str(), 900, 360 + (i * 25), kWhite);
	//	interfaceText.str("");

	//	// current position
	//	interfaceText << "Position: " << cAI[i]->GetPosition();
	//	CentGoth->Draw(interfaceText.str(), 1000, 360 + (i * 25), kWhite);
	//	interfaceText.str("");
	//}

	//-- STATS INTERFACE --//
	// frametime
	//interfaceText << "FPS: " << 1 / frameTime;
	//ComicSans->Draw(interfaceText.str(), FontFpsX, FontFpsY, kWhite);
	//interfaceText.str("");
	
	// current checkpoint
	//interfaceText << "Checkpoint: " << cPlayer->GetCheckpoint();
	//CentGoth->Draw(interfaceText.str(), 900, 650, kWhite);
	//interfaceText.str("");

	////Player ammunition
	//interfaceText << "Ammunition: ";
	//ComicSans->Draw(interfaceText.str(), 40, 795, kWhite);
	//interfaceText.str("");

	//interfaceText << "X: " << cPlayer->GetX() << "           Z: " <<  cPlayer->GetZ();
	//ComicSans->Draw(interfaceText.str(), 50, 50, kWhite);
	//interfaceText.str("");

	//-- Player movement --//
	cPlayer->SinHoverMovement(frameTime);

	//PLAYERSTATE = ALIVE;
	
	if (PLAYERSTATE == STARTRACE)
	{
		if (startingCounter >= 2 && startingCounter < 4)
		{
			interfaceText << "3";
		}
		else if (startingCounter > 4 && startingCounter < 6)
		{
			interfaceText << "2";
		}
		else if (startingCounter > 6 && startingCounter < 8)
		{
			interfaceText << "1";
		}
		else if (startingCounter > 8 && startingCounter < 9)
		{
			FontStartRaceX = 290;
			interfaceText << "GO";
		}
		else if (startingCounter >= 9)
		{
			PLAYERSTATE = ALIVE;
			RACESTATE = GO;
		}

		RaceStartFont->Draw(interfaceText.str(), FontStartRaceX, FontStartRaceY, kWhite);
		interfaceText.str("");

		startingCounter += frameTime * 1.1;
	}
	DelayCounter += frameTime;

	if (PLAYERSTATE == ALIVE)
	{

		cPlayer->PlayerUpdate(frameTime);

		//- player movement direction dependent on what key is hit
		cPlayer->GetModel()->MoveLocalZ(frameTime* cPlayer->GetPlayerS());

		cPlayer->ForwardReverseMovement(frameTime);

		//- the player can always move left or right

		cPlayer->RightLeftMovement(frameTime);

		

		//- Check for collision
		cTrack->ObjectCollision(cPlayer, cAI, SmashingSound, ExplostionSound);
		cTrack->AICollision(cPlayer, cAI, SmashingSound);

		//Update exhaust particle's position 
		cFire->update(frameTime, cPlayer);

		cFire2->updateAi(frameTime, cAI[0], cPlayer->GetCamera());
		cFire3->updateAi(frameTime, cAI[1], cPlayer->GetCamera());
		cFire4->updateAi(frameTime, cAI[2], cPlayer->GetCamera());
		cFire5->updateAi(frameTime, cAI[3], cPlayer->GetCamera());

		//- Chec for item collision
		cTrack->ItemCollision(cPlayer, PickupSound);

		if (cPlayer->GetPlayerHealth() < 50)
		{
			smokeActivated = true;
		}

		//Plays crowd cheering if player position is inside that track area
		if (cPlayer->GetZ() > -220.0f && cPlayer->GetZ() < 180)
		{
			if (cPlayer->GetX() > 360.0f && cPlayer->GetX() < 480.0f)
			{
				if (crowdCheering == false)
				{
					CrowdSound->PlaySound();
					crowdCheering = true;
				}
				if (crowdCheering == true)
				{
					cheerTimer += (10.0f * frameTime);
					if (cheerTimer >= 35.0f)
					{
						cheerTimer = 0.0f;
						crowdCheering = false;
					}
				}
			}
		}

		// if the smoke should appear because the player has below 50 health
		if (smokeActivated)
		{
			// if there isnt an instance of smoke class create one and set it to true
			if (!createSmoke)
			{
				cSmoke = new CSmokeSystem();
				createSmoke = true;
			}
			cSmoke->update(frameTime, cPlayer);

			if (cPlayer->GetPlayerHealth() > 50)
			{
				smokeActivated = false;
				createSmoke = false;
				delete(cSmoke);
			}
		}

		if (cPlayer->GetPlayerShield() > 0)
		{
			shieldActivated = true;
		}

		// if the shield should appear
		if (shieldActivated)
		{
			// if there isnt an instance of smoke class create one and set it to true
			if (!createShield)
			{
				testMsh = myEngine->LoadMesh("shield.x");
				testMdl = testMsh->CreateModel(0,0,0);
				testMdl->Scale(0.4);
				createShield = true;
			}
			testMdl->AttachToParent(cPlayer->GetModel());


			if (sheildTimer > 2)
			{
				shieldActivated = false;
				createShield = false;
				myEngine->RemoveMesh(testMsh);
				sheildTimer = 0;
				cPlayer->RemoveShield();
			}
			else if (cPlayer->GetPlayerShield() == 0)
			{
				shieldActivated = false;
				createShield = false;
				myEngine->RemoveMesh(testMsh);
			}
			sheildTimer += 0.5 * frameTime;
		}		
	}

	//- update the players position
	cPlayer->UpdatePlayerPos();

	cTrack->RacePosition(cPlayer, cAI);

	for (int i = 0; i < 4; i++)
	{
		cAI[i]->UpdatePlayerPos();
	}

	if (PLAYERSTATE == DEAD)
	{

		if (deadCounter >= 1.5)
		{
			PLAYERSTATE = ALIVE;

			smokeActivated = false;
			createSmoke = false;
			delete(cSmoke);

			deadCounter = 0;
			cPlayer->ResetPlayerHealth();
			cTrack->ResetPlayerPosition(cPlayer);
			delete(sprite);
			wreckedText = false;
		}
		else
		{
			if (wreckedText == false)
			{
				sprite = myEngine->CreateSprite("WRECKED2.png");
				wreckedText = true;
			}
			
			deadCounter += frameTime * 0.8;
		}
	}

	if (cPlayer->GetLap() == MAXLAPS + 1)
	{
		PLAYERSTATE = ENDRACE;
	}

	//-- AI --//
	if (RACESTATE == GO)
	{
		for (int i = 0; i < 4; i++)
		{ 
			if (cAI[i]->GetPlayerHealth() > 0)
			{
				cAI[i]->SinHoverMovement(frameTime);
				cAI[i]->MoveToWaypoint(frameTime, waypoints);
			}
		}

		for (int i = 0; i < 4; i++)
		{
			if (cAI[i]->GetPlayerHealth() <= 0)
			{
				if (cAI[i]->deathTimer > 2)
				{
					cAI[i]->ResetPlayerHealth();
					cAI[i]->deathTimer = 0;
				}
				else
				{
					cAI[i]->deathTimer += frameTime * 0.8;
				}
			}
		}
	}

	cPlayer->UpdatePreviousPos();

	for (int i = 0; i < 4; i++)
	{ 
		cAI[i]->UpdatePreviousPos();
	}

	//-- Item --//
	cTrack->TrackUpdate(frameTime, cPlayer);

	cTrack->DisplayItemHeld();

	//- Chec for checkpoint collision
	cTrack->CheckPointCollision(cPlayer, cAI);
}

///////////////////////
//-- GAME SHUTDOWN --//
void GameShutdown()
{
	//Remove everything in the setup
	//- Tl Engine related
	myEngine->RemoveFont(CentGoth);
	//myEngine->RemoveMesh(playerMsh);
	myEngine->RemoveMesh(aiMsh);

	for (int i = 0; i < 4; i++)
	{
		delete(cAI[i]);
	}

	// delete the track
	delete(cTrack);
	delete(cPlayer);
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
				cEManager = new CEntityManager(cVMenu->GetSelected());
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
			//if (myEngine->KeyHit(Key_1))
			//{
			//	GAMESTATE = MAINMENU;
			//	setup = false;
				// shut down the game 
			//	GameShutdown();
			//}
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

////--INCLUDES--//
#include "Global.h"

//////////////////////////
////--GLOBAL VARIABLES--//
//I3DEngine* myEngine;
IFont* MyFont;
IFont* frontFont;
ISprite* sprite;
ICamera* myCamera;


// A buffer holds sound data, but the creation of a buffer on its own doesn't play a sound. It is the
// equivalent of a mesh in the TL-Engine
//ALuint buffer;

// A source is an actual sound in the world. A sound must be associated with a buffer to indicate
// which sound data to play. Sources are equivalent to models in the TL-Engine
//ALuint source;

// Each source has several properties, see the code for examples. Here we store position and velocity of
// the sound source above (x, y & z)
//ALfloat sourcePos[3] = { 0.0, 0.0, 0.0 };
//ALfloat sourceVel[3] = { 0.0, 0.0, 0.0 };

// There is always assumed to be a listener in an OpenAL application. We don't need a specific listener
// variable. However, listeners also have properties (examples in code). Here we store the position and
// velocity of the listener
//ALfloat listenerPos[3] = { 0.0, 0.0, 0.0 };
//ALfloat listenerVel[3] = { 0.0, 0.0, 0.0 };

// The listener may be at an angle (which may affect the perception of sound). Here we store the 
// orientation of the listener. The first three values are the facing direction (x, y, z) of the
// listener - called "at" in the documentation. The next three values are the upward direction
// of the listener, called "up". These vectors can be extracted from a world or view matrix
// NOTE: OpenAL (like OpenGL) uses a right-handed system for 3D coordinates. To convert from the
// left-handed system  we have used, we must negate all Z values (facing direction has -ve Z below)
//ALfloat listenerOri[6] = { 0.0, 0.0, -1.0,
//0.0, 1.0, 0.0 };

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
	// Add default folder for meshes and other media
	myEngine->AddMediaFolder("C:\\ProgramData\\TL-Engine\\Media");
	myEngine->AddMediaFolder(".\\Media");
	myEngine->AddMediaFolder(".\\Media\\Vechs");
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Initialise ALUT and hence OpenAL. If not using ALUT, we can initialise using core OpenAL functions.
	// However then we would need to consider what sound devices are available, with what features, and
	// select from those. ALUT just selects the default output device
	//alutInit(0, 0);


	//****************
	// Buffers

	// Create a sound buffer by loading a sound file. Using ALUT again to simplify this process. ALUT makes
	// its best attempt to convert different file formats into an OpenAL data format
	//buffer = alutCreateBufferFromFile("tada.wav");


	//****************
	// Sources

	// Create one sound source
	//alGenSources(1, &source);

	// Set the properties of the source. The full list of available properties can be found in the documentation
	// The last characters of each function name indicate the type of the second parameter (int, float, float vector etc.)
	//alSourcei(source, AL_BUFFER, buffer); // Attach a buffer to the source (identify which sound to play)
	//alSourcef(source, AL_PITCH, 1.0f);   // Pitch multiplier, doubling the pitch shifts the sound up 1 octave, halving
	// the pitch shifts it down 1 octave. Will also shorten/lengthen the sound
	//alSourcef(source, AL_GAIN, 1.0f);   // Effectively the volume of the sound - 0.0 = silent, 1.0 = as recorded. May
	// be able to increase volume over 1, but depends on sound
	//alSourcefv(source, AL_POSITION, sourcePos); // Position of sound relative to listener affects how it is reproduced through speakers
	//alSourcefv(source, AL_VELOCITY, sourceVel); // Velocity of sound relative to listener can cause Doppler effect
	//alSourcei(source, AL_LOOPING, AL_FALSE);  // Whether to loop the sound or just stop when it finishes


	//****************
	// Listener

	// Set the properties of the listener. These are all the available listener properties
	//alListenerfv(AL_POSITION, listenerPos); // Position, velocity and orientation of listener affect sound...
	//alListenerfv(AL_VELOCITY, listenerVel); // ...reproduction as noted above
	//alListenerfv(AL_ORIENTATION, listenerOri);
	//alListenerf(AL_GAIN, 1.0f);        // "Master" gain / volume. Controls overall loudness of all sounds

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

	std::string vechName = "GMC.x";
	playerMsh = myEngine->LoadMesh(vechName);

	///////////////////////////////////////////////////
	IMesh* ss = myEngine->LoadMesh("skybox.X");
	IModel* jj = ss->CreateModel();
	jj->Scale(2);

	IMesh* tt = myEngine->LoadMesh("floor.x");		// THIS WILL BE REMOVED CHECKING OUT SKYMAPS
	IModel* ff = tt->CreateModel(0.0f,1.0f,0.0f);
	ff->SetSkin("ground_07.jpg");
	/////////////////////////////////////////////////////

	//--LOAD FONT--///
	MyFont = myEngine->LoadFont("Comic Sans MS", 36.0f);
	
	//--CREATE SCENE--//
	cPlayer = new CPlayer(playerMsh); // interface to playerclass // constructor creates player vech // Camera creation and attachment

	//--CAMERA CREATION--//
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

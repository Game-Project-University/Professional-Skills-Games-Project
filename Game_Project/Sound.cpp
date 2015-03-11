//#include "Sound.h"
//
//CSound::CSound(int soundNumber)
//{
//	alutInit(0, 0);
//
//	//****************
//	// Buffers
//
//	// Create a sound buffer by loading a sound file. Using ALUT again to simplify this process. ALUT makes
//	// its best attempt to convert different file formats into an OpenAL data format
//	if (soundNumber == 1)
//	{
//		buffer = alutCreateBufferFromFile(".\\media\\tada.wav");
//	}
//
//	//****************
//	// Sources
//
//	// Create one sound source
//	alGenSources(1, &source);
//
//	// Set the properties of the source. The full list of available properties can be found in the documentation
//	// The last characters of each function name indicate the type of the second parameter (int, float, float vector etc.)
//	alSourcei(source, AL_BUFFER, buffer); // Attach a buffer to the source (identify which sound to play)
//	alSourcef(source, AL_PITCH, 1.0f);   // Pitch multiplier, doubling the pitch shifts the sound up 1 octave, halving
//	// the pitch shifts it down 1 octave. Will also shorten/lengthen the sound
//	alSourcef(source, AL_GAIN, 1.0f);   // Effectively the volume of the sound - 0.0 = silent, 1.0 = as recorded. May
//	// be able to increase volume over 1, but depends on sound
//	alSourcefv(source, AL_POSITION, sourcePos); // Position of sound relative to listener affects how it is reproduced through speakers
//	alSourcefv(source, AL_VELOCITY, sourceVel); // Velocity of sound relative to listener can cause Doppler effect
//	alSourcei(source, AL_LOOPING, AL_FALSE);  // Whether to loop the sound or just stop when it finishes
//
//
//	//****************
//	// Listener
//
//	// Set the properties of the listener. These are all the available listener properties
//	alListenerfv(AL_POSITION, listenerPos); // Position, velocity and orientation of listener affect sound...
//	alListenerfv(AL_VELOCITY, listenerVel); // ...reproduction as noted above
//	alListenerfv(AL_ORIENTATION, listenerOri);
//	alListenerf(AL_GAIN, 1.0f);        // "Master" gain / volume. Controls overall loudness of all sounds
//
//}
//
//CSound::~CSound()
//{
//}
//
////////////////////
////--PLAY SOUND--//
//void CSound::PlaySound()
//{
//	alSourcePlay(source);
//}
//
//////////////////////////////
////--SET SOUND PROPERTIES--//
//
////-- source --//
//void CSound::SetSourcePos(float x, float y, float z)
//{
//	sourcePos[0] = x;
//	sourcePos[1] = y;
//	sourcePos[2] = z;
//}
//
//void CSound::SetSourceVel(float x, float y, float z)
//{
//	sourceVel[0] = x;
//	sourceVel[1] = y;
//	sourceVel[2] = z;
//}
//
////-- listener --//
//void CSound::SetListenerPos(float x, float y, float z)
//{
//	listenerPos[0] = x;
//	listenerPos[1] = y;
//	listenerPos[2] = z;
//}
//
//void CSound::SetListenerVel(float x, float y, float z)
//{
//	listenerVel[0] = x;
//	listenerVel[1] = y;
//	listenerVel[2] = z;
//}
//
//void CSound::SetListenerOrientation(float forwardNx, float forwardNy, float forwardNz, float upNx, float upNy, float upNz)
//{
//	listenerOri[0] = forwardNx;
//	listenerOri[1] = forwardNy;
//	listenerOri[2] = forwardNz;
//
//	listenerOri[3] = upNx;
//	listenerOri[4] = upNy;
//	listenerOri[5] = upNz;
//}
//#ifndef SOUND_H
//#define SOUND_H
//
//#include "Global.h"
//
//class CSound
//{
//private: 
//	// A buffer holds sound data, but the creation of a buffer on its own doesn't play a sound. It is the
//	// equivalent of a mesh in the TL-Engine
//	ALuint buffer;
//
//	// A source is an actual sound in the world. A sound must be associated with a buffer to indicate
//	//which sound data to play. Sources are equivalent to models in the TL-Engine
//	ALuint source;
//
//	// Each source has several properties, see the code for examples. Here we store position and velocity of
//	// the sound source above (x, y & z)
//	ALfloat sourcePos[3];
//	ALfloat sourceVel[3];
//
//	// There is always assumed to be a listener in an OpenAL application. We don't need a specific listener
//	// variable. However, listeners also have properties (examples in code). Here we store the position and
//	// velocity of the listener
//	ALfloat listenerPos[3];
//	ALfloat listenerVel[3];
//
//	// The listener may be at an angle (which may affect the perception of sound). Here we store the 
//	// orientation of the listener. The first three values are the facing direction (x, y, z) of the
//	// listener - called "at" in the documentation. The next three values are the upward direction
//	// of the listener, called "up". These vectors can be extracted from a world or view matrix
//	// NOTE: OpenAL (like OpenGL) uses a right-handed system for 3D coordinates. To convert from the
//	// left-handed system  we have used, we must negate all Z values (facing direction has -ve Z below)
//	ALfloat listenerOri[6];
//public:
//	CSound(int soundNumber);
//	~CSound();
//
//	//-Play Sounds-//
//	void PlaySound();
//
//	//-Change sound settings
//	void SetSourcePos(float x, float y, float z);
//	void SetSourceVel(float x, float y, float z);
//
//	void SetListenerPos(float x, float y, float z);
//	void SetListenerVel(float x, float y, float z);
//	void SetListenerOrientation(float forwardNx, float forwardNy, float forwardNz, float upNx, float upNy, float upNz);
//};
//#endif
#pragma once

class iLvLEngine;
class iLvLInput;
class iLvLPhysicsEngine;
class iLvLSoundSystem;

class LvL 
{
public:
	static iLvLEngine* Engine;
	static iLvLInput* Input;
	static iLvLPhysicsEngine* Physics;
	static iLvLSoundSystem* SoundSystem;
};
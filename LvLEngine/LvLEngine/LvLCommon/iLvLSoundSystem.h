#pragma once
#include"LvLBaseDef.h"

class iLvLEngine;

class iLvLSoundSystem 
{
	LvL_ABSTRACT_REFCOUNT();
public:
	virtual void Initialize(int audio_rate,uint16_t  audio_format, int audio_channel, int audio_buffer) = 0;
	virtual void* GetHandle() = 0;
	virtual void ShutDown() = 0;
	virtual void Play() = 0;
	virtual void LoadBGM(const char* path) = 0;
	
protected:
	virtual ~iLvLSoundSystem() {}
	
};

extern "C"
{
	typedef iLvLSoundSystem* (CreateSoundSystemFunc)(iLvLEngine* engine);
	LvL_API iLvLSoundSystem* CreateSoundSystem(iLvLEngine* engine);
}
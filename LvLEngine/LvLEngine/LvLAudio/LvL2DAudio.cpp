#include "pch.h"
#include"iLvLEngine.h"
#include "iLvLSoundSystem.h"
#include "iLvLSound.h"
#include "LvL2DAudio.h"

LvL_IMPLEMENT_REFCOUNTED(LvL2DAudio);

void LvL2DAudio::Initialize(int audio_rate, Uint16 audio_format, int audio_channel, int audio_buffer)
{
	
	audio_rate = 22050;
	audio_format = AUDIO_S16SYS;
	audio_channel = 2;
	audio_buffer = 4096;

	if (Mix_OpenAudio(audio_rate, audio_format, audio_channel, audio_buffer) != 0) 
	{
		exit(-1);
	}
}

void* LvL2DAudio::GetHandle()
{
	return _BGM;
}

void LvL2DAudio::ShutDown()
{
	Mix_Quit();
	_BGM = NULL;
}

void LvL2DAudio::Play()
{
	Mix_PlayMusic(_BGM, -1);
}

LvL2DAudio::~LvL2DAudio()
{
	ShutDown();
}

void LvL2DAudio::LoadBGM(const char* path)
{
	_BGM = Mix_LoadMUS(path);
}
iLvLSoundSystem* CreateSoundSystem(iLvLEngine* engine) 
{
	LvL::Engine = engine;
	iLvLSoundSystem* Soundsys = new LvL2DAudio();
	return Soundsys;
}

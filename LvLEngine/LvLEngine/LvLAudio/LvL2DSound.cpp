#include "pch.h"
#include"iLvLEngine.h"
#include "iLvLSoundSystem.h"
#include "LvL2DSound.h"
#include"iLvLSound.h"

LvL_IMPLEMENT_REFCOUNTED(LvL2DSound);
using namespace std;

LvL2DSound::LvL2DSound(Mix_Music* music, const char* name)
{
	_BGM = music;
	vector<string> result;
	stringstream s_stream(name); //create string stream from the
	while (s_stream.good())
	{
		string substr;
		//split the path with '/'
		getline(s_stream, substr, '\\');
		result.push_back(substr);
	}

	//get the last split and set as name
	_pName = result[result.size() - 1];
}

const char* LvL2DSound::GetName()
{
	return _pName.c_str();
}

eLvLResourceType LvL2DSound::GetType()
{
	return eLvLResourceType::rtSound;
}

void* LvL2DSound::GetHandle()
{
	return _BGM;
}

LvL2DSound::~LvL2DSound()
{
	Mix_FreeMusic(_BGM);
}

void LvL2DSound::Play()
{
	Mix_PlayMusic(_BGM, -1);
}

bool _loaded = false;

iLvLSound* LoadSound(const char* path) 
{
	//TODO
	iLvLSoundSystem* ss = LvL::Engine->GetSoundSystem();
	Mix_Music* bgm = Mix_LoadMUS(path);
	iLvLSound* audio =new LvL2DSound(bgm,path);
	return audio;
}

#pragma once
#include"LvLBaseDef.h"

class iLvLSoundSystem;

class LvL2DAudio :	public iLvLSoundSystem
{
	LvL_DECLARE_REFCOUNTTED();
public:
	// Inherited via iLvLSoundSystem
	virtual void Initialize(int audio_rate, Uint16 audio_format, int audio_channel, int audio_buffer) override;
	virtual void* GetHandle() override;
	virtual void ShutDown() override;
	virtual void LoadBGM(const char* path) override;
	virtual void Play() override;
private:
	virtual ~LvL2DAudio();
	Mix_Music* _BGM;
protected:

};



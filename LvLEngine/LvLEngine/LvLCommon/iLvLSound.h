#pragma once
#include "iLvLResource.h"

enum eLvLSoundType 
{
	ssUnassigned,
	ssBGM,
	ssSFX
};
class iLvLSound : public iLvLResource
{
public:
	virtual void* GetHandle() = 0;
	virtual void Play() = 0;
private:
protected:
	~iLvLSound() {}
};

extern "C"
{
	typedef iLvLSound* (LoadSoundFunc)(const char* path);
	LvL_API iLvLSound* LoadSound(const char* path);
}

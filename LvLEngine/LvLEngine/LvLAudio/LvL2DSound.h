#pragma once
#include"iLvLSound.h"


class LvL2DSound :	public iLvLSound
{
	LvL_DECLARE_REFCOUNTTED();
public:
	// Inherited via iLvLSound
	LvL2DSound(Mix_Music* music, const char* name);
	virtual const char* GetName() override;
	virtual eLvLResourceType GetType() override;
	virtual void* GetHandle() override;
	virtual void Play() override;
private:
	virtual ~LvL2DSound();
	std::string _pName;
	Mix_Music* _BGM = NULL;
};


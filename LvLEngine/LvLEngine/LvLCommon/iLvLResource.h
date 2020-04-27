#pragma once
#include "LvLBaseDef.h"

enum eLvLResourceType 
{
	rtTexture,
	rtSound,
	//etc
};

class iLvLResource 
{
	LvL_ABSTRACT_REFCOUNT();

public:
	virtual const char* GetName() = 0;
	virtual eLvLResourceType GetType() = 0;
protected:
	virtual ~iLvLResource() {}
};
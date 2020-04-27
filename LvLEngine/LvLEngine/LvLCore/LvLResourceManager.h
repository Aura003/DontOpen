#pragma once
#include "LvLBaseDef.h"

class iLvLResource;

typedef std::map<std::string, iLvLResource*> LvL_RESOURCEMAP;
typedef LvL_RESOURCEMAP::iterator LvL_RESOURCEMAP_IT;

class LvLResourceManager
{
public:
	void Add(iLvLResource* res);
	void Release(const char* resID);
	iLvLResource* Get(const char* resID);
	int GetCount();

private:
	LvL_RESOURCEMAP _resourceMap;
};


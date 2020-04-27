#pragma once
#include "LvLBaseDef.h"

class iLvLEngine;

class iLvLGame
{
	LvL_ABSTRACT_REFCOUNT();
public:
	virtual void LoadGame(iLvLEngine* engine) = 0;
	virtual void EndGame() = 0;

};


extern "C"
{
	typedef iLvLGame* (CreateGameFunc)(iLvLEngine* engine);
	LvL_API iLvLGame* CreateGame(iLvLEngine* engine);
}
#pragma once
#include "LvLBaseDef.h"
#include"iLvLGame.h"


class Game01 : 	public iLvLGame
{
	LvL_DECLARE_REFCOUNTTED();

public:
	virtual void LoadGame(iLvLEngine* engine)override;
	virtual void EndGame() override;
	static Game01* Game;

	int Score = 0;
};


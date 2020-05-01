#pragma once
#include "iLvLComponent.h"
#include "iLvLInput.h"

enum eGame01ComponentType
{
	Bouncy = (int)eLvLComponentType::ctHIGHEST,
	ScoreBoard
};

enum class eGame01Tag 
{
	tagUnassigned = 0,
	tagPlayer,
	tagPlatform,
	tagEnemy
};
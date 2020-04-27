#include "stdafx.h"

#include"iLvLGame.h"
#include"iLvLTexture.h"
#include"iLvLRenderer.h"
#include "iLvLPhysicsEngine.h"
#include "LvLEngineModules.h"

const char* LvLEngineModules::GameDLL = NULL;
const char* LvLEngineModules::RendererDLL = NULL;
const char* LvLEngineModules::PhysicsDLL = NULL;

HMODULE GameLib = NULL;
HMODULE RendererLib = NULL;
HMODULE PhysicsLib = NULL;

CreateGameFunc* CREATEGAMEFUNC = NULL;
LoadTextureFunc* LOADTEXTUREFUNC = NULL;
CreateRendererFunc* CREATERENDERERFUNC = NULL;
CreatePhysicsEngineFunc* CREATEPHYSICSENGINEFUNC = NULL;

void LvLEngineModules::LoadGameLib()
{
	if (GameLib == NULL)
	{
		GameLib = LoadLibraryA(LvLEngineModules::GameDLL);//Game01.dll
	}
}

void LvLEngineModules::FreeGameLib()
{
	if (GameLib)
	{
		FreeLibrary(GameLib);
		GameLib = NULL;
	}
}
void LvLEngineModules::LoadRendererLib()
{
	if (RendererLib == NULL)
	{
		RendererLib = LoadLibraryA(LvLEngineModules::RendererDLL);
	}
}
void LvLEngineModules::FreeRendererLib()
{
	if (RendererLib)
	{
		FreeLibrary(RendererLib);
		RendererLib = NULL;
	}
}
void LvLEngineModules::LoadPhysisLib()
{
	if (PhysicsLib == NULL)
	{
		PhysicsLib = LoadLibraryA(LvLEngineModules::PhysicsDLL);
	}
}
void LvLEngineModules::FreePhysicsLib()
{
	if (PhysicsLib)
	{
		FreeLibrary(PhysicsLib);
		PhysicsLib = NULL;
	}
}
iLvLGame* LvL_CreateGame(iLvLEngine* engine) 
{
	if (CREATEGAMEFUNC == NULL)
	{
		CREATEGAMEFUNC = (CreateGameFunc*)GetProcAddress(GameLib, "CreateGame");
	}

	return CREATEGAMEFUNC(engine);

}
iLvLTexture* LvL_LoadTexture(const char* path) 
{
	if (LOADTEXTUREFUNC == NULL)
	{
		LOADTEXTUREFUNC = (LoadTextureFunc*)GetProcAddress(RendererLib, "LoadTexture");
	}
	return LOADTEXTUREFUNC(path);
}

iLvLRenderer* LvL_CreateRenderer(iLvLEngine* engine)
{
	if (CREATERENDERERFUNC == NULL)
	{
		CREATERENDERERFUNC = (CreateRendererFunc*)GetProcAddress(RendererLib, "CreateRenderer");
	}

	return CREATERENDERERFUNC(engine);
}

iLvLPhysicsEngine* LvL_CreatePhysicsEngine(iLvLEngine* engine)
{
	if (CREATEPHYSICSENGINEFUNC == NULL)
	{
		CREATEPHYSICSENGINEFUNC = (CreatePhysicsEngineFunc*)GetProcAddress(PhysicsLib, "CreatePhysicsEngine");
	}
	return CREATEPHYSICSENGINEFUNC(engine);
}

#include "stdafx.h"

#include "iLvLGame.h"
#include "iLvLTexture.h"
#include "iLvLRenderer.h"
#include "iLvLPhysicsEngine.h"
#include "Modules.h"

const char* EngineAlphaModule::GameDLL = NULL;
const char* EngineAlphaModule::RendererDLL = NULL;
const char* EngineAlphaModule::PhysicsDLL = NULL;

HMODULE GameLib = NULL;
HMODULE RendererLib = NULL;
HMODULE PhysicsLib = NULL;

CreateGameFunc* CREATEGAMEFUNC = NULL;
LoadTextureFunc* LOADTEXTUREFUNC = NULL;
CreateRendererFunc* CREATERENDERERFUNC = NULL;
CreatePhysicsEngineFunc* CREATEPHYSICSENGINEFUNC = NULL;

void EngineAlphaModule::LoadGameLib()
{
	if (GameLib == NULL)
	{
		GameLib = LoadLibraryA(EngineAlphaModule::GameDLL);//Game01.dll
	}
}

void EngineAlphaModule::FreeGameLib()
{
	if (GameLib) 
	{
		FreeLibrary(GameLib);
		GameLib = NULL;
	}
}
void EngineAlphaModule::LoadRendererLib()
{
	if (RendererLib == NULL) 
	{
		RendererLib = LoadLibraryA(EngineAlphaModule::RendererDLL);//Game01.dll
	}
}
void EngineAlphaModule::FreeRendererLib()
{
	if (RendererLib)
	{
		FreeLibrary(RendererLib);
		RendererLib = NULL;
	}
}
void EngineAlphaModule::LoadPhysisLib()
{
	if (PhysicsLib == NULL) 
	{
		PhysicsLib = LoadLibraryA(EngineAlphaModule::PhysicsDLL);
	}
}
void EngineAlphaModule::FreePhysicsLib()
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


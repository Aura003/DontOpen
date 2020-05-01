#include "stdafx.h"

#include "iLvLGame.h"
#include "iLvLTexture.h"
#include "iLvLRenderer.h"
#include "iLvLPhysicsEngine.h"
#include "iLvLSoundSystem.h"
#include "iLvLSound.h"
#include "Modules.h"

const char* EngineAlphaModule::GameDLL = NULL;
const char* EngineAlphaModule::RendererDLL = NULL;
const char* EngineAlphaModule::PhysicsDLL = NULL;
const char* EngineAlphaModule::SoundDLL = NULL;

HMODULE GameLib = NULL;
HMODULE RendererLib = NULL;
HMODULE PhysicsLib = NULL;
HMODULE SoundLib = NULL;

CreateGameFunc* CREATEGAMEFUNC = NULL;
LoadTextureFunc* LOADTEXTUREFUNC = NULL;
LoadSoundFunc* LOADSOUNDFUNC = NULL;
CreateRendererFunc* CREATERENDERERFUNC = NULL;
CreatePhysicsEngineFunc* CREATEPHYSICSENGINEFUNC = NULL;
CreateSoundSystemFunc* CREATESOUNDSYSTEMFUNC = NULL;

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
void EngineAlphaModule::LoadSoundLib()
{
	if (SoundLib == NULL)
	{
		SoundLib = LoadLibraryA(EngineAlphaModule::SoundDLL);
	}
}
void EngineAlphaModule::FreeSoundLib()
{
	if (SoundLib)
	{
		FreeLibrary(SoundLib);
		SoundLib = NULL;
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

iLvLSoundSystem* LvL_CreateSoundSystem(iLvLEngine* engine)
{
	if (CREATESOUNDSYSTEMFUNC == NULL)
	{
		CREATESOUNDSYSTEMFUNC = (CreateSoundSystemFunc*)GetProcAddress(SoundLib, "CreateSoundSystem");
	}

	return CREATESOUNDSYSTEMFUNC(engine);
}

iLvLSound* LvL_LoadSound(const char* path)
{
	if (LOADSOUNDFUNC == NULL)
	{
		LOADSOUNDFUNC = (LoadSoundFunc*)GetProcAddress(SoundLib, "LoadSound");
	}
	return LOADSOUNDFUNC(path);
}


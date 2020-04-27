#pragma once

class iLvLTexture;
class iLvLRenderer;
class iLvLPhysicsEngine;

class EngineAlphaModule 
{
public:
	static const char* GameDLL;
	static void LoadGameLib();
	static void FreeGameLib();
	
	static const char* RendererDLL;
	static void LoadRendererLib();
	static void FreeRendererLib();

	static const char* PhysicsDLL;
	static void LoadPhysisLib();
	static void FreePhysicsLib();
};

iLvLGame* LvL_CreateGame(iLvLEngine* engine);
iLvLTexture* LvL_LoadTexture(const char* path);
iLvLRenderer* LvL_CreateRenderer(iLvLEngine* engine);
iLvLPhysicsEngine* LvL_CreatePhysicsEngine(iLvLEngine* engine);
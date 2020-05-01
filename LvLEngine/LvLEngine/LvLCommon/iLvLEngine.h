#pragma once
#include "LvLBaseDef.h"

class iLvLRenderer;
class iLvLTexture;
class LvLResourceManager;
struct LvLWindowParams;
class LvLEntitySystem;
class iLvLInput;
class iLvLPhysicsEngine;
class iLvLSoundSystem;
class iLvLSound;

class iLvLEngine 
{

public:
	/**
	*  Initializes the engine. First to execute before start of engine
	* @param windowParams window parameters where the main app will run
	*/
	virtual void Initialize(const LvLWindowParams& windowParams) =0; //=0 makes it abstract 
	/**
	*  Shuts Down the Engine.  Calls FreeGameLib(); and FreeRenderLib(); SDL_DestroyWindow(); and SDL_QUIT();
	*/
	virtual void ShutDown() = 0;
	/**
	*  Loads the Renderer Library, Physics Library and WindowsParams
	*/
	virtual void StartEngine() = 0;
	/**
	*  Runs Update based on SDL_PollEvent, Computes delta Time based on SDL_GetTicks();
	*/
	virtual bool Update() = 0;
	virtual iLvLRenderer* GetRenderer() = 0;
	virtual iLvLSoundSystem* GetSoundSystem() = 0;
	virtual void* GetWindowHandle() = 0;
	virtual LvLResourceManager* GetResourceManager() = 0;
	virtual LvLEntitySystem* GetEntitySystem() = 0;
	virtual iLvLPhysicsEngine* GetPhysicsEngine() = 0;
	virtual iLvLInput* GetInput() = 0;

	virtual void BeginDraw() = 0;
	virtual void Draw() = 0;
	virtual void Present() = 0;

	//Resource Management
	virtual iLvLTexture* LoadTexture(const char* path) = 0;
	virtual iLvLTexture* GetTexture(const char* id) = 0;
	virtual void LoadResourceFolder(const char* folder)=0;
	virtual iLvLSound* LoadSound(const char* path) = 0;
	virtual iLvLSound* GetSound(const char* id) = 0;

	//game
	virtual void LoadGame(const char* game) = 0;
	virtual void UnloadGame() = 0;

private:
protected:
};

struct LvLWindowParams 
{
public:
	int PositionX = -1;
	int PositionY = -1;
	int Width = 640;
	int Height = 480;

	unsigned char Red;
	unsigned char Green;
	unsigned char Blue;
	unsigned char Alpha;
};

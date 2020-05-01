#pragma once
//#include "iLvLGame.h"
#include "LvLResourceManager.h"
#include "LvLEngineInput.h"


struct SDL_Window;
struct SDL_Surface;
class iLvLGame;
class iLvLRenderer;
class LvLEntitySystem;
class iLvLPhysicsEngine;
class iLvLSoundSystem;

class LvLEngineAlpha : public iLvLEngine
{
public:
	virtual void Initialize(const LvLWindowParams& windowParams) override;
	virtual void ShutDown() override;
	virtual void StartEngine() override;
	virtual bool Update() override;

	virtual void BeginDraw() override;
	virtual void Draw() override;
	virtual void Present() override;

	virtual iLvLRenderer* GetRenderer() override;
	virtual iLvLSoundSystem* GetSoundSystem() override;
	virtual void* GetWindowHandle() override;
	virtual LvLResourceManager* GetResourceManager() override;

	virtual LvLEntitySystem* GetEntitySystem() override;
	virtual iLvLTexture* LoadTexture(const char* path) override;
	virtual iLvLTexture* GetTexture(const char* id) override;
	virtual iLvLSound* LoadSound(const char* path) override;
	virtual iLvLSound* GetSound(const char* id) override;
	virtual void LoadResourceFolder(const char* folder) override;
	virtual iLvLPhysicsEngine* GetPhysicsEngine()override;

	virtual void LoadGame(const char* game) override;
	virtual void UnloadGame() override;

	virtual iLvLInput* GetInput() override;

private:
	SDL_Window* _window = NULL;
	SDL_Surface* _mainSurface = NULL;
	UINT32 _clearColor = NULL;
	bool _running = false;
	iLvLGame* _pGame;
	iLvLRenderer* _pRenderer = NULL;
	iLvLSoundSystem* _pSoundSystem = NULL;


	LvLResourceManager _resourceManager;
	LvLEntitySystem* _pEntitySystem;
	iLvLPhysicsEngine* _pPhysicsEngine;
	LvLEngineInput _input;










};


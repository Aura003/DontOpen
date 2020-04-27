#pragma once
//#include "iLvLGame.h"
#include "LvLResourceManager.h"
#include "EngineAlphaInput.h"

struct SDL_Window;
struct SDL_Surface;
class iLvLGame;
class iLvLRenderer;
class LvLEntitySystem;
class iLvLPhysicsEngine;
//class LvLResourceManager;

class EngineAlpha : public iLvLEngine
{
public:
	// Inherited via iLvLEngine
	virtual void Initialize(const LvLWindowParams& windowParams) override;
	virtual void ShutDown() override;
	virtual void StartEngine() override;
	virtual bool Update() override;

	virtual void BeginDraw() override;
	virtual void Draw() override;
	virtual void Present() override;

	virtual iLvLRenderer* GetRenderer() override;
	virtual void* GetWindowHandle() override;
	virtual LvLResourceManager* GetResourceManager() override;
	// Inherited via iLvLEngine
	virtual LvLEntitySystem* GetEntitySystem() override;
	virtual iLvLTexture* LoadTexture(const char* path) override;
	virtual iLvLTexture* GetTexture(const char* id) override;
	virtual void LoadResourceFolder(const char* folder) override;
	virtual iLvLPhysicsEngine* GetPhysicsEngine()override;

	// Inherited via iLvLEngine
	virtual void LoadGame(const char* game) override;
	virtual void UnloadGame() override;

	// Inherited via iLvLEngine
	virtual iLvLInput* GetInput() override;

private:
	SDL_Window* _window = NULL;
	SDL_Surface* _mainSurface = NULL;
	UINT32 _clearColor = NULL;
	bool _running = false;
	iLvLGame* _pGame;
	iLvLRenderer* _pRenderer = NULL;

	LvLResourceManager _resourceManager;
	LvLEntitySystem* _pEntitySystem;
	iLvLPhysicsEngine* _pPhysicsEngine;
	EngineAlphaInput _input;



};


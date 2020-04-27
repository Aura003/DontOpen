#include"stdafx.h"
#include"iLvLEngine.h"
#include "iLvLGame.h"
#include "iLvLTexture.h"
#include "iLvLRenderer.h"
#include "LvLEntitySystem.h"
#include "LvLResourceManager.h"
#include "iLvLPhysicsEngine.h"
#include "LvLEngineAlpha.h"
#include "LvLEngineModules.h"


using namespace std;

void LvLEngineAlpha::Initialize(const LvLWindowParams& windowParams)
{
	int posX = windowParams.PositionX == -1 ? SDL_WINDOWPOS_CENTERED : windowParams.PositionX;
	int posY = windowParams.PositionY == -1 ? SDL_WINDOWPOS_CENTERED : windowParams.PositionY;

	_window = SDL_CreateWindow("My Engine", posX, posY, windowParams.Width, windowParams.Height, SDL_WINDOW_SHOWN);

	_mainSurface = SDL_GetWindowSurface(_window);
	
	_clearColor = SDL_MapRGB(_mainSurface->format, windowParams.Red, windowParams.Green, windowParams.Blue);
}


void LvLEngineAlpha::StartEngine()
{
	_running = true;
	LvLEngineModules::LoadRendererLib();
	_pEntitySystem = new LvLEntitySystem();

	LvLWindowParams fake; //TODO
	_pRenderer = LvL_CreateRenderer(this);
	_pRenderer->Initialize(fake);

	LvLEngineModules::LoadPhysisLib();
	_pPhysicsEngine = LvL_CreatePhysicsEngine(this);
	_pPhysicsEngine->Initialize(XMFLOAT3(0, -9.8f, 0), 30,32);
}

double _deltaTime = 0;
UINT64 _start = 0;
bool LvLEngineAlpha::Update() 
{
	
	_input.Refresh();

	SDL_Event event;
	
	while (SDL_PollEvent(&event) != 0)
	{
		switch (event.type)
		{
		case SDL_QUIT:
			_running = false;
			break;
		default:
			_input.ProcessEvent(&event);
			break;
		}
	}
	_pPhysicsEngine->Update(_deltaTime);
	_pEntitySystem->Update((float)_deltaTime);

	UINT64 end = SDL_GetTicks();
	_deltaTime = (double)((end - _start) / 1000.0f);
	_start = end;

	return _running;
}
void LvLEngineAlpha::Draw() 
{
	_pEntitySystem->PrepareDOP(_pRenderer);
	_pRenderer->Draw();

}
iLvLRenderer* LvLEngineAlpha::GetRenderer()
{
	return _pRenderer;
}
void* LvLEngineAlpha::GetWindowHandle()
{
	return _window;
}
LvLResourceManager* LvLEngineAlpha::GetResourceManager()
{
	return &_resourceManager;
}
void LvLEngineAlpha::BeginDraw()
{
	_pRenderer->BeginDraw();
}
void LvLEngineAlpha::Present()
{
	_pRenderer->Present();
}
iLvLTexture* LvLEngineAlpha::LoadTexture(const char* path)
{
	//Load texture via module call
	iLvLTexture* texture = LvL_LoadTexture(path);
	if (texture)
	{
		//store the texture if it is successfull
		_resourceManager.Add(texture);
	}
	//store the texture if it is successfull
	return texture;

}
iLvLTexture* LvLEngineAlpha::GetTexture(const char* id)
{
	return (iLvLTexture*)_resourceManager.Get(id);
}
LvLEntitySystem* LvLEngineAlpha::GetEntitySystem()
{
	return _pEntitySystem;
}
iLvLInput* LvLEngineAlpha::GetInput()
{
	return &_input;
	
}
void LvLEngineAlpha::LoadResourceFolder(const char* folder)
{
	//all png
	string path = folder;
	string ext = ".png";
	for (const auto& res : filesystem::directory_iterator(path))
	{
		auto& relpath = res.path();
		string extractedExt = relpath.extension().string();
		if (ext == extractedExt)
		{
			string tex = relpath.string();
			//hurray this is a texture
			LoadTexture(tex.c_str());
		}
	}
	//all wav
}
iLvLPhysicsEngine* LvLEngineAlpha::GetPhysicsEngine()
{
	return _pPhysicsEngine;
}
void LvLEngineAlpha::LoadGame(const char* game)
{
	LvLEngineModules::GameDLL = game;

	LvLEngineModules::LoadGameLib();
	_pGame = LvL_CreateGame(this);
	_pGame->LoadGame(this);
}
void LvLEngineAlpha::UnloadGame()
{
	_pGame->EndGame();
	LvL_SAFERELEASE(_pGame);
	LvLEngineModules::FreeGameLib();
}
void LvLEngineAlpha::ShutDown() 
{
	LvL_SAFERELEASE(_pGame);
	LvL_SAFERELEASE(_pRenderer);

	LvLEngineModules::FreeGameLib();
	LvLEngineModules::FreeRendererLib();
	SDL_DestroyWindow(_window);
	SDL_Quit();
}
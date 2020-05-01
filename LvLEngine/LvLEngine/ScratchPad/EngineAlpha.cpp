#include"stdafx.h"
#include "iLvLEngine.h"
#include "iLvLGame.h"
#include"iLvLTexture.h"
#include "iLvLSound.h"
#include "iLvLRenderer.h"
#include"LvLEntitySystem.h"
#include"LvLResourceManager.h"
#include "iLvLPhysicsEngine.h"
#include "iLvLSoundSystem.h"
#include "EngineAlpha.h"
#include"Modules.h"

using namespace std;

void EngineAlpha::Initialize(const LvLWindowParams& windowParams)
{
	int posX = windowParams.PositionX == -1 ? SDL_WINDOWPOS_CENTERED : windowParams.PositionX;
	int posY = windowParams.PositionY == -1 ? SDL_WINDOWPOS_CENTERED : windowParams.PositionY;

	_window = SDL_CreateWindow("My Engine", posX, posY, windowParams.Width, windowParams.Height, SDL_WINDOW_SHOWN);

	_mainSurface = SDL_GetWindowSurface(_window);

	_clearColor = SDL_MapRGB(_mainSurface->format, windowParams.Red, windowParams.Green, windowParams.Blue);

}


void EngineAlpha::StartEngine()
{
	_running = true;
	EngineAlphaModule::LoadRendererLib();
	_pEntitySystem = new LvLEntitySystem(this);
	
	LvLWindowParams fake; //TODO
	_pRenderer = LvL_CreateRenderer(this);
	_pRenderer->Initialize(fake);

	EngineAlphaModule::LoadPhysisLib();
	_pPhysicsEngine = LvL_CreatePhysicsEngine(this);
	_pPhysicsEngine->Initialize(XMFLOAT3(0, -9.8f, 0), 30, 32);

	EngineAlphaModule::LoadSoundLib();
	_pSoundSystem = LvL_CreateSoundSystem(this);
	_pSoundSystem->Initialize(22050, AUDIO_S16SYS, 2, 4096);
}
	
double _deltaTime = 0;
UINT64 _start = 0;

bool EngineAlpha::Update()
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

void EngineAlpha::Draw()
{
	//TODO draw call
	_pEntitySystem->PrepareDOP(_pRenderer);
	_pRenderer->Draw();
}

iLvLRenderer* EngineAlpha::GetRenderer()
{
	return _pRenderer;
}

void* EngineAlpha::GetWindowHandle()
{
	return _window;
}

LvLResourceManager* EngineAlpha::GetResourceManager()
{
	return &_resourceManager;
}

iLvLTexture* EngineAlpha::LoadTexture(const char* path)
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

iLvLTexture* EngineAlpha::GetTexture(const char* id)
{
	return (iLvLTexture*)_resourceManager.Get(id);
}

void EngineAlpha::LoadGame(const char* game)
{
	EngineAlphaModule::GameDLL = game;
	
	EngineAlphaModule::LoadGameLib();
	_pGame = LvL_CreateGame(this);
	_pGame->LoadGame(this);
}

void EngineAlpha::UnloadGame()
{
	_pGame->EndGame();
	LvL_SAFERELEASE(_pGame);
	EngineAlphaModule::FreeGameLib();
}

iLvLInput* EngineAlpha::GetInput()
{
	return &_input;
}

iLvLSoundSystem* EngineAlpha::GetSoundSystem()
{
	return _pSoundSystem;
}

iLvLSound* EngineAlpha::LoadSound(const char* path)
{
	iLvLSound* audio = LvL_LoadSound(path);
	if (audio) 
	{
		_resourceManager.Add(audio);
	}
	return audio;
}

iLvLSound* EngineAlpha::GetSound(const char* id)
{
	return (iLvLSound*)_resourceManager.Get(id);
}

void EngineAlpha::LoadResourceFolder(const char* folder)
{
	//all png
	string path = folder;
	string ext = ".png";
	string soundext = ".mp3|.wav|.ogg";
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
		else if (soundext.find(extractedExt) != std::string::npos) 
		{
			string aud = relpath.string();
			//hurray this is an audio
			LoadTexture(aud.c_str());
		}
	}
	
	
}

iLvLPhysicsEngine* EngineAlpha::GetPhysicsEngine()
{
	return _pPhysicsEngine;
}

LvLEntitySystem* EngineAlpha::GetEntitySystem()
{
	return _pEntitySystem;
}

void EngineAlpha::BeginDraw()
{
	_pRenderer->BeginDraw();
}

void EngineAlpha::Present()
{
	_pRenderer->Present();
}

void EngineAlpha::ShutDown()
{
	//delete _pGame;
	LvL_SAFERELEASE(_pGame);
	//TODO release entity system
	LvL_SAFERELEASE(_pRenderer);

	EngineAlphaModule::FreeGameLib();
	EngineAlphaModule::FreeRendererLib();
	SDL_DestroyWindow(_window);
	SDL_Quit();
}
#include"stdafx.h"
#include"iLvLEngine.h"
#include "LvLEngineAlpha.h"

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
}
bool LvLEngineAlpha::Update() 
{
	SDL_Event event;
	while (SDL_PollEvent(&event) != 0)
	 {
		switch (event.type)
		{
		case SDL_QUIT:
			_running = false;
			break;
		}
	 }
	return false;
}
void LvLEngineAlpha::Draw() 
{

	SDL_FillRect(_mainSurface, NULL, _clearColor);
	SDL_UpdateWindowSurface(_window);//TODO
}
void LvLEngineAlpha::ShutDown() 
{
	SDL_DestroyWindow(_window);
	SDL_Quit();
}
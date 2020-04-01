#pragma once
struct SDL_Window;
struct SDL_Surface;

class LvLEngineAlpha : public iLvLEngine
{
public:
	virtual void Initialize(const LvLWindowParams& windowParams) override;
	virtual void ShutDown() override;
	virtual void StartEngine() override;
	virtual bool Update() override;
	virtual void Draw() override;

private:
	SDL_Window* _window = NULL;
	SDL_Surface* _mainSurface = NULL;
	UINT32 _clearColor = NULL;
	bool _running = false;
};


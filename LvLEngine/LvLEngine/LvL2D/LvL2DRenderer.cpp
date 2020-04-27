#include "pch.h"
#include "iLvLEngine.h"
#include "iLvLRenderer.h"
#include"iLvLTexture.h"
#include "LvL2DRenderer.h"

LvL_IMPLEMENT_REFCOUNTED(LvL2DRenderer);


LvL2DRenderer::~LvL2DRenderer()
{
	ShutDown();
}

void LvL2DRenderer::PrepareDOP(const LvLDrawOp& dop)
{
	LvLDrawOp newdop = dop;
	memset(newdop.ResourceName, '\0', sizeof(dop.ResourceName));
	strcpy_s(newdop.ResourceName, dop.ResourceName);
	_pDrawOps.push_back(newdop);
}

void LvL2DRenderer::Initialize(const LvLWindowParams& wp)
{
	void* handle = LvL::Engine->GetWindowHandle(); //void* = any type
	_pRenderer = SDL_CreateRenderer((SDL_Window*)handle,-1,SDL_RENDERER_ACCELERATED);

}

bool _SortDrawOperations(const LvLDrawOp& a, const LvLDrawOp& b)
{
	return a.SortingOrder < b.SortingOrder;
}

void LvL2DRenderer::BeginDraw()
{
	_pDrawOps.clear();
	SDL_RenderClear(_pRenderer);
}

void LvL2DRenderer::Draw()
{
	std::sort(_pDrawOps.begin(), _pDrawOps.end(), _SortDrawOperations);
	SDL_Rect rect;
	rect.x = rect.y = 0;
	//int nb = _pDrawOps.size();
	for (DRAWOPLIST_IT it = _pDrawOps.begin(); it != _pDrawOps.end(); it++) 
	{
		const LvLDrawOp& dop = *it;
		iLvLTexture* lvltex = LvL::Engine->GetTexture(dop.ResourceName);
		SDL_Texture* tex = (SDL_Texture*)lvltex->GetHandle();
		XMINT2 size = lvltex->GetSize();

		size.x = (int)(size.x * dop.Scale.x);
		size.y = (int)(size.y * dop.Scale.y);
		

		rect.x = (int)(dop.Position.x - (size.x * 0.5f));
		rect.y = -(int)(dop.Position.y + (size.y * 0.5f));

		rect.w = size.x; 
		rect.h = size.y;

		SDL_RenderCopyEx(_pRenderer, tex,NULL, &rect, dop.Rotation.z,NULL,SDL_FLIP_NONE); //TODO
	}
}

void LvL2DRenderer::Present()
{
	SDL_RenderPresent(_pRenderer);
}

void LvL2DRenderer::ShutDown()
{
	if(_pRenderer)
		SDL_DestroyRenderer(_pRenderer);

	_pRenderer = NULL;
}

void* LvL2DRenderer::GetHandle()
{
	return _pRenderer;
}


iLvLRenderer* CreateRenderer(iLvLEngine* engine) 
{
	LvL::Engine = engine;
	iLvLRenderer* renderer = new LvL2DRenderer();
	
	return renderer;
}

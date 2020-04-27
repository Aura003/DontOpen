#include "pch.h"
#include "iLvLEngine.h"
#include"iLvLRenderer.h"
#include "iLvLTexture.h"
#include "LvL2DTexture.h"

LvL_IMPLEMENT_REFCOUNTED(LvL2DTexture);
using namespace std;

LvL2DTexture::LvL2DTexture(SDL_Texture* texture, const char* name)
{
	_pTexture = texture;
	//isolate the name of file
	vector<string> result;
	stringstream s_stream(name); //create string stream from the
	while (s_stream.good()) 
	 {
		string substr;
		//split the path with '/'
		getline(s_stream, substr, '\\');
		result.push_back(substr);
	 }
	
	//get the last split and set as name
	_pName = result[result.size() -1];
}
LvL2DTexture::~LvL2DTexture()
{
	SDL_DestroyTexture(_pTexture);
}

XMINT2 LvL2DTexture::GetSize()
{
	XMINT2 size;
	SDL_QueryTexture(_pTexture, NULL, NULL, &size.x, &size.y);
	return size;
}

void* LvL2DTexture::GetHandle()
{
	return _pTexture;
}


const char* LvL2DTexture::GetName()
{
	return _pName.c_str();
}

eLvLResourceType LvL2DTexture::GetType()
{
	return eLvLResourceType::rtTexture;
}

bool _loaded = false;

iLvLTexture* LoadTexture(const char* path) 
{
	if (!_loaded) 
	{
		assert(IMG_Init(IMG_INIT_PNG) != 0);
			_loaded = true;
	}
	iLvLRenderer* ir = LvL::Engine->GetRenderer();
	SDL_Renderer* renderer = (SDL_Renderer*)ir->GetHandle();
	SDL_Surface* ts = IMG_Load(path);
	if (ts)
	{
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, ts);
		iLvLTexture* tex = new LvL2DTexture(texture, path);
		SDL_FreeSurface(ts);

		return tex;
	}
	else return NULL;
}
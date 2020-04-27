#pragma once
#include "iLvLResource.h"

class iLvLTexture :public iLvLResource 
{
	
public:
	virtual void* GetHandle() = 0;
	virtual XMINT2 GetSize() = 0;
protected:
	virtual ~iLvLTexture(){}
};

extern "C" 
{
	typedef iLvLTexture* (LoadTextureFunc)(const char* path);
	LvL_API iLvLTexture* LoadTexture(const char* path);
}
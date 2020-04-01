#pragma once
#include "LvLBaseDef.h"

struct LvLWindowParams;

class iLvLEngine 
{

public:
	virtual void Initialize(const LvLWindowParams& windowParams) =0; //=0 makes it abstract 
	virtual void ShutDown() = 0;
	virtual void StartEngine() = 0;
	virtual bool Update() = 0;
	virtual void Draw() = 0;
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

#pragma once
#include "LvLBaseDef.h"

struct LvLWindowParams;
class iLvLEngine;
struct LvLDrawOp;


class iLvLRenderer
{
	LvL_ABSTRACT_REFCOUNT();

public:
	virtual void Initialize(const LvLWindowParams& wp) = 0;
	virtual void BeginDraw() = 0;
	virtual void Draw() = 0;
	virtual void Present() = 0;
	virtual void ShutDown() = 0;
	virtual void* GetHandle() = 0;
	
	virtual void PrepareDOP(const LvLDrawOp& dop) = 0;

protected:
	virtual ~iLvLRenderer() {}
};

struct LvLDrawOp 
{
	//TODO add position, rotation and sclae
	XMFLOAT3 Position = XMFLOAT3(0, 0, 0);
	XMFLOAT3 Rotation = XMFLOAT3(0, 0, 0);
	XMFLOAT3 Scale = XMFLOAT3(1,1,1);
	char ResourceName[LvL_MAXRESOURCENAME_LENGTH];

	int SortingOrder = 0;
};

extern "C" {
	typedef iLvLRenderer* (CreateRendererFunc)(iLvLEngine* engine);
	LvL_API iLvLRenderer* CreateRenderer(iLvLEngine* engine);
}
#pragma once
#include "LvLBaseDef.h"

typedef std::vector<LvLDrawOp> DRAWOPLIST;
typedef DRAWOPLIST::iterator DRAWOPLIST_IT;

class LvL2DRenderer : 	public iLvLRenderer
{
	LvL_DECLARE_REFCOUNTTED();

public:
	//LvL2DRenderer(iLvLEngine* engine);
	// Inherited via iLvLRenderer
	virtual void Initialize(const LvLWindowParams& wp) override;
	virtual void BeginDraw() override;
	virtual void Draw() override;
	virtual void Present() override;
	virtual void ShutDown() override;
	virtual void* GetHandle() override;

	virtual void PrepareDOP(const LvLDrawOp& dop) override;

private:
	SDL_Renderer* _pRenderer = NULL;
	virtual ~LvL2DRenderer();

	DRAWOPLIST _pDrawOps;

};


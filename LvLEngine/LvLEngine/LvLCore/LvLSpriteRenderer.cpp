#include "stdafx.h"
#include "iLvLRenderer.h"
#include "LvLTransform.h"
#include "LvLEntitySystem.h"
#include "LvLSpriteRenderer.h"

LvL_IMPLEMET_COMPONENT(LvLSpriteRenderer);

void LvLSpriteRenderer::Awake()
{
}

void LvLSpriteRenderer::Start()
{
}

void LvLSpriteRenderer::Update(float deltaTime)
{
}

void LvLSpriteRenderer::OnDestroy()
{
}


void LvLSpriteRenderer::PrepareDOP(iLvLRenderer* renderer)
{
	LvLDrawOp dop;
	LvLTransform* transform = _pOwner->GetTransform();
	//get the latest transform pos, rot, scale
	dop.Position = transform->Position;
	dop.Rotation = transform->Rotation;
	dop.Scale.x = transform->Scale.x *_pixelRatio;
	dop.Scale.y = transform->Scale.y *_pixelRatio;
	dop.Scale.z = transform->Scale.z * _pixelRatio;
	dop.SortingOrder = _sortingOrder;

	//set the resourcename
	strcpy_s(dop.ResourceName, _pResourceName.c_str());
	//add dop to renderer
	renderer->PrepareDOP(dop);
}

void LvLSpriteRenderer::SetSprite(const char* spriteID)
{
	_pResourceName = spriteID;
}

const char* LvLSpriteRenderer::GetSprite()
{
	return _pResourceName.c_str();
}
void LvLSpriteRenderer::SetPixelToUnitRatio(float ratio) 
{
	_pixelRatio = ratio;
}

void LvLSpriteRenderer::SetSortingOrder(int order)
{
	_sortingOrder = order;
}

int LvLSpriteRenderer::GetSortingOrder() const
{
	return _sortingOrder;
}

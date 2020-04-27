#pragma once
#include "LvLBaseDef.h"
#include "iLvLComponent.h"
class LvLSpriteRenderer : 	public iLvLComponent
{
	LvL_DECLARE_COMPONENT(LvLSpriteRenderer, eLvLComponentType::ctSpriteRenderer);
public:

	// Inherited via iLvLComponent
	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update(float deltaTime) override;
	virtual void OnDestroy() override;
	virtual void PrepareDOP(iLvLRenderer* renderer) override;
	void SetSprite(const char* spriteID);
	const char* GetSprite();
	void SetPixelToUnitRatio(float ratio);
	void SetSortingOrder(int order);
	int GetSortingOrder()const;

private:

	std::string _pResourceName;
	float _pixelRatio = 1.0f;
	int _sortingOrder = 0;
};


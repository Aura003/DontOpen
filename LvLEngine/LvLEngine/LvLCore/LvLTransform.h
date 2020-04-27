#pragma once
#include "LvLBaseDef.h"
#include "iLvLComponent.h"


class LvLTransform : 	public iLvLComponent
{
	LvL_DECLARE_COMPONENT(LvLTransform, eLvLComponentType::ctTransform);
public:

	// Inherited via iLvLComponent
	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update(float deltaTime) override;
	virtual void OnDestroy() override;
	virtual void PrepareDOP(iLvLRenderer* renderer) override;

	XMFLOAT3 Position = XMFLOAT3(0, 0, 0);
	XMFLOAT3 Rotation = XMFLOAT3(0, 0, 0);
	XMFLOAT3 Scale = XMFLOAT3(1, 1, 1);

};


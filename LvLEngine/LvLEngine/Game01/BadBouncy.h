#pragma once
#include"LvLBaseDef.h"
#include "iLvLComponent.h"

class LvLRigidBody;

class BadBouncy :public iLvLComponent
{
	LvL_DECLARE_COMPONENT(BadBouncy, eGame01ComponentType::Bouncy);

public:
	// Inherited via iLvLComponent
	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update(float deltaTime) override;
	virtual void OnDestroy() override;
	virtual void PrepareDOP(iLvLRenderer* renderer) override;
	virtual void OnTriggerEnter(LvLEntity* other) override;

private:
	LvLRigidBody* _rigid = NULL;
};


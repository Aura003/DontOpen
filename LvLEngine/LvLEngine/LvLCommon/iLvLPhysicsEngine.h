#pragma once
#include "LvLBaseDef.h"
#include "iLvLPhysicsBody.h"

class iLvLEngine;

class iLvLPhysicsEngine 
{
	LvL_ABSTRACT_REFCOUNT();
protected:
	virtual ~iLvLPhysicsEngine() {}
public:
	virtual void Initialize(const XMFLOAT3& gravity, int updatePerSecond,float pixelsToUnit) = 0;
	virtual void ShutDown() = 0;
	virtual void Update(float deltaTime) = 0;

	//creation of different bodies
	virtual iLvLPhysicsBody* CreateBox(eLvLPhysicsBody bodyType, const XMFLOAT3& externs, float density = 1.0f, float friction = 0.1f, float bounciness = 0.5f, bool isTrigger = false) = 0;
	virtual iLvLPhysicsBody* CreateSphere(eLvLPhysicsBody bodyType, float radius, float density = 1.0f, float friction = 0.1f, float bounciness = 0.5f, bool isTrigger = false) = 0;
};

extern "C" 
{
	typedef iLvLPhysicsEngine* (CreatePhysicsEngineFunc)(iLvLEngine* engine);
	LvL_API iLvLPhysicsEngine* CreatePhysicsEngine(iLvLEngine* engine);
}
#pragma once
#include "iLvLPhysicsEngine.h"

typedef std::map<b2Body*, iLvLPhysicsBody*> LvL_PHYSICSBODYMAP;
typedef LvL_PHYSICSBODYMAP::iterator LvL_PHYSICSBODYMAP_IT;

class LvLContactListener : public b2ContactListener 
{
public:
	virtual void BeginContact(b2Contact* contact) override;
	virtual void EndContact(b2Contact* contact) override;
};

class LvLPhysicsEngine2D :	public iLvLPhysicsEngine
{
	 LvL_DECLARE_REFCOUNTTED();

protected:
	virtual ~LvLPhysicsEngine2D();
public:

	LvLPhysicsEngine2D(iLvLEngine* engine);
	// Inherited via iLvLPhysicsEngine
	virtual void Initialize(const XMFLOAT3& gravity, int updatePerSecond,float pixelsToUnit) override;
	virtual void ShutDown() override;
	virtual void Update(float deltaTime) override;
	friend class LvLPhysicsBody2D;
	friend class LvLContactListener;

	// Inherited via iLvLPhysicsEngine
	virtual iLvLPhysicsBody* CreateBox(eLvLPhysicsBody bodyType, const XMFLOAT3& externs, float density = 1.0f, float friction = 0.1f, float bounciness = 0.5f, bool isTrigger = false) override;
	virtual iLvLPhysicsBody* CreateSphere(eLvLPhysicsBody bodyType, float radius, float density = 1.0f, float friction = 0.1f, float bounciness = 0.5f, bool isTrigger = false) override;

private:
	double _timeStep = 0;
	b2World* _pWorld = NULL;
	float _pixelsToUnit;
	LvLContactListener _pListener;
	LvL_PHYSICSBODYMAP _bodies;

};


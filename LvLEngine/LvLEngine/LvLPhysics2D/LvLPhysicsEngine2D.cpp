#include "pch.h"
#include "LvLPhysicsBody2D.h"
#include "LvLPhysicsEngine2D.h"

LvL_IMPLEMENT_REFCOUNTED(LvLPhysicsEngine2D);

LvLPhysicsEngine2D::LvLPhysicsEngine2D(iLvLEngine* engine)
{
	LvL::Engine = engine;
	LvL::Physics = this;
}
LvLPhysicsEngine2D::~LvLPhysicsEngine2D()
{
	
}


void LvLPhysicsEngine2D::Initialize(const XMFLOAT3& gravity, int updatePerSecond,float pixelsToUnit)
{
	_timeStep = 1.0 / updatePerSecond;
	b2Vec2 gv(gravity.x, gravity.y);
	_pWorld = new b2World(gv);
	_pixelsToUnit = pixelsToUnit;
	_pWorld->SetContactListener(&_pListener);
}

void LvLPhysicsEngine2D::ShutDown()
{
	delete _pWorld;
	_pWorld = NULL;
}

void LvLPhysicsEngine2D::Update(float deltaTime)
{
	static double _currentTimeStep = 0;
	_currentTimeStep += deltaTime;
	if (_currentTimeStep > _timeStep) 
	{
		_pWorld->Step((float)_currentTimeStep, 2, 6);
		_currentTimeStep = 0;
	}
}

iLvLPhysicsBody* LvLPhysicsEngine2D::CreateBox(eLvLPhysicsBody bodyType, const XMFLOAT3& externs, float density, float friction, float bounciness, bool isTrigger)
{
	b2BodyDef bodyDef;
	bodyDef.type = (b2BodyType)bodyType; //assuming that eLvLPhysiscBodyType is the same as b2Bodytype

	b2PolygonShape shape;
	shape.SetAsBox(externs.x / _pixelsToUnit, externs.y / _pixelsToUnit);//TODO

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;

	fixtureDef.density = density;
	fixtureDef.friction = friction;
	fixtureDef.restitution = bounciness;
	fixtureDef.isSensor = isTrigger;

	b2Body* body = _pWorld->CreateBody(&bodyDef);
	body->CreateFixture(&fixtureDef);

	LvLPhysicsBody2D* pbody = new LvLPhysicsBody2D(eLvLColliderType::clBoxCollider, body);
	//TODO store this in a map

	_bodies[body] = pbody;

	return pbody;
}

iLvLPhysicsBody* LvLPhysicsEngine2D::CreateSphere(eLvLPhysicsBody bodyType, float radius, float density, float friction, float bounciness, bool isTrigger)
{
	b2BodyDef bodyDef;
	bodyDef.type = (b2BodyType)bodyType;
	
	b2CircleShape shape;
	shape.m_p.Set(0, 0);
	shape.m_radius = radius;

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;

	fixtureDef.density = density;
	fixtureDef.friction = friction;
	fixtureDef.restitution = bounciness;
	fixtureDef.isSensor = isTrigger;

	b2Body* body = _pWorld->CreateBody(&bodyDef);
	body->CreateFixture(&fixtureDef);

	LvLPhysicsBody2D* pbody = new LvLPhysicsBody2D(eLvLColliderType::clSphereCollider, body);

	_bodies[body] = pbody;

	return pbody;
}

iLvLPhysicsEngine* CreatePhysicsEngine(iLvLEngine* engine) 
{
	iLvLPhysicsEngine* physics = new LvLPhysicsEngine2D(engine);
	return physics;
}

void LvLContactListener::BeginContact(b2Contact* contact)
{
	b2Body* bodyA = contact->GetFixtureA()->GetBody();
	b2Body* bodyB = contact->GetFixtureB()->GetBody();

	LvL_PHYSICSBODYMAP& bodies = ((LvLPhysicsEngine2D*)LvL::Physics)->_bodies;
	LvL_PHYSICSBODYMAP_IT ait = bodies.find(bodyA);
	LvL_PHYSICSBODYMAP_IT bit = bodies.find(bodyB);

	if (ait != bodies.end() && bit != bodies.end()) 
	{
		//call bodyA ontrigger
		ait->second->OnTrigger(bit->second, eLvLTriggerEvent::teEnter);
		//call bodyB ontrigger
		bit->second->OnTrigger(ait->second, eLvLTriggerEvent::teEnter);
	}
}

void LvLContactListener::EndContact(b2Contact* contact)
{
	b2Body* bodyA = contact->GetFixtureA()->GetBody();
	b2Body* bodyB = contact->GetFixtureB()->GetBody();

	LvL_PHYSICSBODYMAP& bodies = ((LvLPhysicsEngine2D*)LvL::Physics)->_bodies;
	LvL_PHYSICSBODYMAP_IT ait = bodies.find(bodyA);
	LvL_PHYSICSBODYMAP_IT bit = bodies.find(bodyB);

	if (ait != bodies.end() && bit != bodies.end())
	{
		//call bodyA ontrigger
		ait->second->OnTrigger(bit->second, eLvLTriggerEvent::teExit);
		//call bodyB ontrigger
		bit->second->OnTrigger(ait->second, eLvLTriggerEvent::teExit);
	}
}


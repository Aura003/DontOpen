#include "pch.h"
#include "LvLPhysicsEngine2D.h"
#include "LvLPhysicsBody2D.h"

LvL_IMPLEMENT_REFCOUNTED(LvLPhysicsBody2D);

LvLPhysicsBody2D::LvLPhysicsBody2D(eLvLColliderType colliderType, b2Body* body)
{
	_pColliderType = colliderType;
	_pBody = body;
}

LvLPhysicsBody2D::~LvLPhysicsBody2D()
{
	((LvLPhysicsEngine2D*)LvL::Physics)->_bodies.erase(_pBody);
	((LvLPhysicsEngine2D*)LvL::Physics)->_pWorld->DestroyBody(_pBody);
	_pBody = NULL;
}


void* LvLPhysicsBody2D::GetHandle() const
{
	return _pBody;
}

eLvLPhysicsBody LvLPhysicsBody2D::GetBodyType() const
{
	return (eLvLPhysicsBody)_pBody->GetType();
}

eLvLColliderType LvLPhysicsBody2D::GetColliderType() const //const for no dynamic data
{
	return _pColliderType;
}

void LvLPhysicsBody2D::SetTransform(const XMFLOAT3& position, const XMFLOAT3& rotation, const XMFLOAT3& scale)
{
	float pixelsToUnit = ((LvLPhysicsEngine2D*)LvL::Physics)->_pixelsToUnit;
	b2Vec2 pos(position.x / pixelsToUnit, position.y / pixelsToUnit);

	_pBody->SetTransform(pos, -rotation.z * LvL_DEG2RAD);
}

void LvLPhysicsBody2D::GetTransform(XMFLOAT3& position, XMFLOAT3& rotation, XMFLOAT3& scale)
{
	float pixelsToUnit = ((LvLPhysicsEngine2D*)LvL::Physics)->_pixelsToUnit;
	b2Vec2 pos = _pBody->GetPosition();
	float angle = _pBody->GetAngle();
	position.x = pos.x * pixelsToUnit;
	position.y = pos.y * pixelsToUnit;
	rotation.z = -angle * LvL_RAD2DEG;
}

void LvLPhysicsBody2D::AddForce(const XMFLOAT3& force)
{
	b2Vec2 bf(force.x, force.y);
	_pBody->ApplyForceToCenter(bf, true);
}

void LvLPhysicsBody2D::SetTriggerEvent(LvLOnTriggerFunc func, void* context)
{
	_pContext = context;
	_OnTrigger = func;
}

void LvLPhysicsBody2D::OnTrigger(iLvLPhysicsBody* other, eLvLTriggerEvent triggerEvent)
{
	_OnTrigger(other, triggerEvent, _pContext);
}

void LvLPhysicsBody2D::SetOwner(void* owner)
{
	_pOwner = owner;
}

void* LvLPhysicsBody2D::GetOwner() const
{
	return _pOwner;
}

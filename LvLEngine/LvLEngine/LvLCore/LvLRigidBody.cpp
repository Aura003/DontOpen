#include "stdafx.h"
#include "LvLTransform.h"
#include "LvLEntitySystem.h"
#include "LvLRigidBody.h"

LvL_IMPLEMET_COMPONENT(LvLRigidBody);

void LvLRigidBody::Awake()
{
}

void LvLRigidBody::Start()
{
}

void LvLRigidBody::Update(float deltaTime)
{
	if (_pBody->GetBodyType() == eLvLPhysicsBody::btDynamicBody) 
	{
		LvLTransform* transform = GetTransform();
		_pBody->GetTransform(transform->Position, transform->Rotation,transform->Scale);
	}
	else 
	{
		UpdateBodyTransform();
	}
}

void LvLRigidBody::OnDestroy()
{
}

void LvLRigidBody::PrepareDOP(iLvLRenderer* renderer)
{
}

void _OnTrigger(iLvLPhysicsBody* other, eLvLTriggerEvent triggerEvent, void* context) 
{
	LvLRigidBody* otherbody = (LvLRigidBody*)other->GetOwner();
	switch (triggerEvent)
	{
	case eLvLTriggerEvent::teEnter:
		((LvLRigidBody*)context)->GetEntity()->OnTriggerEnter(otherbody->GetEntity());
		break;
	case eLvLTriggerEvent::teExit:
		((LvLRigidBody*)context)->GetEntity()->OnTriggerExit(otherbody->GetEntity());
		break;
	default:
		break;
	}
	

}

void LvLRigidBody::SetBody(iLvLPhysicsBody* body)
{
	LvL_SAFERELEASE(_pBody);
	_pBody = body;
	_pBody->AddRef();
	_pBody->SetOwner(this);
	_pBody->SetTriggerEvent(&_OnTrigger, this);
}

void LvLRigidBody::UpdateBodyTransform()
{
	LvLTransform* transform = GetTransform();
	_pBody->SetTransform(transform->Position, transform->Rotation, transform->Scale);

}

void LvLRigidBody::AddForce(const XMFLOAT3& force)
{
	_pBody->AddForce(force);
}

void LvLRigidBody::SetLinearVelocity(const XMFLOAT3& v)
{
	_pBody->SetLinearVelocity(v);
}

void LvLRigidBody::SetAngularVelocity(float omega)
{
	_pBody->SetAngularVelocity(omega);
}

XMFLOAT3 LvLRigidBody::GetLinearVelocity() const
{
	return _pBody->GetLinearVelocity();
}

XMFLOAT3 LvLRigidBody::GetAngularVelocity() const
{
	return _pBody->GetAngularVelocity();
}

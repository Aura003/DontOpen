#pragma once
#include "iLvLPhysicsBody.h"
class LvLPhysicsBody2D : public iLvLPhysicsBody
{
	LvL_DECLARE_REFCOUNTTED();
protected:
	virtual ~LvLPhysicsBody2D();

public:
	LvLPhysicsBody2D(eLvLColliderType colliderType, b2Body* body);

	// Inherited via iLvLPhysicsBody
	virtual void* GetHandle() const override;

	virtual eLvLPhysicsBody GetBodyType() const override;
	virtual eLvLColliderType GetColliderType() const override;
	virtual void SetTransform(const XMFLOAT3& position, const XMFLOAT3& rotation, const XMFLOAT3& scale) override;
	virtual void GetTransform(XMFLOAT3& position, XMFLOAT3& rotation, XMFLOAT3& scale) override;
	
	virtual void AddForce(const XMFLOAT3& force) override;

	virtual void SetTriggerEvent(LvLOnTriggerFunc func, void* context) override;
	virtual void OnTrigger(iLvLPhysicsBody* other, eLvLTriggerEvent triggerEvent) override;
	virtual void SetOwner(void* owner) override;
	virtual void* GetOwner() const override;

private:
	b2Body* _pBody = NULL;
	eLvLColliderType _pColliderType;

	void* _pContext = NULL;
	void* _pOwner = NULL;
	LvLOnTriggerFunc _OnTrigger = NULL;

};


#pragma once
#include "LvLBaseDef.h"
#include "iLvLComponent.h"
#include "iLvLPhysicsBody.h"


class LvLRigidBody : 	public iLvLComponent
{
	LvL_DECLARE_COMPONENT(LvLRigidBody, eLvLComponentType::ctRigidbody);
public:
	
	// Inherited via iLvLComponent
	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update(float deltaTime) override;
	virtual void OnDestroy() override;
	virtual void PrepareDOP(iLvLRenderer* renderer) override;

	void SetBody(iLvLPhysicsBody* body);
	void UpdateBodyTransform();

	void AddForce(const XMFLOAT3& force);
	void SetLinearVelocity(const XMFLOAT3& v);
	void SetAngularVelocity(float omega);
	XMFLOAT3 GetLinearVelocity()const;
	XMFLOAT3 GetAngularVelocity()const;
	

private:
	iLvLPhysicsBody* _pBody = NULL;

};


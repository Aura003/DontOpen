#pragma once
#include "LvLBaseDef.h"

enum eLvLColliderType 
{
	clNoCollider,
	clBoxCollider,
	clSphereCollider,
	clPolygonCollider
};

enum eLvLPhysicsBody 
{
	btStaticBody=0,
	btKinematicBody,
	btDynamicBody
};
enum eLvLTriggerEvent 
{
	teEnter,
	teExit
};

class iLvLPhysicsBody;
typedef void(*LvLOnTriggerFunc)(iLvLPhysicsBody* other, eLvLTriggerEvent triggerEvent, void*); //Callback

class iLvLPhysicsBody 
{
	LvL_ABSTRACT_REFCOUNT();
protected:
	virtual ~iLvLPhysicsBody() {}
public:
	virtual void* GetHandle() const = 0;
	virtual eLvLPhysicsBody GetBodyType() const = 0;
	virtual eLvLColliderType GetColliderType() const = 0;

	virtual void SetTransform(const XMFLOAT3& position, const XMFLOAT3& rotation, const XMFLOAT3& scale) = 0;
	virtual void GetTransform(XMFLOAT3& position, XMFLOAT3& rotation, XMFLOAT3& scale) = 0;
	
	virtual void AddForce(const XMFLOAT3& force) = 0;
	virtual void SetLinearVelocity(const XMFLOAT3& v) = 0;
	virtual XMFLOAT3& GetLinearVelocity() const = 0;
	virtual void SetAngularVelocity(float omega) = 0;
	virtual XMFLOAT3& GetAngularVelocity() const = 0;
	virtual void ApplyTorque(float torque, bool wake) = 0;



	//ADD MORE! - ASSIGNMENT
	//velocity - Get and Set
	//Angular Velocity - Get and Set
	//Torque - add
	//Note: must be implemented in RigidBody

	//implement text rendering(LvL2D) and/or Play Sound (seperate DLL)

	//collision event
	virtual void SetTriggerEvent(LvLOnTriggerFunc func, void* context) = 0;
	virtual void OnTrigger(iLvLPhysicsBody* other, eLvLTriggerEvent triggerEvent) = 0;
	virtual void SetOwner(void* owner) = 0;
	virtual void* GetOwner() const = 0;
};
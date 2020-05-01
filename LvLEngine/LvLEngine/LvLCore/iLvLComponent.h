#pragma once
#include "LvLBaseDef.h"

class LvLEntity;
class iLvLRenderer;

enum eLvLComponentType 
{
	ctTransform,
	ctSpriteRenderer,
	ctRigidbody,
	ctAudioSource,
	ctHIGHEST
};

enum eLvLComponentState 
{
	esCreated,
	esAwaken,
	esStarted,

};

class iLvLComponent
{
	LvL_ABSTRACT_REFCOUNT();
public:
	virtual ~iLvLComponent() {}
	virtual void Awake() = 0;
	virtual void Start() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void OnDestroy() = 0;
	virtual LvLEntity* GetEntity() = 0;
	virtual eLvLComponentType GetType() = 0;
	virtual void PrepareDOP(iLvLRenderer* renderer) = 0;
	virtual eLvLComponentState GetState() const = 0;
	friend class LvLEntity;

	virtual void OnTriggerEnter(LvLEntity* other) {}
	virtual void OnTriggerExit(LvLEntity* other) {}
protected:
	virtual void SetState(eLvLComponentState state) = 0;
};
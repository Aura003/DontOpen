#pragma once
#include "LvLBaseDef.h"
#include "iLvLComponent.h"
#include "LvLTransform.h"
#include "iLvLSound.h"

class iLvLSound;

class LvLAudioSource :	public iLvLComponent
{
	LvL_DECLARE_COMPONENT(LvLAudioSource,eLvLComponentType::ctAudioSource)
public:
	// Inherited via iLvLComponent
	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update(float deltaTime) override;
	virtual void OnDestroy() override;
	virtual void PrepareDOP(iLvLRenderer* renderer) override;

	void Play();
	void SetAutio(const char* path);
private:
	iLvLSound* _pAudio = NULL;
protected:
	~LvLAudioSource();

};


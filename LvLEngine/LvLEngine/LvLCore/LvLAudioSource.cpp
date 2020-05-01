#include "stdafx.h"
#include "LvLTransform.h"
#include "LvLEntitySystem.h"
#include "LvLAudioSource.h"
#include "LvLResourceManager.h"
#include "iLvLEngine.h"

LvL_IMPLEMET_COMPONENT(LvLAudioSource);

LvLAudioSource::~LvLAudioSource()
{
	LvL_SAFERELEASE(_pAudio);
}
void LvLAudioSource::Awake()
{
}

void LvLAudioSource::Start()
{
}

void LvLAudioSource::Update(float deltaTime)
{
	_pAudio->Play();
}

void LvLAudioSource::OnDestroy()
{
}

void LvLAudioSource::PrepareDOP(iLvLRenderer* renderer)
{
}

void LvLAudioSource::Play()
{
	_pAudio->Play();
}

void LvLAudioSource::SetAutio(const char* path)
{
	_pAudio =(iLvLSound*) _pOwner->GetEntitySystem()->GetEngine()->GetResourceManager()->Get(path);
	_pAudio->AddRef();
}


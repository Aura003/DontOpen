#include "pch.h"
#include "LvLTransform.h"
#include "LvLEntitySystem.h"
#include "iLvLEngine.h"
#include "iLvLRenderer.h"
#include"Game01Common.h"
#include "BadBouncy.h"
#include "LvLRigidBody.h"
#include "Game01.h"

LvL_IMPLEMET_COMPONENT(BadBouncy);

void BadBouncy::Awake()
{
	_rigid = _pOwner->GetComponent<LvLRigidBody>();
}

void BadBouncy::Start()
{

}

void BadBouncy::Update(float deltaTime)
{
	//_pOwner->GetTransform()->Scale = XMFLOAT3(0.5f, 0.5f, 1);
	float horizontal = 0;
	if (LvL::Input->GetButton("forward"))
		horizontal = 1;
	else if (LvL::Input->GetButton("backward"))
		horizontal = -1;
	if (horizontal != 0) {
		_rigid->AddForce(XMFLOAT3(200 * deltaTime * horizontal, 0, 0));
	}
	if (LvL::Input->GetButtonDown("jump")) 
	{
		_rigid->AddForce(XMFLOAT3(0,600,0));
	}
		
	XMFLOAT3 currentPos = GetTransform()->Position;
	LvL::Engine->GetRenderer()->SetCameraPosition(currentPos);
}

void BadBouncy::OnDestroy()
{
}


void BadBouncy::PrepareDOP(iLvLRenderer* renderer)
{
}

void BadBouncy::OnTriggerEnter(LvLEntity* other)
{
	if(other->Tag==(int)eGame01Tag::tagPlatform)
		Game01::Game->Score++;

	printf("Triggered");
}

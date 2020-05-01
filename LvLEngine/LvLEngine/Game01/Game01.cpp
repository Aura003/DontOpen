#include "pch.h"
#include "LvLUtils.h"
#include "LvLEntitySystem.h"
#include  "LvLSpriteRenderer.h"
#include "LvLTransform.h"
#include "LvLRigidBody.h"
#include "iLvLPhysicsEngine.h"
#include"iLvLEngine.h"
#include "iLvLGame.h"
#include "iLvLSoundSystem.h"
#include "LvLAudioSource.h"  //from core - component
#include "Game01Common.h"
#include "BadBouncy.h"
#include "Game01.h"

Game01* Game01::Game = NULL;

LvL_IMPLEMENT_REFCOUNTED(Game01);

LvLEntity* _CreatePlatform(XMFLOAT3 pos) 
{
	float pixelRatio = 0.2f;
	LvLEntitySystem& es = *LvL::Engine->GetEntitySystem();
	LvLEntity* bouncy = es.CreateEntity();
	LvLSpriteRenderer* sr = bouncy->AddComponent<LvLSpriteRenderer>();
	sr->SetSprite("Sci_Fi_BG.png");
	sr->SetPixelToUnitRatio(pixelRatio);
	bouncy->GetTransform()->Position = XMFLOAT3(pos);
	XMINT2 size = LvLUtils::GetTextureSize(LvL::Engine, "Ohyea.png", pixelRatio);
	return bouncy;
}
void Game01::LoadGame(iLvLEngine* engine)
{
	Game = this;
	LvL::Engine = engine;
	LvL::Input = engine->GetInput();
	LvL::Physics = engine->GetPhysicsEngine();
	LvL::SoundSystem = engine->GetSoundSystem();
	LvL::SoundSystem->LoadBGM("bgm.wav");
	LvL::SoundSystem->Play();

	LvL::Input->MapButtonKey("forward", 2, (int)'d', kcArrowRight);
	LvL::Input->MapButtonKey("backward", 2, (int)'a', kcArrowLeft);
	LvL::Input->MapButtonKey("jump", 1, (int)' ');

	float pixelRatio = 0.25f;
	LvLEntitySystem& es = *LvL::Engine->GetEntitySystem();
	LvLEntity* bouncy = es.CreateEntity("bouncy", true);
	bouncy->GetTransform()->Position = XMFLOAT3(0, 0, 0);
	LvLSpriteRenderer* sr = bouncy->AddComponent<LvLSpriteRenderer>();//new LvLSpriteRenderer(bouncy);
	sr->SetSprite("Ohyea.png");
	sr->SetPixelToUnitRatio(pixelRatio);
	sr->SetSortingOrder(91);
	//BadBouncy* b = new BadBouncy(bouncy);
	bouncy->AddComponent<BadBouncy>();
	LvLRigidBody* rigid = bouncy ->AddComponent<LvLRigidBody>();
	XMINT2 bouncysize = LvLUtils::GetTextureSize(LvL:: Engine, "Ohyea.png", pixelRatio);
	iLvLPhysicsBody* body = LvL::Physics->CreateBox(eLvLPhysicsBody::btDynamicBody, XMFLOAT3(bouncysize.x/2,bouncysize.y/2, 0));
	rigid->SetBody(body);
	rigid->UpdateBodyTransform();
	   

	LvLEntity* BG = es.CreateEntity("Sci_Fi_BG");
	LvLSpriteRenderer* sp = BG->AddComponent<LvLSpriteRenderer>();
	BG->GetTransform()->Position = XMFLOAT3(0, 0, 0);
	sp->SetSprite("Sci_Fi_BG.png");
	sp->SetPixelToUnitRatio(pixelRatio);
	sp->SetSortingOrder(90);
	XMINT2 size = LvLUtils::GetTextureSize(LvL::Engine, "Sci_Fi_BG.png", pixelRatio);

	LvLEntity* platform = es.CreateEntity("Sci_Fi_Platform");
	LvLSpriteRenderer* splat = platform->AddComponent<LvLSpriteRenderer>();
	platform->GetTransform()->Position = XMFLOAT3(0, -130, 0);
	splat->SetSprite("Sci_Fi_Platform.png");
	splat->SetPixelToUnitRatio(pixelRatio);
	splat->SetSortingOrder(91);
	XMINT2 size2 = LvLUtils::GetTextureSize(LvL::Engine, "Sci_Fi_BG.png", pixelRatio);
	LvLRigidBody* rigidplatform = platform->AddComponent<LvLRigidBody>();
	iLvLPhysicsBody* bouncybody = LvL::Physics->CreateBox(eLvLPhysicsBody::btStaticBody, XMFLOAT3(size.x / 10, size.y / 10, 0));
	rigidplatform->SetBody(bouncybody);
	rigidplatform->UpdateBodyTransform();
	
	//for (size_t i = 0; i < 3; i++) 
	//{
	//	_CreatePlatform(XMFLOAT3(100 + 115 * i, -300, 0));
	//}
}

void Game01::EndGame()
{
}


iLvLGame* CreateGame(iLvLEngine* engine) 
{
	Game01* game = new Game01();
	return game;
}
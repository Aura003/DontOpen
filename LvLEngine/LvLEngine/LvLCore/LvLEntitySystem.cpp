#include "stdafx.h"
#include "iLvLComponent.h"
#include"LvLTransform.h"
#include "LvLEntitySystem.h"

using namespace std;

#define LvL_COMPONENTFUNC(func, cmap)\
LvL_COMPONENTMAP& ccmap = cmap;\
for(LvL_COMPONENTMAP_IT cit = ccmap.begin(); cit!= ccmap.end();cit++)\
{ cit->second->func; }

#define LvL_ENTITYFUNC(func)\
for(LvL_ENTITYMAP_IT it=_pEntities.begin(); it!=_pEntities.end(); it++)\
{  it->second->func;}

int _anonymousEntity = 0;
LvLEntitySystem::LvLEntitySystem(iLvLEngine * engine)
{
}
LvLEntity* LvLEntitySystem::CreateEntity(bool withTransform)
{
	_anonymousEntity++;
	string name = string("anonymous") + std::to_string(_anonymousEntity);
	return CreateEntity(name.c_str(), withTransform);
}

LvLEntity* LvLEntitySystem::CreateEntity(const char* name, bool withTransform)
{
	//check if entity name already exists
	string sname = name;
	LvL_ENTITYMAP_IT it = _pEntities.find(sname);
	if (it != _pEntities.end()) 
		return NULL;
	else 
	{
		LvLEntity* entity = new LvLEntity(name, this);
		_pEntities[sname] = entity;
		if (withTransform) 
		{
			LvLTransform* transform = new LvLTransform(entity);
			entity->_pTransform = transform;
		}
		return entity;
	}
}

LvLEntity* LvLEntitySystem::GetEntity(const char* name)
{
	string sname = name;
	LvL_ENTITYMAP_IT it = _pEntities.find(sname);
	if (it != _pEntities.end()) return it->second;
	else return NULL;
}

void LvLEntitySystem::DeleteEntity(const char* name)
{
	string sname = name;
	LvL_ENTITYMAP_IT it = _pEntities.find(sname);
	if (it != _pEntities.end()) 
	{
		_pGarbageBin.push_back(it->second);
	
	}
}

void LvLEntitySystem::PrepareDOP(iLvLRenderer* renderer)
{
	LvL_ENTITYFUNC(PrepareDOP(renderer));
}

void LvLEntitySystem::Update(float deltaTime)
{
	while (_pGarbageBin.size()>0)
	{
		int i = _pGarbageBin.size();
		LvLEntity* entity = _pGarbageBin[i - 1];
		entity->OnDestroy();
		_pEntities.erase(entity->_pName);
		_pGarbageBin.pop_back();
		delete entity;
	}
	LvL_ENTITYFUNC(Update(deltaTime));
	
}

iLvLEngine* LvLEntitySystem::GetEngine()
{
	return _pEngine;
}


bool LvLEntity::AddComponent(iLvLComponent* component)
{
	//check if component type already exists
	int type = component->GetType();
	//if exists return null
	LvL_COMPONENTMAP_IT it = _pComponents.find(type);
	if (it != _pComponents.end())return NULL;
	else
	{
			//TODO must assign an owner
			//else register to map
		_pComponents[type] = component;
		return true;;
	}
}



iLvLComponent* LvLEntity::GetComponent(int type)
{
	LvL_COMPONENTMAP_IT it = _pComponents.find(type);
	if (it != _pComponents.end()) return it->second;
	else return NULL;
}

void LvLEntity::DeleteComponent(int type)
{
	LvL_COMPONENTMAP_IT it = _pComponents.find(type);
	if (it != _pComponents.end()) 
	{
		//TODO release the component
		_pComponents.erase(type);
	}
}

void LvLEntity::PrepareDOP(iLvLRenderer* renderer)
{
	LvL_COMPONENTFUNC(PrepareDOP(renderer), _pComponents);
}

LvLTransform* LvLEntity::GetTransform()
{
	return _pTransform;
}

void LvLEntity::OnTriggerEnter(LvLEntity* other)
{
	LvL_COMPONENTFUNC(OnTriggerEnter(other), _pComponents);
}

void LvLEntity::OnTriggerExit(LvLEntity* other)
{
	LvL_COMPONENTFUNC(OnTriggerExit(other), _pComponents);
}

LvLEntitySystem* LvLEntity::GetEntitySystem() const
{
	return _entitySystem;
}

LvLEntity::~LvLEntity()
{
	LvL_COMPONENTFUNC(Release(), _pComponents);
}

LvLEntity::LvLEntity(const char* name, LvLEntitySystem* system)
{
	_pName = name;
	_entitySystem = system;
}

void LvLEntity::Awake()
{
	LvL_COMPONENTFUNC(Awake(), _pComponents);
}

void LvLEntity::Start()
{
	LvL_COMPONENTFUNC(Start(), _pComponents);
}

void LvLEntity::Update(float deltaTime)
{
	//LvL_COMPONENTFUNC(Update(deltaTime), _pComponents);
	FOREACH(LvL_COMPONENTMAP_IT, it, _pComponents) 
	{
		iLvLComponent* comp = it->second;
		switch (comp->GetState()) 
		{
		case eLvLComponentState::esCreated:
			comp->Awake();
			comp->SetState(eLvLComponentState::esAwaken);
			break;
		case eLvLComponentState::esAwaken:
			comp->Start();
			comp->SetState(eLvLComponentState::esStarted);
			break;
		case eLvLComponentState::esStarted:
			comp->Update(deltaTime);
			break;
		default:
			break;
		}
	}
}

void LvLEntity::OnDestroy()
{
	LvL_COMPONENTFUNC(OnDestroy(), _pComponents);
}

void LvLEntity::DeleteEnity()
{
	GetEntitySystem()->DeleteEntity(_pName.c_str());
}

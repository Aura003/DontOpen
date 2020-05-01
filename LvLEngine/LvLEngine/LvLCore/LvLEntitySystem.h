#pragma once

#include "iLvLComponent.h"
class iLvLComponent;
class LvLEntity;
class iLvLRenderer;
class LvLTransform;
class iLvLEngine;

//map for entities (key = name)
typedef std::map<std::string, LvLEntity*> LvL_ENTITYMAP;
typedef LvL_ENTITYMAP::iterator LvL_ENTITYMAP_IT;

//map for components (key = type/int)
typedef std::map<int, iLvLComponent*> LvL_COMPONENTMAP;
typedef LvL_COMPONENTMAP::iterator LvL_COMPONENTMAP_IT;

typedef std::vector<LvLEntity*> LvL_ENTITYLIST;
typedef LvL_ENTITYLIST::iterator LvL_ENTITYLIST_IT;

class LvLEntitySystem
{
public:
		//create entityl
		LvLEntitySystem(iLvLEngine* engine);
		LvLEntity* CreateEntity(bool withTransform = true);
		LvLEntity* CreateEntity(const char* name, bool withTransform = true);
		LvLEntity* GetEntity(const char* name);
		//delete entity
		void DeleteEntity(const char* name);

		void PrepareDOP(iLvLRenderer* renderer);
		void Update(float deltaTime);

		iLvLEngine* GetEngine();
private:
		//map of entities with name as ID
	iLvLEngine* _pEngine = NULL;
	LvL_ENTITYMAP _pEntities;
	LvL_ENTITYLIST _pGarbageBin;
};
class LvLEntity
{
public:
	LvLEntity(const char* name, LvLEntitySystem* system);
	void Awake();
	void Start();
	void Update(float deltaTime);
	void OnDestroy();

	void DeleteEnity();

	bool AddComponent(iLvLComponent* component);
	template<class T>
	T* AddComponent() 
	{
		T* component = new T(this);
		AddComponent(component);
		return component;
	}
	template<class T>
	T* GetComponent() 
	{
		int i = T::Type;
		eLvLComponentType type = (eLvLComponentType)i;
		T* component = (T*)GetComponent(type);
		if (component != NULL) return (T*)component;
		else return NULL;
	}

	iLvLComponent* GetComponent(int type);
	void DeleteComponent(int type);

	void PrepareDOP(iLvLRenderer* renderer);
	LvLTransform* GetTransform();

	void OnTriggerEnter(LvLEntity* other);
	void OnTriggerExit(LvLEntity* other);
	LvLEntitySystem* GetEntitySystem() const;

	int Tag = 0;

private:
	~LvLEntity();
	std::string _pName;
	LvL_COMPONENTMAP _pComponents;
	friend class LvLEntitySystem;
	LvLTransform* _pTransform = NULL;
	LvLEntitySystem* _entitySystem = NULL;
};
//enitity
//map of iComponents
//enitity will have a name
//addComponent
//deleteComponent
//getComponent
//prepareDOP calls the component PrepareDOP
//awake, start, update, ondestory - calling component's

//iComponent
//int as the component type
//reference to the owner entity
//awake, start, update, ondestroy
//prepareDOP

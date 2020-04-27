#pragma once

#include "iLvLComponent.h"
class iLvLComponent;
class LvLEntity;
class iLvLRenderer;
class LvLTransform;

//map for entities (key = name)
typedef std::map<std::string, LvLEntity*> LvL_ENTITYMAP;
typedef LvL_ENTITYMAP::iterator LvL_ENTITYMAP_IT;

//map for components (key = type/int)
typedef std::map<int, iLvLComponent*> LvL_COMPONENTMAP;
typedef LvL_COMPONENTMAP::iterator LvL_COMPONENTMAP_IT;

class LvLEntitySystem
{
public:
		//create entityl
		LvLEntity* CreateEntity(const char* name, bool withTransform = true);
		LvLEntity* GetEntity(const char* name);
		//delete entity
		void DeleteEntity(const char* name);
		void PrepareDOP(iLvLRenderer* renderer);
		void Update(float deltaTime);
private:
		//map of entities with name as ID
	LvL_ENTITYMAP _pEntities;
};
class LvLEntity
{
public:
	LvLEntity(const char* name);
	void Awake();
	void Start();
	void Update(float deltaTime);
	void OnDestroy();

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

private:
	std::string _pName;
	LvL_COMPONENTMAP _pComponents;
	friend class LvLEntitySystem;
	LvLTransform* _pTransform = NULL;
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

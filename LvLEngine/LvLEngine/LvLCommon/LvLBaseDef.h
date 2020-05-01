#pragma once

#define NULL 0

#define LvL_PI 3.14159265359f
#define LvL_DEG2RAD LvL_PI / 180.0f
#define LvL_RAD2DEG 180.0f / LvL_PI

#ifdef LvL_API_EXPORTS //all Dll that need to export stuff
#define LvL_API __declspec(dllexport)
#else
#define LvL_API __declspec(dllimport)
#endif

#define LvL_SAFERELEASE(p)\
if (p) {p->Release(); p=NULL;}

#define FOREACH(iteratortype, iterator, map)\
for(iteratortype iterator = map.begin(); iterator!=map.end(); iterator++)

#define LvL_MAXRESOURCENAME_LENGTH 30


//Begining of Ref Counted stuff
#define LvL_ABSTRACT_REFCOUNT()\
public:\
	virtual void AddRef() = 0;\
	virtual int Release() = 0;\
	virtual int GetRefCount() = 0;

#define LvL_DECLARE_REFCOUNTTED()\
public:\
	virtual void AddRef()  override;\
	virtual int Release()  override;\
	virtual int GetRefCount()  override;\
private:\
	int _iRefCount = 0;

#define LvL_IMPLEMENT_REFCOUNTED(nspace)\
void nspace::AddRef(){_iRefCount++;}\
int nspace::Release()\
{\
if(--_iRefCount<=0){\
	delete this;\
	return 0;\
} else return _iRefCount;\
}\
int nspace::GetRefCount() {return _iRefCount;}

//#define LvL_DECLARE_DIRECT_REFCOUNTED()


#define LvL_DECLARE_COMPONENT(classType, componentType)\
LvL_DECLARE_REFCOUNTTED();\
public:\
classType(LvLEntity* owner);\
static const eLvLComponentType Type = (eLvLComponentType)componentType;\
virtual eLvLComponentType GetType() override;\
virtual LvLEntity* GetEntity() override;\
LvLTransform* GetTransform() const;\
virtual eLvLComponentState GetState() const override;\
friend class LvLEntity;\
protected:\
virtual void SetState(eLvLComponentState state) override;\
private:\
LvLEntity* _pOwner = NULL;\
eLvLComponentState _state = eLvLComponentState::esCreated;

#define LvL_IMPLEMET_COMPONENT(classType)\
LvL_IMPLEMENT_REFCOUNTED(classType);\
classType::classType(LvLEntity* owner)\
	{_pOwner = owner; owner->AddComponent(this);}\
eLvLComponentType classType::GetType()\
	{return classType::Type;}\
LvLEntity* classType::GetEntity()\
	{return _pOwner;}\
LvLTransform* classType::GetTransform() const\
{return _pOwner->GetTransform();}\
eLvLComponentState classType::GetState() const\
{return _state;}\
void classType::SetState(eLvLComponentState state)\
{_state = state; }
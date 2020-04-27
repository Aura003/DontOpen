#include "stdafx.h"
#include "iLvLResource.h"
#include "LvLResourceManager.h"

using namespace std;

void LvLResourceManager::Add(iLvLResource* res)
{
	string id = res->GetName();
	//check if id exists
	LvL_RESOURCEMAP_IT it = _resourceMap.find(id);
	if (it != _resourceMap.end()) 
	{
		//if it does, then release that resource
		it->second->Release();
	}
	//insert resource in map
	_resourceMap[id] = res;
}

void LvLResourceManager::Release(const char* resID)
{
	string id = resID; //const char* to std::string
	LvL_RESOURCEMAP_IT it = _resourceMap.find(id);
	if (it != _resourceMap.end()) 
	{
		it->second->Release();
		_resourceMap.erase(id);
	}
}

iLvLResource* LvLResourceManager::Get(const char* resID)
{
	string id = resID; //const char* to std::string
	LvL_RESOURCEMAP_IT it = _resourceMap.find(id);
	if (it != _resourceMap.end()) 
	{
		return it->second;
	}
	else return NULL;
}

int LvLResourceManager::GetCount()
{
	return (int)_resourceMap.size();
}

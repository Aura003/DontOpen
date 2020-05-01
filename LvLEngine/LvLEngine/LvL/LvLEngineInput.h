#pragma once
#include "iLvLInput.h"

union SDL_Event;

typedef std::vector<int> LvL_KEYLIST;
typedef LvL_KEYLIST::iterator LvL_KEYLIST_IT;

struct LvLInputMap
{
	eLvLInputState State = isNothing;
	LvL_KEYLIST Keys;
};

typedef std::map<std::string, LvLInputMap> LvL_KEYMAP;
typedef LvL_KEYMAP::iterator LvL_KEYMAP_IT;

class LvLEngineInput : public iLvLInput 
{
public:

	// Inherited via iLvLInput
	virtual void MapButtonKey(const char* name, int count, ...) override;
	virtual void Refresh() override;
	virtual bool GetButtonDown(const char* name) override;
	virtual bool GetButton(const char* name) override;
	virtual bool GetButtonUp(const char* name) override;
	virtual XMINT2 GetMousePosition() const override;


	void ProcessEvent(SDL_Event* sd);

private:
	LvL_KEYMAP _pKeyBindings;


};
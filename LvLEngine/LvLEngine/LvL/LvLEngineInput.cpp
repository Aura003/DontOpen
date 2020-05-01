#include "stdafx.h"
#include "LvLEngineInput.h"

void LvLEngineInput::MapButtonKey(const char* name, int count, ...)
{
	//instantiate LvLInputMap and register to keybinding map
	LvLInputMap& map = _pKeyBindings[name] = LvLInputMap();

	va_list list; //for optional muliple params object[]
	va_start(list, count);
	for (int i = 0; i < count; i++)
	{
		int key = va_arg(list, int);
		map.Keys.push_back(key);
	}
	va_end(list);
}

void LvLEngineInput::Refresh()
{
	//for (LvL_KEYMAP_IT it = _pKeyBindings.begin();it!=_pKeyBindings.end();it++) 
	FOREACH(LvL_KEYMAP_IT, it, _pKeyBindings)
	{
		LvLInputMap& map = it->second;
		switch (map.State)
		{
		case eLvLInputState::isInputDown:
			map.State = eLvLInputState::isInputHold; break;
		case eLvLInputState::isInputUp:
			map.State = eLvLInputState::isNothing; break;
		}
	}
}

bool LvLEngineInput::GetButtonDown(const char* name)
{
	LvLInputMap& map = _pKeyBindings[name];
	return map.State == eLvLInputState::isInputDown;
}

bool LvLEngineInput::GetButton(const char* name)
{
	LvLInputMap& map = _pKeyBindings[name];
	return map.State == eLvLInputState::isInputHold;
}

bool LvLEngineInput::GetButtonUp(const char* name)
{
	LvLInputMap& map = _pKeyBindings[name];
	return map.State == eLvLInputState::isInputUp;
}


void ProcessKeyboard(SDL_Event* sd, LvL_KEYMAP& map, eLvLInputState state)
{
	int key = sd->key.keysym.sym;
	FOREACH(LvL_KEYMAP_IT, it, map)
	{
		LvLInputMap& imap = it->second;
		FOREACH(LvL_KEYLIST_IT, kit, imap.Keys)
		{
			if (key == *kit)
			{
				imap.State = state;
				break;
			}
		}
	}
}

void LvLEngineInput::ProcessEvent(SDL_Event* sd)
{
	switch (sd->type)
	{
	case SDL_KEYDOWN:
		ProcessKeyboard(sd, _pKeyBindings, eLvLInputState::isInputDown); break;
	case SDL_KEYUP:
		ProcessKeyboard(sd, _pKeyBindings, eLvLInputState::isInputUp); break;

	}
}

XMINT2 LvLEngineInput::GetMousePosition() const
{
	return XMINT2();
}

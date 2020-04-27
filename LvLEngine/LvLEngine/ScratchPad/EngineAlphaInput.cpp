#include "stdafx.h"
#include "EngineAlphaInput.h"

void EngineAlphaInput::MapButtonKey(const char* name, int count, ...)
{
	//instantiate LvLInputMap and register to keybinding map
	LvLInputMap& map = _pKeyBindings[name] = LvLInputMap();

	va_list list; //for optional muliple params object[]
	va_start(list, count);
	for (int i =0; i<count;i++) 
	{
		int key = va_arg(list, int);
		map.Keys.push_back(key);
	}
	va_end(list);
}

void EngineAlphaInput::Refresh()
{
	//for (LvL_KEYMAP_IT it = _pKeyBindings.begin();it!=_pKeyBindings.end();it++) 
	FOREACH(LvL_KEYMAP_IT, it,_pKeyBindings)
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

bool EngineAlphaInput::GetButtonDown(const char* name)
{
	LvLInputMap& map = _pKeyBindings[name];
	return map.State == eLvLInputState::isInputDown;

}

bool EngineAlphaInput::GetButton(const char* name)
{
	LvLInputMap& map = _pKeyBindings[name];
	return map.State == eLvLInputState::isInputHold;
}

bool EngineAlphaInput::GetButtonUp(const char* name)
{
	LvLInputMap& map = _pKeyBindings[name];
	return map.State == eLvLInputState::isInputUp;
}

int EngineAlphaInput::GetMouseX()
{
	return 0;
}

int EngineAlphaInput::GetMouseY()
{
	return 0;
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
void EngineAlphaInput::ProcessEvent(SDL_Event* sd)
{
	switch (sd->type) 
	{
	case SDL_KEYDOWN:
		ProcessKeyboard(sd, _pKeyBindings, eLvLInputState::isInputDown); break;
	case SDL_KEYUP:
		ProcessKeyboard(sd, _pKeyBindings, eLvLInputState::isInputUp); break;

	}

}

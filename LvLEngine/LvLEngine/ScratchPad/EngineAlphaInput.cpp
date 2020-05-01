#include "stdafx.h"
#include "EngineAlphaInput.h"

EngineAlphaInput::EngineAlphaInput()
{
	 _pKeyBindings["mouse_0"] = LvLInputMap();
	 _pKeyBindings["mouse_1"] = LvLInputMap();
	 _pKeyBindings["mouse_2"] = LvLInputMap();
}

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



void ProcessMouseButton(SDL_Event* sd, LvL_KEYMAP& map, eLvLInputState state) 
{
	int button = sd->button.button;
	switch (button) 
	{
	case SDL_BUTTON_LEFT:
	{
		LvLInputMap& m = map["mouse_0"];
		m.State = state;
		break;
	}
	case SDL_BUTTON_RIGHT:
	{
		LvLInputMap& m = map["mouse_1"];
		m.State = state;
		break;
	}
	case SDL_BUTTON_MIDDLE:
	{
		LvLInputMap& m = map["mouse_2"];
		m.State = state;
		break;
	}
	default:
		break;
	}
}
void ProcessKeyboard(SDL_Event* sd, LvL_KEYMAP& map, eLvLInputState state) 
{
	bool down = state == eLvLInputState::isInputDown;
	int key = sd->key.keysym.sym;
	FOREACH(LvL_KEYMAP_IT, it, map) 
	{
		LvLInputMap& imap = it->second;
		FOREACH(LvL_KEYLIST_IT, kit, imap.Keys) 
		{
			if (key == *kit) 
			{
				if (imap.State == eLvLInputState::isInputHold && down) 
				{
					//nothing
				}
				imap.State = state;
				break;
			}
		}
	}
}
void ProcessMouseMove(SDL_Event* sd, XMINT2& mousepos) 
{
	auto m = sd->motion;
	mousepos.x = m.x;
	mousepos.y = -m.y;
}
void EngineAlphaInput::ProcessEvent(SDL_Event* sd)
{
	switch (sd->type) 
	{
	case SDL_KEYDOWN:
		ProcessKeyboard(sd, _pKeyBindings, eLvLInputState::isInputDown); break;
	case SDL_KEYUP:
		ProcessKeyboard(sd, _pKeyBindings, eLvLInputState::isInputUp); break;
	case SDL_MOUSEBUTTONDOWN:
		ProcessMouseButton(sd, _pKeyBindings, eLvLInputState::isInputDown);
		break;
	case SDL_MOUSEBUTTONUP:
		ProcessMouseButton(sd, _pKeyBindings, eLvLInputState::isInputUp);
		break;
	case SDL_MOUSEMOTION:
		ProcessMouseMove(sd, _mousePosition);
		break;
		

	}

}

XMINT2 EngineAlphaInput::GetMousePosition() const
{
	return _mousePosition;
}

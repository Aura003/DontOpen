#pragma once
#include"LvLBaseDef.h"

enum eLvLInputState
{
	isNothing,
isInputDown,
isInputHold,
isInputUp
};


class iLvLInput 
{
public:
	virtual ~iLvLInput() {};
	virtual void MapButtonKey(const char* name, int count, ...)=0;
	virtual void Refresh() = 0;
	virtual bool GetButtonDown(const char* name) = 0;
	virtual bool GetButton(const char* name) = 0;
	virtual bool GetButtonUp(const char* name) = 0;

	virtual XMINT2 GetMousePosition() const = 0;
protected:
};

#define LvLK_SCANCODE_MASK (1<<30)
#define LvL_SCANCODE_TO_KEYCODE(X)  (X | LvLK_SCANCODE_MASK)

enum eLvLScanCode
{
	scRight = 79,
	scLeft = 80,
	scDown=81,
	scUp=82,
};
enum eLvLKeyCode 
{
	kcArrowRight = LvL_SCANCODE_TO_KEYCODE(scRight),
	kcArrowLeft = LvL_SCANCODE_TO_KEYCODE(scLeft),
	kcArowDown = LvL_SCANCODE_TO_KEYCODE(scDown),
	kcArrowUp = LvL_SCANCODE_TO_KEYCODE(scUp)
};
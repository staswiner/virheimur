#pragma once
#include "Mouse.h"
#include "UserInterface.h"
class Cursor
{
public:
	Cursor();
	~Cursor();
	void Initialize();
	void Draw();
private:
	UIElement* CursorEl;
};


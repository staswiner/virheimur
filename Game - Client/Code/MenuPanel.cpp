#include "MenuPanel.h"



MenuPanel::MenuPanel()
{
}


MenuPanel::~MenuPanel()
{
}

void MenuPanel::Initialize()
{
	iMenuPanel.Initialize("Interface/Menu.png");
}

void MenuPanel::DrawMenuPanel()
{
	Mouse mouse;
	vec2 WindowSize = mouse.GetWindowSize();
	iMenuPanel.Draw(vec2(0, WindowSize.y - 100), vec2(WindowSize.x, WindowSize.y));
}

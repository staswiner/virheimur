#include "Keyboard.h"


list<pair<int, time_t>> staticKeyboard::Commands;
list<pair<int, time_t>> staticKeyboard::Letters;

staticKeyboard::staticKeyboard()
{
	for (int i = 0; i < nKeys; i++)
	{
		keystates[i] = false;
	}

}


staticKeyboard::~staticKeyboard()
{
}

short staticKeyboard::isKeyPressed(VirtualKeys Key) const
{
	return (keystates[Key]);
}

void staticKeyboard::OnKeyPressed(const byte keycode)
{
	/*if (keystates[keycode] == false)
		Commands.push_back(pair<int,time_t>(keycode,time(NULL)));*/
	keystates[keycode] = true;

	while (Commands.size() > 0)
	{
		if (Commands.front().second - time(NULL) > 10) {
			Commands.pop_front();
		}
		else
			break;
	}
	while (Letters.size() > 0)
	{
		if (Letters.front().second - time(NULL) > 10) {
			Letters.pop_front();
		}
		else
			break;
	}
	if (keystates[VK_ESCAPE])
	{	
//		PostMessage(GetWindow(NULL,NULL), WM_CLOSE, 0, 0); // TODO: add hwnd parameter to get that work
	}
}
void staticKeyboard::OnKeyReleased(const byte keycode)
{
	keystates[keycode] = false;
}

/***Keyboard Cover Class***/
staticKeyboard Keyboard::sKeyboard;
Keyboard::Keyboard()
{
}
Keyboard::~Keyboard()
{

}

list<pair<int, time_t>>& Keyboard::getCommands()
{
	return this->sKeyboard.Commands;
}

list<pair<int, time_t>>& Keyboard::getLetters()
{
	return this->sKeyboard.Letters;
}

void Keyboard::PushBackCommand(short wParam)
{
	sKeyboard.Commands.push_back(pair<int, time_t>(wParam, time(NULL)));
}

void Keyboard::PushBackLetter(short wParam)
{
	sKeyboard.Letters.push_back(pair<int, time_t>(wParam, time(NULL)));
}

short Keyboard::isKeyPressed(VirtualKeys Key) const
{
	return sKeyboard.isKeyPressed(Key);
}
void Keyboard::OnKeyPressed(const byte keycode)
{
	sKeyboard.OnKeyPressed(keycode);
}
void Keyboard::OnKeyReleased(const byte keycode)
{
	sKeyboard.OnKeyReleased(keycode);
}

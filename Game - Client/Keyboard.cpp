#include "Keyboard.h"



Keyboard::Keyboard()
{
	for (int i = 0; i < nKeys; i++)
	{
		keystates[i] = false;
	}

}


Keyboard::~Keyboard()
{
}

short Keyboard::isKeyPressed(Key Key) const
{
	return (keystates[static_cast<char>(Key)]);
}

void Keyboard::OnKeyPressed(const byte keycode)
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
void Keyboard::OnKeyReleased(const byte keycode)
{
	keystates[keycode] = false;
}



list<pair<int, time_t>>& Keyboard::getCommands()
{
	return this->Commands;
}

list<pair<int, time_t>>& Keyboard::getLetters()
{
	return this->Letters;
}

void Keyboard::PushBackCommand(short wParam)
{
	this->Commands.push_back(pair<int, time_t>(wParam, time(NULL)));
}

void Keyboard::PushBackLetter(short wParam)
{
	this->Letters.push_back(pair<int, time_t>(wParam, time(NULL)));
}

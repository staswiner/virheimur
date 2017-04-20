#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <Windows.h>
#include <list>
#include <utility>
#include <time.h>
using namespace std;
typedef unsigned char byte;
enum class Key
{
	A = 0x41,
	B,
	C,
	D,
	E,
	F,
	G,
	H,
	I,
	J,
	K,
	L,
	M,
	N,
	O,
	P,
	Q,
	R,
	S,
	T,
	U,
	V,
	W,
	X,
	Y,
	Z,
	Down = VK_DOWN,
	Up = VK_UP,
	Right = VK_RIGHT,
	Left = VK_LEFT,
	Esc = VK_ESCAPE,
	Space = VK_SPACE,
	Enter = VK_RETURN,
	Alt = VK_MENU,
	Tab = VK_TAB,
	Backspace = VK_BACK,
	Shift = VK_SHIFT
};

class Keyboard
{
private:
	static Keyboard instance;
	Keyboard();
	Keyboard(Keyboard&) = delete;
	Keyboard& operator=(Keyboard const & rhs) = delete;

	static const int nKeys = 256;
	bool keystates[nKeys];
public:
	static Keyboard& Instance()
	{
		static Keyboard instance;
		return instance;
	}
	~Keyboard();
	short isKeyPressed(Key) const;
	void OnKeyPressed(const byte);
	void OnKeyReleased(const byte);
	list<pair<int, time_t>>& getCommands();
	list<pair<int, time_t>>& getLetters();
	void PushBackCommand(short wParam);
	void PushBackLetter(short wParam);
	list<pair<int, time_t>> Commands;
	list<pair<int, time_t>> Letters;

};

#pragma once
#include <Windows.h>
#include <list>
#include <utility>
#include <time.h>
using namespace std;
typedef unsigned char byte;
enum VirtualKeys
{
	A_Key = 0x41,
	B_Key,
	C_Key,
	D_Key,
	E_Key,
	F_Key,
	G_Key,
	H_Key,
	I_Key,
	J_Key,
	K_Key,
	L_Key,
	M_Key,
	N_Key,
	O_Key,
	P_Key,
	Q_Key,
	R_Key,
	S_Key,
	T_Key,
	U_Key,
	V_Key,
	W_Key,
	X_Key,
	Y_Key,
	Z_Key,
	DOWN = VK_DOWN,
	UP = VK_UP,
	RIGHT = VK_RIGHT,
	LEFT = VK_LEFT,
	ESC = VK_ESCAPE,
	SPACE = VK_SPACE,
	ENTER = VK_RETURN,
	ALT = VK_MENU,
	TAB = VK_TAB,
	BACKSPACE = VK_BACK,
	SHIFT = VK_SHIFT
};

class staticKeyboard
{
private:
	static const int nKeys = 256;
	bool keystates[nKeys];
public:
	staticKeyboard();
	~staticKeyboard();

	short isKeyPressed(VirtualKeys) const;
	void OnKeyPressed(const byte);
	void OnKeyReleased(const byte);
	static list<pair<int, time_t>> Commands;
	static list<pair<int, time_t>> Letters;

};
class Keyboard
{
private:
	static staticKeyboard sKeyboard;
public:
	Keyboard();
	~Keyboard();

	list<pair<int, time_t>>& getCommands();
	list<pair<int, time_t>>& getLetters();
	void PushBackCommand(short wParam);
	void PushBackLetter(short wParam);
	short isKeyPressed(VirtualKeys) const;
	void OnKeyPressed(const byte);
	void OnKeyReleased(const byte);

};

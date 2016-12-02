#pragma once
#include <string>
#include <iostream>
#include "Client.h"
#include "Login_Screen_Graphics.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "Text.h"
#include <future>

using namespace std;
class Login_Screen
{
public:
	Login_Screen();
	~Login_Screen();
	void ConnectToServer();
	void LoopScreen();
	void CheckUsernamePasswordMatch();
	void CreateAccount();
	static HDC m_HDC;
	typedef void (*KeyboardInput)(Login_Screen*, char);
private:
	string Username;
	string Password;
	string mField[2];
	Client mClient;
	bool KeyIsPressed[255];

	
	Mouse mouse;
	Keyboard keyboard;
	Login_Screen_Graphics mLogin_Screen_Graphics;

	bool isTabPressed = false;
	
	int mCurrentSelection = 0;

	void SetPassword();
	void SetUsername();

	void Draw();
public:
	KeyboardInput kbInput[256];

	static void pressed_space(Login_Screen* a_ls, char);
	static void pressed_enter(Login_Screen* a_ls, char);
	static void pressed_tab(Login_Screen* a_ls, char);

	static void pressed_backspace(Login_Screen* a_ls, char);
	static void pressed_key(Login_Screen* a_ls, char key);
	static void pressed_shiftkey(char key);

	static void pressed_default(Login_Screen* a_ls, char key);
};


#pragma once
#include "ImageLoader.h"
#include "UserInterface.h"
#include "Text.h"
#include "Keyboard.h"
#include "GameLogic.h"
class LoginState
{
public:
	LoginState();
	~LoginState();
	void Initialize();
	void Input();
	void Draw(HDC hdc);
	void PerformLogin();
private:
	UIElement* GenerateForm();
	string Username;
	string Password;
	UserInterface UI;
	HDC m_hdc;
};


#pragma once
#include "ImageLoader.h"
#include "UserInterface.h"
#include "Text.h"
#include "Keyboard.h"
#include "GameLogic.h"
#include "TCP.h"
#include "Session.h"
class LoginState
{
public:
	LoginState();
	~LoginState();
	void Initialize(char* State);
	void Input();
	void Draw(HDC hdc);

	void PerformLogin();
private:
	UIElement* GenerateForm();
	UserInterface UI;
	HDC m_hdc;
	char* GameState;

};


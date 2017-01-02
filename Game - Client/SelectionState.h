#pragma once
#include "ImageLoader.h"
#include "UserInterface.h"
#include "Text.h"
#include "Keyboard.h"
#include "GameLogic.h"
using namespace glm;
class SelectionState
{
public:
	SelectionState();
	~SelectionState();
	void Initialize();
	void Input();
	void Draw(HDC hdc);
	void Draw3D();
	void PerformLogin();
private:
	UIElement* GenerateForm();
	string Username;
	string Password;
	UserInterface UI;
	HDC m_hdc;
	vec2 LeftBot;
	vec2 RightTop;
};


#pragma once
#include "ImageLoader.h"
#include "UserInterface.h"
#include "Text.h"
#include "Keyboard.h"
#include "GameLogic.h"
#include "MultiSampleFBO.h"
#include "FBO.h"
class CharacterCreationState
{
public:
	CharacterCreationState();
	~CharacterCreationState();
	void Initialize(char* State);
	void Input();
	void Draw(HDC hdc);
	void Draw3D();
	void PerformLogin();
	void CreateNewCharacter();
private:
	UIElement* GenerateForm();
	string Username;
	string Password;
	UserInterface UI;
	HDC m_hdc;
	vec2 LeftBot;
	vec2 RightTop;
	MultiSampleFBO mAntiAliasing;
	char* GameState;
};


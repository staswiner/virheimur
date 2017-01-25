#pragma once
#include "ImageLoader.h"
#include "UserInterface.h"
#include "Text.h"
#include "Keyboard.h"
#include "GameLogic.h"
#include "MultiSampleFBO.h"
#include "FBO.h"
#include "TCP.h"
#include "json.hpp"
#include "Session.h"
class CharacterCreationState
{
public:
	CharacterCreationState();
	~CharacterCreationState();
	void Initialize(char* State);
	void Input();
	void Draw(HDC hdc);
	void Draw3D();
	void CreateNewCharacter();
	void GoBackToSelectionPage();
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


#pragma once
#include "ImageLoader.h"
#include "UserInterface.h"
#include "Text.h"
#include "Keyboard.h"
#include "GameLogic.h"
#include "MultiSampleFBO.h"
#include "FBO.h"
#include "TCP.h"
#include "Session.h"
using namespace glm;
class SelectionState
{
public:
	SelectionState();
	~SelectionState();
	void Initialize(char* State);
	void Input();
	void Draw(HDC hdc);
	void Draw3D();
	void PerformLogin();
	void CreateNewCharacter();
	void ChangeCharacter(bool direction);
	void Reload();
private:
	UIElement* GenerateForm();
	UserInterface UI;
	HDC m_hdc;
	vec2 LeftBot;
	vec2 RightTop;
	MultiSampleFBO mAntiAliasing;
	vector<Player*> Characters;
	vector<Player*>::iterator SelectedPlayer;
	char* GameState;
};


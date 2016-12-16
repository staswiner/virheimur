#pragma once
#include "Keyboard.h"
#include "Mouse.h"
#include "Text.h"
#include "UIElement.h"
#include "UIWindow.h"
#include <map>
#include <utility>
#include "ChampionChat.h"
#include "Minimap.h"
#include "MenuPanel.h"
#include "StatsWindow.h"
#include "MasteryWindow.h"
using namespace std;
class UserInterface
{
	struct tempW;
public:
	UserInterface();
	~UserInterface();
	void GenerateForm(); 
	void AcceptInput();
	void CleanWindows();
	void FocusControl();
	void LeftClick();
	map<GLchar,GLuint> Inputs;
	//vector<pair<unique_ptr<ChampionChat>, GLuint>> tempWindows;
	vector<tempW> tempWindows;
	vector<UIWindow> vUIWindows;
	UIElement* root;

	string Chat;	
	UIElement* Focused;
	UIElement* Pressed;
	list<GLchar> InWorldCommands;
private:
	Keyboard keyboard;
	Mouse mouse;
	struct tempW
	{
		unique_ptr<ChampionChat> first;
		time_t second;
	};
	Minimap minimap;
	MenuPanel menuPanel;
	StatsWindow statsWindow;
	MasteryWindow masteryWindow;
	void OpenStatWindow();
	bool StatWindowOpen = true;;

};


#pragma once
#include "Keyboard.h"
#include "Mouse.h"
#include "Text.h"
#include "UIElement.h"
#include <map>
#include <utility>
#include "ChampionChat.h"
#include "Minimap.h"
#include "MenuPanel.h"
#include "StatsWindow.h"
using namespace std;
class UserInterface
{
	struct tempW;
public:
	UserInterface();
	~UserInterface();
	void GenerateForm(); 
	void GenerateForm(UIElement* root);
	void GenerateLoginForm();
	void AcceptInput();
	char AccessWorldCommands();
	void CleanWindows();
	void FocusControl();
	bool LeftClick();
	void LeftPress();
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
	struct tempW
	{
		unique_ptr<ChampionChat> first;
		time_t second;
	};
	Minimap minimap;
	MenuPanel menuPanel;
	StatsWindow statsWindow;
	void FocusNext();
	void OpenStatWindow();
	bool StatWindowOpen = true;;

};


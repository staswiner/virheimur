#pragma once
#include "Keyboard.h"
#include "Mouse.h"
#include "Text.h"
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
	void AcceptInput();
	void CleanWindows();
	void FocusControl();
	map<GLchar,GLuint> Inputs;
	//vector<pair<unique_ptr<ChampionChat>, GLuint>> tempWindows;
	vector<tempW> tempWindows;
	vector<UIWindow> vUIWindows;
	string Chat;
	GLuint Focus;
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
};


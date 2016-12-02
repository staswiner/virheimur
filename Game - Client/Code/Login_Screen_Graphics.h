#pragma once
#include "Graphics_Header.h"
#include "ImageLoader.h"
#include "Textbox.h"
#include "Button.h"
class Login_Screen_Graphics
{
public:
	Login_Screen_Graphics();
	~Login_Screen_Graphics();
	void Initialize();
	void DrawDisconnectedLoginScreen();
	void DrawConnectedLoginScreen(int Selection, string mField[2]);
	void SelectTextBox(Textbox*);
	enum e_Selection{ b_Username = 1, b_Password };
public:
	Textbox* tb_Username;
	Textbox* tb_Password;
	Button* b_TryLogin;
	vector<Textbox*> textBoxes;
	Textbox* SelectedTextBox;
};


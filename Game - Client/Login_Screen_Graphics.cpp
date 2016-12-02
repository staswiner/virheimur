#include "Login_Screen_Graphics.h"



Login_Screen_Graphics::Login_Screen_Graphics()
{
}


Login_Screen_Graphics::~Login_Screen_Graphics()
{
}

void Login_Screen_Graphics::Initialize()
{
	tb_Username = new Textbox(vec2(200,100), vec2(400,150),b_Username, 10);
	tb_Password = new Textbox(vec2(200,175), vec2(400,225),b_Password, 10);
	b_TryLogin = new Button(vec2(450, 150), vec2(650, 200), 3, "Log-in");
	tb_Username->Initialize();
	tb_Password->Initialize();
	b_TryLogin->Initialize();
	textBoxes.push_back(new EmptyTextbox(vec2(),vec2(),0,0));
	textBoxes.push_back(tb_Username);
	textBoxes.push_back(tb_Password);
	SelectedTextBox = NULL;
}

void Login_Screen_Graphics::DrawDisconnectedLoginScreen()
{
}

void Login_Screen_Graphics::DrawConnectedLoginScreen(int Selection, string mField[2])
{
	for each (Textbox* tb in this->textBoxes)
	{
		tb->Draw();
	}
	b_TryLogin->Draw();
	
}

void Login_Screen_Graphics::SelectTextBox(Textbox * a_Tb)
{
	this->SelectedTextBox = a_Tb;
}

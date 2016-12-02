#include "LoginState.h"



LoginState::LoginState()
{
}


LoginState::~LoginState()
{
}

void LoginState::Initialize()
{
	sex=UsernameTextbox.LoadTexture("Interface/Textbox.png");
	UsernameTextbox.LoadVAO();
	PasswordTextbox.LoadTexture("Interface/Textbox.png");
	PasswordTextbox.LoadVAO();
}

void LoginState::Draw()
{
	Mouse mouse;
	vec2 Center(mouse.GetWindowSize().x / 2, mouse.GetWindowSize().y / 2);
	UsernameTextbox.Draw(vec2(Center.x - 100,Center.y - 125), vec2(Center.x + 100, Center.y - 75));
}

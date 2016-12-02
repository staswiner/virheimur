#pragma once
#include "ImageLoader.h"
#include "Text.h"
#include "Keyboard.h"
#include "GameLogic.h"
class LoginState
{
public:
	LoginState();
	~LoginState();
	void Initialize();

	void Draw();
private:
	string Username;
	string Password;
	ImageLoader UsernameTextbox;
	ImageLoader PasswordTextbox;
	GLuint sex;
};


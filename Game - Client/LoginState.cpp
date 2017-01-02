#include "LoginState.h"



LoginState::LoginState()
{
}


LoginState::~LoginState()
{
}

void LoginState::Initialize()
{
	UI.GenerateForm(this->GenerateForm());
}

void LoginState::Input()
{
#define is ==

	using namespace Stas;
	Mouse mouse;
	static bool LeftIsPressed = false;
	if (mouse.LeftIsPressed())
	{
		LeftIsPressed = true;
		UI.LeftPress();
	}
	// on left release
	if (!mouse.LeftIsPressed() and LeftIsPressed is true)
	{
		LeftIsPressed = false;
		UI.LeftClick();
	}
	UI.FocusControl();
	UI.AcceptInput();
#undef is
}

void LoginState::Draw(HDC hdc)
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glClearColor(255, 255, 255, 255);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);
	glDepthMask(GL_TRUE);

	UI.root->Draw();

	glFlush();
	SwapBuffers(hdc);
}

void LoginState::PerformLogin()
{
	int i = 0;
}

UIElement* LoginState::GenerateForm()
{
	vec2 Position;
	UIElement* root = new UIElement("Root", "");

	UIElement* UsernameElement = new UIElement("Username", "Interface/Textbox.png");
	Position = vec2(10, 80);
	UsernameElement->TopLeft = Position;
	UsernameElement->SetByTrueSize(Position);
	UsernameElement->AddHoverEvent([]
	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/TextboxHovered.png"); });
	UsernameElement->AddHoverDoneEvent([]
	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/Textbox.png"); });
	UsernameElement->AddReturnDefaultEvent([]
	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/Textbox.png"); });
	UsernameElement->AddClickEvent([]
	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/TextboxSelected.png"); });
	root->AppendChild(UsernameElement);

	UIElement* PasswordElement = new UIElement("Password", "Interface/Textbox.png");
	Position = vec2(10, 180);
	PasswordElement->TopLeft = Position;
	PasswordElement->SetByTrueSize(Position);
	PasswordElement->AddHoverEvent([]
	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/TextboxHovered.png"); });
	PasswordElement->AddHoverDoneEvent([]
	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/Textbox.png"); });
	PasswordElement->AddReturnDefaultEvent([]
	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/Textbox.png"); });
	PasswordElement->AddClickEvent([]
	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/TextboxSelected.png"); });
	root->AppendChild(PasswordElement);

	UIElement* LogInElement = new UIElement("LoginButton", "Interface/Button1.png");
	Position = vec2(230, 180);
	LogInElement->TopLeft = Position;
	LogInElement->SetByTrueSize(Position);
	LogInElement->AddHoverEvent([]
	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/Button1Hovered.png"); });
	LogInElement->AddHoverDoneEvent([]
	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/Button1.png"); });
	LogInElement->AddReturnDefaultEvent([]
	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/Button1.png"); });
	LogInElement->AddClickEvent([&]
	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/Button1Selected.png"); this->PerformLogin(); });
	LogInElement->AddPressEvent([]
	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/Button1Pressed.png"); });
	root->AppendChild(LogInElement);
	return root;
}

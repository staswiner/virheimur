#include "LoginState.h"



LoginState::LoginState()
{
	this->SaveUsername = false;
}


LoginState::~LoginState()
{
}

void LoginState::Initialize(char* State)
{
	UI.GenerateForm(this->GenerateForm());
	this->GameState = State;
	this->UI.root->GetUIElement("Username")->innerText = Cookies::GetInstance().GetCookie("Username");
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
	UI.AcceptInput();
	UI.FocusControl();
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
	TCP tcp;
	string username = this->UI.root->GetUIElement("Username")->innerText;
	string password = this->UI.root->GetUIElement("Password")->innerText;
	/// Set Username Cookie
	if (this->SaveUsername == true)
	{
		Cookies::GetInstance().SetCookie("Username", username);
	}

	/// add support when i get home & get a tcp server working
	tcp.SendPacket("Authentication "+username+" "+password+" <EOF>");
	string output = tcp.ReceivePacketsAsync();	
#define is ==
//#define then {
//#define end }
//#define else }else
	if (output is "valid")
	{
		Session& session = Session::GetInstance();
		session.Username = username;
		*this->GameState = 1;
	}
	else if (output is "Invalid")
	{
		this->UI.root->GetUIElement("Invalid")->Show();
	}
}

UIElement* LoginState::GenerateForm()
{
	// UI can do few things : change itself, send request to server, change some flag, activate function
	vec2 Position;
	UIElement* root = new UIElement("Root", "");

	UIElement* UsernameElement = new UIElement("Username", "Interface/Textbox.png");
	Position = vec2(10, 80);
	UsernameElement->innerText = "";
	UsernameElement->TopLeft = Position;
	UsernameElement->SetByTrueSize(Position);
	UsernameElement->writable = true;
	UsernameElement->AddHoverEvent([]
	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/TextboxHovered.png"); });
	UsernameElement->AddHoverDoneEvent([]
	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/Textbox.png"); });
	UsernameElement->AddReturnDefaultEvent([]
	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/Textbox.png"); });
	UsernameElement->AddClickEvent([]
	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/TextboxSelected.png"); });
	root->AppendChild(UsernameElement);

	UIElement* Element = new UIElement("UsernameSaveCheckbox", "Interface/Textbox.png");
	Position = vec2(210, 80);
	Element->TopLeft = Position;
	Element->BotRight = Position + vec2(50,50);
	Element->AddHoverEvent([]
	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/TextboxHovered.png"); });
	Element->AddHoverDoneEvent([]
	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/Textbox.png"); });
	Element->AddReturnDefaultEvent([]
	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/Textbox.png"); });
	Element->AddClickEvent([&]
	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/TextboxSelected.png"); this->SaveUsername = true; });
	root->AppendChild(Element);

	UIElement* PasswordElement = new UIElement("Password", "Interface/Textbox.png");
	Position = vec2(10, 180);
	PasswordElement->innerText = "ilovemyreann<3";
	PasswordElement->TopLeft = Position;
	PasswordElement->style.MaskedText = true;
	PasswordElement->writable = true;
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

	LogInElement = new UIElement("Invalid", "Interface/Button1.png");
	Position = vec2(30, 30);
	LogInElement->TopLeft = Position;
	LogInElement->BotRight = vec2(300,50);
	LogInElement->Hide();
	LogInElement->style.font.size = 15.0f;
	LogInElement->style.font.color = vec3(1,0.2,0.2);

	LogInElement->innerText = "Username or Password invalid";
	LogInElement->AddHoverEvent([]
	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/Button1Hovered.png"); });
	LogInElement->AddHoverDoneEvent([]
	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/Button1.png"); });
	LogInElement->AddReturnDefaultEvent([]
	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/Button1.png"); });
	root->AppendChild(LogInElement);

	return root;
}

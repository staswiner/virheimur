#include "LoginState.h"



LoginState::LoginState()
{
}


LoginState::~LoginState()
{
}

void LoginState::Initialize(char* State)
{
	UI.GenerateForm(this->GenerateForm());
	this->GameState = State;
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
	TCP tcp;
	string username = this->UI.root->GetUIElement("Username")->innerText;
	string password = this->UI.root->GetUIElement("Password")->innerText;
	/// add support when i get home & get a tcp server working
	/*tcp.SendPacket("");
	string output = tcp.ReceivePacketsAsync();*/
	string output = "Test";// default for tests
#define is ==
//#define then {
//#define end }
//#define else }else
	if (output is "valid")
	{
		Session& session = Session::GetInstance();
		session.Username = username;
		session.UserID = stoi(output);
		*this->GameState = 1;
	}
	else if (output is "Invalid")
	{
		this->UI.root->GetUIElement("Invalid")->Show();
	}
	else if (output is "Test")
	{
		*this->GameState = 1;
	}
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

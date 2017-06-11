#include "CharacterCreationState.h"



CharacterCreationState::CharacterCreationState()
{
}


CharacterCreationState::~CharacterCreationState()
{
}

void CharacterCreationState::Initialize(char * State)
{
	this->GameState = State;
	UI.root = GenerateForm();
}

void CharacterCreationState::Input()
{
#define is ==

	using namespace Stas;
	Mouse& mouse = Mouse::Instanace();

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

void CharacterCreationState::Draw(HDC hdc)
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glClearColor(0, 255, 255, 255);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);
	glDepthMask(GL_TRUE);

	Mouse& mouse = Mouse::Instanace();

	glViewport(0, 0, (int)mouse.GetWindowSize().x, (int)mouse.GetWindowSize().y);



	FBO::UnbindFrameBuffer();
	mAntiAliasing.BindFrameBuffer();
	UI.root->Draw();
	Draw3D();
	mAntiAliasing.CopyBuffer(0);
	FBO::UnbindFrameBuffer();


	glFlush();
	SwapBuffers(hdc);
}

void CharacterCreationState::Draw3D()
{
}


void CharacterCreationState::CreateNewCharacter()
{
	TCP tcp;
	string CharacterName = this->UI.root->GetUIElement("CharacterName")->innerText;
	string Username = Session::Instance().Username;
	json jCharacter;
	jCharacter["Username"] = Username;
	jCharacter["CharacterName"] = CharacterName;
	//tcp.SendPacket(jCharacter.dump());
	string Content = "CreateCharacter " + Username + " " + CharacterName + "<EOF>";
	tcp.SendPacket(Content);
	string ReceiveContent = tcp.ReceivePacketsAsync();
	if (ReceiveContent == "Character Name Taken")
	{

	}
	else if (ReceiveContent == "Created")
	{
		*this->GameState = 1;
	}
}
void CharacterCreationState::GoBackToSelectionPage()
{
	*this->GameState = 1;
}
UIElement * CharacterCreationState::GenerateForm()
{
//	vec2 Position;
//	UIElement* root = new UIElement("Root", "");
//	UIElement* Element;
//	UIElement* CreateButton = new UIElement("CreateCharacterButton", "Interface/Button1.png");
//	Position = vec2(200, 200);
//	CreateButton->Top = Position.y;
//	CreateButton->Left = Position.x;
//	CreateButton->SetByTrueSize(Position);
//	CreateButton->innerText = "Create";
//	CreateButton->AddHoverEvent([]
//	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/Button1Hovered.png"); });
//	CreateButton->AddHoverDoneEvent([]
//	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/Button1.png"); });
//	CreateButton->AddReturnDefaultEvent([]
//	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/Button1.png"); });
//	CreateButton->AddClickEvent([&]
//	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/Button1Selected.png"); this->CreateNewCharacter(); });
//	CreateButton->AddPressEvent([]
//	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/Button1Pressed.png"); });
//	root->AppendChild(CreateButton);
//
//	Element = new UIElement("Back", "Interface/Button1.png");
//	Position = vec2(310, 200);
//	Element->Top = Position.y;
//	Element->Left = Position.x;
//	Element->SetByTrueSize(Position);
//	Element->innerText = "Back";
//	Element->AddHoverEvent([]
//	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/Button1Hovered.png"); });
//	Element->AddHoverDoneEvent([]
//	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/Button1.png"); });
//	Element->AddReturnDefaultEvent([]
//	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/Button1.png"); });
//	Element->AddClickEvent([&]
//	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/Button1Selected.png"); this->GoBackToSelectionPage(); });
//	Element->AddPressEvent([]
//	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/Button1Pressed.png"); });
//	root->AppendChild(Element);
//
//	Element = new UIElement("CharacterName", "Interface/Textbox.png");
//	Position = vec2(10, 80);
//	Element->innerText = "Came2fame";
//	Element->Top = Position.y;
//	Element->Left = Position.x;
//	Element->SetByTrueSize(Position);
//	Element->AddHoverEvent([]
//	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/TextboxHovered.png"); });
//	Element->AddHoverDoneEvent([]
//	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/Textbox.png"); });
//	Element->AddReturnDefaultEvent([]
//	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/Textbox.png"); });
//	Element->AddClickEvent([]
//	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/TextboxSelected.png"); });
//	root->AppendChild(Element);
//
//	return root;
	return nullptr;
}

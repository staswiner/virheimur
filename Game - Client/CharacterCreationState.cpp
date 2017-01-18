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
}

void CharacterCreationState::Draw(HDC hdc)
{
}

void CharacterCreationState::Draw3D()
{
}


void CharacterCreationState::CreateNewCharacter()
{
	TCP tcp;
	string CharacterName = "Came2fame";
	string Username = Session::GetInstance().Username;
	json jCharacter;
	jCharacter["Username"] = Username;
	jCharacter["CharacterName"] = CharacterName;
	tcp.SendPacket(jCharacter.dump());

	*this->GameState = 2;
}

UIElement * CharacterCreationState::GenerateForm()
{
	vec2 Position;
	UIElement* root = new UIElement("Root", "");

	UIElement* CreateButton = new UIElement("CreateCharacterButton", "Interface/Button1.png");
	Position = vec2(200, 200);
	CreateButton->TopLeft = Position;
	CreateButton->SetByTrueSize(Position);
	CreateButton->innerText = "Create";
	CreateButton->AddHoverEvent([]
	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/Button1Hovered.png"); });
	CreateButton->AddHoverDoneEvent([]
	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/Button1.png"); });
	CreateButton->AddReturnDefaultEvent([]
	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/Button1.png"); });
	CreateButton->AddClickEvent([&]
	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/Button1Selected.png"); this->CreateNewCharacter(); });
	CreateButton->AddClickEvent([]
	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/Button1Pressed.png"); });
	root->AppendChild(CreateButton);

	return root;
}

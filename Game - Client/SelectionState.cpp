#include "SelectionState.h"



SelectionState::SelectionState()
{


}


SelectionState::~SelectionState()
{
}

void SelectionState::Initialize(char* State)
{

	// test purposes
	Characters.push_back(new Player());
	Characters.push_back(new Player());
	Characters[0]->stats.Exp = 100;
	Characters[0]->CharacterName = "Nightblue3";
	Characters[1]->stats.Exp = 250;
	Characters[1]->CharacterName = "Nightblue4";
	SelectedPlayer = Characters.begin();

	// not test
	UI.GenerateForm(this->GenerateForm());
	mAntiAliasing.InitializeMultiSample();
	this->GameState = State;


}

void SelectionState::Input()
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

void SelectionState::Draw(HDC hdc)
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glClearColor(0, 255, 255, 255);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);
	glDepthMask(GL_TRUE);

	Mouse mouse;
	glViewport(0,0, mouse.GetWindowSize().x, mouse.GetWindowSize().y);
	

	
	FBO::UnbindFrameBuffer();
	mAntiAliasing.BindFrameBuffer();
	UI.root->Draw();
	Draw3D();
	mAntiAliasing.CopyBuffer(0);
	FBO::UnbindFrameBuffer();
	//glViewport(0, 0, 50, 50);
	//Draw3D();
	//glViewport(50, 50, 100, 100);
	//Draw3D();

	glFlush();
	SwapBuffers(hdc);
}

void SelectionState::Draw3D()
{
	Mouse mouse;
	LeftBot = vec2(200, mouse.GetWindowSize().y - 500);
	RightTop = vec2(300, 300);
	glViewport(LeftBot.x, LeftBot.y, RightTop.x, RightTop.y);
	vec3 CameraPos(0,20,30);
	vec3 NewLightPos(-20,30,30);
	mat4 ProjectionMatrix = glm::perspective(radians(45.0f),
		float(RightTop.x / RightTop.y), 1.0f, 1000.0f);
	mat4 ViewMatrix = rotate(mat4(), radians(30.0f), vec3(1, 0, 0));
	ViewMatrix = translate(ViewMatrix, -CameraPos);
	long long time = (chrono::duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count()/10 )% 360;
	float Time = radians(
		fmod((float)time,360.0f)
	);
	mat4 ModelMatrix = rotate(mat4(), 
		Time
		, vec3(0,1,0));
	mat4 WVM = ProjectionMatrix * ViewMatrix * ModelMatrix;
	Loaded_Models loaded_Models;
	ShaderBuilder::LoadShader(Shader::At("Animation"))->
		Add_mat4("WVM", WVM).
		Add_mat4("Model", ModelMatrix).
		Add_bool("isAnimated", true).
		Add_float("Texelation", 10.0f).
		Add_vec3("lightPos", NewLightPos).
		Add_vec3("cameraPos", -CameraPos).
		Add_Material("Wood", Materials::GetInstance()["chrome"]).
		Add_textures(loaded_Models["Collada"]->Textures);
	loaded_Models["Collada"]->Draw();

}

void SelectionState::PerformLogin()
{
	*this->GameState = 2;
}

void SelectionState::CreateNewCharacter()
{

}

void SelectionState::ChangeCharacter(bool direction)
{
	// right is true
	if (direction)
	{
		if ((SelectedPlayer+1)!=Characters.end())
		SelectedPlayer++;
	}
	// left is false
	else
	{
		if (SelectedPlayer != Characters.begin())
		SelectedPlayer--;
	}
	this->UI.root->GetUIElement("Exp")->innerText = "Exp: " + to_string((*SelectedPlayer)->stats.Exp);
	this->UI.root->GetUIElement("Name")->innerText = "Name: " + (*SelectedPlayer)->CharacterName;
}

UIElement * SelectionState::GenerateForm()
{

	vec2 Position;
	UIElement* root = new UIElement("Root", "");

	UIElement* CharacterFrameElement = new UIElement("CharacterFrame", "Minimap/Minimap.png");
	Position = vec2(200, 200);
	CharacterFrameElement->TopLeft = Position;
	CharacterFrameElement->SetByTrueSize(Position);
	CharacterFrameElement->AddHoverEvent([]
	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/TextboxHovered.png"); });
	CharacterFrameElement->AddHoverDoneEvent([]
	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/Textbox.png"); });
	CharacterFrameElement->AddReturnDefaultEvent([]
	(UIElement* Element)mutable-> void { Element->ChangePicture("Minimap/Minimap.png"); });
	CharacterFrameElement->AddClickEvent([]
	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/TextboxSelected.png"); });
	root->AppendChild(CharacterFrameElement);

	UIElement* SelectCharacterElement = new UIElement("SelectCharacter", "Interface/Button1.png");
	Position = vec2(520, 200);
	SelectCharacterElement->innerText = "Get Online";
	SelectCharacterElement->TopLeft = Position;
	SelectCharacterElement->BotRight = Position + vec2(250, 50);
	SelectCharacterElement->AddHoverEvent([]
	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/Button1Hovered.png"); });
	SelectCharacterElement->AddHoverDoneEvent([]
	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/Button1.png"); });
	SelectCharacterElement->AddReturnDefaultEvent([]
	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/Button1.png"); });
	SelectCharacterElement->AddClickEvent([&]
	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/Button1Selected.png"); this->PerformLogin(); });
	SelectCharacterElement->AddPressEvent([]
	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/Button1Pressed.png"); });
	root->AppendChild(SelectCharacterElement);

	UIElement* CreateNewCharacterElement = new UIElement("CreateNewCharacter", "Interface/Button1.png");
	Position = vec2(520, 260);
	CreateNewCharacterElement->innerText = "Create New Character";
	CreateNewCharacterElement->TopLeft = Position;
	CreateNewCharacterElement->BotRight = Position + vec2(250,50);
	CreateNewCharacterElement->AddHoverEvent([]
	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/Button1Hovered.png"); });
	CreateNewCharacterElement->AddHoverDoneEvent([]
	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/Button1.png"); });
	CreateNewCharacterElement->AddReturnDefaultEvent([]
	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/Button1.png"); });
	CreateNewCharacterElement->AddClickEvent([&]
	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/Button1Selected.png"); this->CreateNewCharacter(); });
	CreateNewCharacterElement->AddPressEvent([]
	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/Button1Pressed.png"); });
	root->AppendChild(CreateNewCharacterElement);

	UIElement* button = new UIElement("Right", "Interface/RightButton.png");
	Position = vec2(450, 300);
	button->TopLeft = Position;
	button->SetByTrueSize(Position);
	button->AddHoverEvent([]
	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/RightButtonHovered.png"); });
	button->AddHoverDoneEvent([]
	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/RightButton.png"); });
	button->AddReturnDefaultEvent([]
	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/RightButton.png"); });
	button->AddClickEvent([&]
	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/RightButton.png"); this->ChangeCharacter(true); });
	button->AddPressEvent([]
	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/RightButtonPressed.png"); });
	root->GetUIElement("CharacterFrame")->AppendChild(button);

	button = new UIElement("Left", "Interface/LeftButton.png");
	Position = vec2(200, 300);
	button->TopLeft = Position;
	button->SetByTrueSize(Position);
	button->AddHoverEvent([]
	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/LeftButtonHovered.png"); });
	button->AddHoverDoneEvent([]										  
	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/LeftButton.png"); });
	button->AddReturnDefaultEvent([]									   
	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/LeftButton.png"); });
	button->AddClickEvent([&]											   
	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/LeftButton.png"); this->ChangeCharacter(false); });
	button->AddPressEvent([]											   
	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/LeftButtonPressed.png"); });
	root->GetUIElement("CharacterFrame")->AppendChild(button);

	//button = new UIElement("Name", "Interface/LeftButton.png");
	//Position = vec2(175, 300);
	//button->TopLeft = Position;
	//button->SetByTrueSize(Position);
	//button->innerText = "Name";
	//button->AddHoverEvent([]
	//(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/LeftButtonHovered.png"); });
	//button->AddHoverDoneEvent([]
	//(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/LeftButton.png"); });
	//button->AddReturnDefaultEvent([]
	//(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/LeftButton.png"); });
	//button->AddClickEvent([&]
	//(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/LeftButton.png"); this->ChangeCharacter(false); });
	//button->AddPressEvent([]
	//(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/LeftButtonPressed.png"); });
	//root->GetUIElement("CharacterFrame")->AppendChild(button);
	// Stats
	UIElement* Stat = new UIElement("Exp", "Interface/Button1.png");
	Position = vec2(550, 350);
	Stat->TopLeft = Position;
	Stat->BotRight = Position + vec2(200,50);
	Stat->innerText = "Exp: " + to_string((*SelectedPlayer)->stats.Exp);
	root->AppendChild(Stat);

	Stat = new UIElement("Name", "Interface/Button1.png");
	Position = vec2(250, 230);
	Stat->TopLeft = Position;
	Stat->BotRight = Position + vec2(200, 50);
	Stat->innerText = "Name: " + (*SelectedPlayer)->CharacterName;
	root->GetUIElement("CharacterFrame")->AppendChild(Stat);

	return root;
}
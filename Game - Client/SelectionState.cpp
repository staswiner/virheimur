#include "SelectionState.h"



SelectionState::SelectionState()
{
}


SelectionState::~SelectionState()
{
}

void SelectionState::Initialize()
{
	UI.GenerateForm(this->GenerateForm());
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
	UI.root->Draw();
	
	Draw3D();
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
	Mouse mouse;
	vec3 CameraPos(0,20,30);
	vec3 NewLightPos(-20,30,30);
	mat4 ProjectionMatrix = glm::perspective(radians(45.0f),
		float(RightTop.x / RightTop.y), 1.0f, 1000.0f);;
	mat4 ViewMatrix = rotate(mat4(), radians(30.0f), vec3(1, 0, 0));
	ViewMatrix = translate(ViewMatrix, -CameraPos);
	long long time = (chrono::duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count()/10 )% 1000;
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

UIElement * SelectionState::GenerateForm()
{

	vec2 Position;
	UIElement* root = new UIElement("Root", "");

	UIElement* UsernameElement = new UIElement("CharacterFrame", "Minimap/Minimap.png");
	Position = vec2(200, 200);
	UsernameElement->TopLeft = Position;
	UsernameElement->SetByTrueSize(Position);
	UsernameElement->AddHoverEvent([]
	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/TextboxHovered.png"); });
	UsernameElement->AddHoverDoneEvent([]
	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/Textbox.png"); });
	UsernameElement->AddReturnDefaultEvent([]
	(UIElement* Element)mutable-> void { Element->ChangePicture("Minimap/Minimap.png"); });
	UsernameElement->AddClickEvent([]
	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/TextboxSelected.png"); });
	root->AppendChild(UsernameElement);

	
	return root;
}

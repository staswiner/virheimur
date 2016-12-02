#include "Input.h"



Input::Input(GlobalDataObject& Data, UserInterface& UI)
	:Data(Data),UI(UI)
{
}


Input::~Input()
{
}

void Input::SetInitialCharacterData(GDO NewData)
{
	this->NewData = NewData;
}

GlobalDataObject& Input::TranslateInput()
{
	Camera::CalculateTimeDelta();
	this->GetMouseInput();

	UI.AcceptInput();

	return NewData;
}

Camera & Input::GetCamera()
{
	return this->camera;
}

Keyboard & Input::GetKeyboard()
{
	return this->keyboard;
}

Mouse & Input::GetMouse()
{
	return this->mouse;
}

void Input::GetMouseInput()
{
	/*Right Click Would point the place i want to go*/
	if (mouse.RightIsPressed())
	{
		RayCast ray(camera.GetProjectionMatrix(), camera.GetCameraMatrix());
		vec3 Destination = ray.PlaneIntersection(vec3(1,0,0),vec3(0,0,1),vec3(0,0,0), 
			ray.GetWorldRay(),camera.GetCameraPosition());
		Player myPlayer;
		myPlayer.GetUnitData().Destination = Destination;

		NewData.UpdateMyPlayer(myPlayer,Data.MyUsername);
		{

			PRMalgorithm prm;
			if (Data.Map)
			{
				delete Data.Map;
			}
			Data.Map = prm.GeneratePoints(myPlayer.GetUnitData().Position, Destination);
			Data.RouteChanged = true;
			if (Data.Path)
			{
				delete Data.Path;
			}
			Data.Path = prm.FoundPath(Data.Map, myPlayer.GetUnitData().Position, Destination);
		}
	}
	/*Left Click would change focus of User Interface Windows*/
	if (mouse.LeftIsPressed())
	{
		UI.LeftClick();
	}
	UI.FocusControl();
	if (UI.Pressed == nullptr)
	{
		// Allow camera, and game interactions
		camera.GetUpdatedCamera();
	}
	
}


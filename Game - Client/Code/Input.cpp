#include "Input.h"



Input::Input(GlobalDataObject& Data)
	:Data(Data)
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
	camera.GetUpdatedCamera();
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
	
	vec2 MouseCoord(mouse.GetMouseX(), mouse.GetMouseY());
	for each (UIWindow uiw in UI.vUIWindows)
	{
		if (MouseIsIn(MouseCoord, uiw.LeftTop, uiw.RightBot))
		{
			HoverFocus = uiw.TargetID;
		}
	}
	
}

bool Input::MouseIsIn(vec2 MouseCoord, vec2 WindowStart, vec2 WindowEnd)
{
	if (MouseCoord.x > WindowStart.x && MouseCoord.x < WindowEnd.x &&
		MouseCoord.y > WindowStart.y && MouseCoord.y < WindowEnd.y)
		return true;
	return false;
}

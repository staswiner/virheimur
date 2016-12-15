#include "Input.h"



Input::Input(GlobalDataObject& Data, UserInterface& UI,FBO* Index)
	:ReceivedData(Data),UI(UI)
{
	this->Index = Index;
}


Input::~Input()
{
}

void Input::SetInitialCharacterData(GDO NewData)
{
	this->NewData = NewData;
}

GlobalDataObject& Input::TranslateInput(GlobalDataObject& Data)
{
	NewData.Clear();
	NewData.MyUsername = ReceivedData.MyUsername;
	this->Data = &Data;
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
		//glNamedFramebufferReadBuffer(Index->PostProcessingFBO,GL_COLOR_ATTACHMENT0);
#pragma region FBO Read Pixel
		glBindFramebuffer(GL_FRAMEBUFFER, Index->PostProcessingFBO);
		glReadBuffer(GL_COLOR_ATTACHMENT0);
		vec4 pixel;
		int x = mouse.GetMouseX();
		glReadPixels(mouse.GetMouseX(), mouse.GetWindowSize().y-mouse.GetMouseY(), 1, 1, GL_RGBA, GL_FLOAT, &pixel);
		FBO::UnbindFrameBuffer();
#pragma endregion FBO Read Pixel
		vector<vec3> PlaneCoord;
		PlaneCoord.push_back(vec3(1, 0, 0)); // 1st vector of the plane
		PlaneCoord.push_back(vec3(0, 0, 1)); // second vector of the plane
		PlaneCoord.push_back(vec3(0, 50, 0)); // point on the plane
		// unused, just for reference
		vec3 CurrentPosition = Data->GetPlayerInformation()[ReceivedData.MyUsername].GetUnitData().GetPosition();
		// Get Fragment Plane
		PlaneCoord = loaded_Models["Land"]->meshes[0].mCollision->GetPlaneCoords(vec3(pixel.r,pixel.g,pixel.b));
		// Get Ray Cast
		RayCast ray(camera.GetProjectionMatrix(), camera.GetCameraMatrix());
		// Intersect Raycast with the plane
		vec3 Destination = ray.PlaneIntersection(PlaneCoord[0], PlaneCoord[1], PlaneCoord[2],
			ray.GetWorldRay(),camera.GetCameraPosition());
		// Set Destination to player
		Player& myPlayer = NewData.GetPlayerInformation()[ReceivedData.MyUsername]; // also creates the character
		myPlayer.Username = ReceivedData.MyUsername;
		myPlayer.unit_Data.Path.clear();
		myPlayer.unit_Data.Path.push_back(Destination);
		myPlayer.unit_Data.Destination = myPlayer.GetUnitData().Path.front();
		myPlayer.unit_Data.StartPoint = Data->GetPlayerInformation()[ReceivedData.MyUsername].unit_Data.Position;
		myPlayer.unit_Data.StartPointTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
	//	myPlayer.GetUnitData().Position = Destination;
		
		//{

		//	PRMalgorithm prm;
		//	if (ReceivedData.Map)
		//	{
		//		delete ReceivedData.Map;
		//	}
		//	ReceivedData.Map = prm.GeneratePoints(myPlayer.GetUnitData().Position, Destination);
		//	ReceivedData.RouteChanged = true;
		//	if (ReceivedData.Path)
		//	{
		//		delete ReceivedData.Path;
		//	}
		//	ReceivedData.Path = prm.FoundPath(ReceivedData.Map, myPlayer.GetUnitData().Position, Destination);
		//}

		Data->Effects.push_back(Effect("Collada", milliseconds(500), Destination));
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


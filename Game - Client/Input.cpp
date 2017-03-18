#include "Input.h"



Input::Input(GlobalDataObject& Data, UserInterface& UI,FBO* Index, GlobalDataObject& InputToScene)
	:ReceivedData(Data),UI(UI), InputToScene(InputToScene)
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
	this->GetKeyboardInput();

	return NewData;
}
GlobalDataObject& Input::TranslateInputOffline(GlobalDataObject& Data)
{
	NewData.Clear();
	NewData.MyUsername = ReceivedData.MyUsername;
	this->Data = &Data;
	Camera::CalculateTimeDelta();
	this->GetMouseInputOffline();

	UI.AcceptInput();
	this->GetKeyboardInput();

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
		Session& session = Session::GetInstance();
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
		vec3 CurrentPosition = Data->GetPlayerInformation()[session.CharacterName]->GetUnitData().GetPosition();
		// Get Fragment Plane
		PlaneCoord = loaded_Models["Land"]->meshes[0].mCollision->GetPlaneCoords(vec3(pixel.r,pixel.g,pixel.b));
		// Get Ray Cast
		RayCast ray(camera.GetProjectionMatrix(), camera.GetCameraMatrix());
		// Intersect Raycast with the plane
		vec3 Destination = ray.PlaneIntersection(PlaneCoord[0], PlaneCoord[1], PlaneCoord[2],
			ray.GetWorldRay(),camera.GetCameraPosition());
		// Set Destination to player
		Player* myPlayer = NewData.GetPlayerInformation()[session.CharacterName];
		myPlayer->Username = session.Username;
		// Other variables
		myPlayer->unit_Data.StartPoint = Data->GetPlayerInformation()[session.CharacterName]->unit_Data.Position;
		myPlayer->unit_Data.StartPointTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
		// Set Path
		myPlayer->unit_Data.Path.clear();
		/*myPlayer->unit_Data.Path.push_back(myPlayer->unit_Data.StartPoint);
		myPlayer->unit_Data.Path.push_back(Destination);*/
		//myPlayer->stats.Hp = Data->GetPlayerInformation()[ReceivedData.MyUsername]->stats.Hp - 5;
	//	myPlayer.GetUnitData().Position = Destination;
		
		//{
#define ASTAR 0
#define PRM 1
		int AlgorithmType = PRM;
		if (AlgorithmType == ASTAR)
		{
			vector<vec3> BacktrackPath = Stas::Maths::AstarGridB(Data->Map, myPlayer->unit_Data.StartPoint, Destination);
			for (int i = BacktrackPath.size() - 1; i >= 0; i--)
			{
				myPlayer->unit_Data.Path.push_back(BacktrackPath[i]);
				ReceivedData.RouteChanged = true;
			}
			ReceivedData.Path = &myPlayer->unit_Data.Path;
		}
		else if (AlgorithmType == PRM)
		{
			PRMalgorithm prm;
			auto startTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch());

			if (ReceivedData.Graph)
			{
				delete ReceivedData.Graph;
			}
			vector<vec3> BacktrackPath;
			
			milliseconds FastestRun(100000);
			milliseconds SlowestRun(0);
			float averageDistance = 0;
			int FindingChance = 0;
			for (int i = 0; i < 1; i++)
			{

			//	auto startTimeSingle = duration_cast<milliseconds>(system_clock::now().time_since_epoch());

				try
				{
					ReceivedData.Graph = prm.GeneratePoints(Data->Map, myPlayer->unit_Data.StartPoint, Destination);
					ReceivedData.RouteChanged = true;
				}
				catch (exception ex)
				{
					int i = 0;
				}
				BacktrackPath = prm.FoundPath(ReceivedData.Graph, myPlayer->unit_Data.StartPoint, Destination);
				//BacktrackPath = Stas::Maths::AstarGridB(Data->Map, myPlayer->unit_Data.StartPoint, Destination);

				//auto endTimeSingle = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
				//auto deltaSingle = endTimeSingle - startTimeSingle;
				//if (deltaSingle > SlowestRun)
				//	SlowestRun = deltaSingle;

				//if (deltaSingle < FastestRun)
				//	FastestRun = deltaSingle;

				//float TotalDistance = 0;
				//for (int i = 0; i < BacktrackPath.size()-1; i++)
				//{
				//	TotalDistance += glm::distance(BacktrackPath[i], BacktrackPath[i + 1]);
				//}
				//averageDistance += TotalDistance;
				//if (BacktrackPath.size() > 0)
				//	FindingChance++;
			}
			/*auto endTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
			auto deltaTime = endTime - startTime;*/
			for (int i = BacktrackPath.size() - 1; i >= 0; i--)
			{
				myPlayer->unit_Data.Path.push_back(BacktrackPath[i]);
			}
			if (myPlayer->unit_Data.Path.size() == 0)
			{
				int i = 0;
			}
			ReceivedData.Path = &myPlayer->unit_Data.Path;
		}
		Data->Effects.push_back(Effect("Collada", milliseconds(500), Destination));
	}
	/*Left Click would change focus of User Interface Windows*/

	if (mouse.LeftIsPressed())
	{
		UI.LeftPress();
		LeftWasPressed = true;
	}

	// on left release
	if (!mouse.LeftIsPressed() and LeftWasPressed == true)
	{
		LeftWasPressed = false;
		if (UI.LeftClick() == false) // something other than UI was clicked
		{
			glBindFramebuffer(GL_FRAMEBUFFER, Index->PostProcessingFBO);
			glReadBuffer(GL_COLOR_ATTACHMENT0);
			vec4 pixel;
			glReadPixels(mouse.GetMouseX(), mouse.GetWindowSize().y - mouse.GetMouseY(), 1, 1, GL_RGBA, GL_FLOAT, &pixel);
			if (pixel.g == 0 && pixel.b == 0 && !LeftWasPressed)
			{
				// NPCS
				int i = pixel.r;
				auto Shop = UI.root->GetUIElement("Shop");
				Shop->GetUIElement("Shop-Gold")->innerText = to_string(Data->GetPlayerInformation()[
					Session::GetInstance().CharacterName]->stats.Gold);
				Shop->Show();
			}
			if (pixel.r == 0 && pixel.b == 0 && !LeftWasPressed)
			{
				// Players
				int i = pixel.g;
			}
		}
	}
	// Hover Ingame
	glBindFramebuffer(GL_FRAMEBUFFER, Index->PostProcessingFBO);
	glReadBuffer(GL_COLOR_ATTACHMENT0);
	vec4 pixel;
	InputToScene.Highlight.clear();

	glReadPixels(mouse.GetMouseX(), mouse.GetWindowSize().y - mouse.GetMouseY(), 1, 1, GL_RGBA, GL_FLOAT, &pixel);
	if (pixel.g == 0 && pixel.b == 0 && !LeftWasPressed)
	{
		// NPCS
		int i = pixel.r;
		InputToScene.Highlight.push_back("House1");
	}

	// UI checks
	UI.FocusControl();
	if (UI.Pressed == nullptr or not UI.Pressed->visible)
	{
		// Allow camera, and game interactions
		camera.GetUpdatedCamera();
		// Locked camera
	/*	Player* myPlayer = Data->GetPlayerInformation()[ReceivedData.MyUsername];
		Unit_Data& unit = myPlayer->unit_Data;
		float Rotation;
		if (unit.Destination == unit.StartPoint)
		{
			Rotation = -acos(dot(vec3(0,0,0), vec3(1, 0, 0)));
		}
		else
		{
			Rotation = -acos(dot(glm::normalize(unit.Destination - unit.StartPoint), vec3(1, 0, 0)));
		}
			(unit.Destination.z - unit.StartPoint.z < 0) ?
				unit.Rotation.y = radians(360.0f) - unit.Rotation.y
				: unit.Rotation.y
				;
		camera.GetLockedCamera(myPlayer->unit_Data.Position, vec3(0, Rotation, 0));*/
	}
	
}
void Input::GetMouseInputOffline()
{
	/*Right Click Would point the place i want to go*/

	if (mouse.RightIsPressed())
	{
		OfflineDataObject& offlineData = OfflineDataObject::GetInstance();
		vec3 ClickOnMapCoord = GetMouseCoord_MapCoord();
		
		offlineData.Effects.push_back(Effect("Collada", milliseconds(500), ClickOnMapCoord));

		vec3 CurrentPosition = offlineData.player.GetUnitData().GetPosition();

		// Set Destination to player
		Player* myPlayer = &offlineData.player;
		// Other variables
		myPlayer->unit_Data.StartPoint = offlineData.player.unit_Data.Position;
		myPlayer->unit_Data.StartPointTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
		// Set Path
		myPlayer->unit_Data.Path.clear();
		/*myPlayer->unit_Data.Path.push_back(myPlayer->unit_Data.StartPoint);
		myPlayer->unit_Data.Path.push_back(Destination);*/
		//myPlayer->stats.Hp = Data->GetPlayerInformation()[ReceivedData.MyUsername]->stats.Hp - 5;
		//	myPlayer.GetUnitData().Position = Destination;

		//{
#define ASTAR 0
#define PRM 1
		int AlgorithmType = PRM;
		if (AlgorithmType == ASTAR)
		{
			vector<vec3> BacktrackPath = Stas::Maths::AstarGridB(Data->Map, myPlayer->unit_Data.StartPoint, ClickOnMapCoord);
			for (int i = BacktrackPath.size() - 1; i >= 0; i--)
			{
				myPlayer->unit_Data.Path.push_back(BacktrackPath[i]);
				ReceivedData.RouteChanged = true;
			}
			ReceivedData.Path = &myPlayer->unit_Data.Path;
		}
		else if (AlgorithmType == PRM)
		{
			PRMalgorithm prm;
			auto startTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch());

			if (ReceivedData.Graph)
			{
				delete ReceivedData.Graph;
			}
			vector<vec3> BacktrackPath;

			milliseconds FastestRun(100000);
			milliseconds SlowestRun(0);
			float averageDistance = 0;
			int FindingChance = 0;
			for (int i = 0; i < 1; i++)
			{

				//	auto startTimeSingle = duration_cast<milliseconds>(system_clock::now().time_since_epoch());

				try
				{
					ReceivedData.Graph = prm.GeneratePoints(Data->Map, myPlayer->unit_Data.StartPoint, ClickOnMapCoord);
					ReceivedData.RouteChanged = true;
				}
				catch (exception ex)
				{
					int i = 0;
				}
				BacktrackPath = prm.FoundPath(ReceivedData.Graph, myPlayer->unit_Data.StartPoint, ClickOnMapCoord);
				//BacktrackPath = Stas::Maths::AstarGridB(Data->Map, myPlayer->unit_Data.StartPoint, Destination);

				//auto endTimeSingle = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
				//auto deltaSingle = endTimeSingle - startTimeSingle;
				//if (deltaSingle > SlowestRun)
				//	SlowestRun = deltaSingle;

				//if (deltaSingle < FastestRun)
				//	FastestRun = deltaSingle;

				//float TotalDistance = 0;
				//for (int i = 0; i < BacktrackPath.size()-1; i++)
				//{
				//	TotalDistance += glm::distance(BacktrackPath[i], BacktrackPath[i + 1]);
				//}
				//averageDistance += TotalDistance;
				//if (BacktrackPath.size() > 0)
				//	FindingChance++;
			}
			/*auto endTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
			auto deltaTime = endTime - startTime;*/
			for (int i = BacktrackPath.size() - 1; i >= 0; i--)
			{
				myPlayer->unit_Data.Path.push_back(BacktrackPath[i]);
			}
			if (myPlayer->unit_Data.Path.size() == 0)
			{
				int i = 0;
			}
			ReceivedData.Path = &myPlayer->unit_Data.Path;
		}
	}
	/*Left Click would change focus of User Interface Windows*/

	if (mouse.LeftIsPressed())
	{
		UI.LeftPress();
		LeftWasPressed = true;
	}

	// on left release
	if (!mouse.LeftIsPressed() and LeftWasPressed == true)
	{
		LeftWasPressed = false;
		if (UI.LeftClick() == false) // something other than UI was clicked
		{
			glBindFramebuffer(GL_FRAMEBUFFER, Index->PostProcessingFBO);
			glReadBuffer(GL_COLOR_ATTACHMENT0);
			vec4 pixel;
			glReadPixels(mouse.GetMouseX(), mouse.GetWindowSize().y - mouse.GetMouseY(), 1, 1, GL_RGBA, GL_FLOAT, &pixel);
			//if (pixel.g == 0 && pixel.b == 0 && !LeftWasPressed)
			//{
			//	// NPCS
			//	int i = pixel.r;
			//	auto Shop = UI.root->GetUIElement("Shop");
			//	Shop->GetUIElement("Shop-Gold")->innerText = to_string(Data->GetPlayerInformation()[
			//		Session::GetInstance().CharacterName]->stats.Gold);
			//	Shop->Show();
			//}
			//if (pixel.r == 0 && pixel.b == 0 && !LeftWasPressed)
			//{
			//	// Players
			//	int i = pixel.g;
			//}
		}
	}
	// Hover Ingame
	glBindFramebuffer(GL_FRAMEBUFFER, Index->PostProcessingFBO);
	glReadBuffer(GL_COLOR_ATTACHMENT0);
	vec4 pixel;
	InputToScene.Highlight.clear();

	glReadPixels(mouse.GetMouseX(), mouse.GetWindowSize().y - mouse.GetMouseY(), 1, 1, GL_RGBA, GL_FLOAT, &pixel);
	if (pixel.g == 0 && pixel.b == 0 && !LeftWasPressed)
	{
		// NPCS
		int i = pixel.r;
		InputToScene.Highlight.push_back("House1");
	}

	// UI checks
	UI.FocusControl();
	if (UI.Pressed == nullptr or not UI.Pressed->visible)
	{
		// Allow camera, and game interactions
		camera.GetUpdatedCamera();
		// Locked camera
		/*	Player* myPlayer = Data->GetPlayerInformation()[ReceivedData.MyUsername];
		Unit_Data& unit = myPlayer->unit_Data;
		float Rotation;
		if (unit.Destination == unit.StartPoint)
		{
		Rotation = -acos(dot(vec3(0,0,0), vec3(1, 0, 0)));
		}
		else
		{
		Rotation = -acos(dot(glm::normalize(unit.Destination - unit.StartPoint), vec3(1, 0, 0)));
		}
		(unit.Destination.z - unit.StartPoint.z < 0) ?
		unit.Rotation.y = radians(360.0f) - unit.Rotation.y
		: unit.Rotation.y
		;
		camera.GetLockedCamera(myPlayer->unit_Data.Position, vec3(0, Rotation, 0));*/
	}

}

void Input::GetKeyboardInput()
{

	if (UI.InWorldCommands.size() > 0)
	{
		/* body of processed commands */
		GLchar input = UI.InWorldCommands.front();
		switch (input)
		{
		case ' ': ResetCharacterPosition(); break;
		}
		// end
		UI.InWorldCommands.pop_front();
	}
}

vec3 Input::GetMouseCoord_MapCoord()
{
	// FBO Read Pixel
	glBindFramebuffer(GL_FRAMEBUFFER, Index->PostProcessingFBO);
	glReadBuffer(GL_COLOR_ATTACHMENT0);
	vec4 pixel;
	int x = mouse.GetMouseX();
	glReadPixels(mouse.GetMouseX(), mouse.GetWindowSize().y - mouse.GetMouseY(), 1, 1, GL_RGBA, GL_FLOAT, &pixel);
	FBO::UnbindFrameBuffer();

	vector<vec3> PlaneCoord;
	PlaneCoord.push_back(vec3(1, 0, 0)); // 1st vector of the plane
	PlaneCoord.push_back(vec3(0, 0, 1)); // second vector of the plane
	PlaneCoord.push_back(vec3(0, 50, 0)); // point on the plane
										  // unused, just for reference
	// Get Fragment Plane
	PlaneCoord = loaded_Models["Land"]->meshes[0].mCollision->GetPlaneCoords(vec3(pixel.r, pixel.g, pixel.b));
	// Get Ray Cast
	RayCast ray(camera.GetProjectionMatrix(), camera.GetCameraMatrix());
	// Intersect Raycast with the plane
	vec3 ClickCoordOnMap = ray.PlaneIntersection(PlaneCoord[0], PlaneCoord[1], PlaneCoord[2],
		ray.GetWorldRay(), camera.GetCameraPosition());
	
	return ClickCoordOnMap;
}

void Input::ResetCharacterPosition()
{
	Session& session = Session::GetInstance();
	vec3 Position = loaded_Models["Land"]->meshes[0].mCollision->OnCollision(vec3(0));
	Player* myPlayer = NewData.GetPlayerInformation()[session.CharacterName]; // also creates the character
	myPlayer->Username = ReceivedData.MyUsername;
	myPlayer->unit_Data.Path.clear();
	myPlayer->unit_Data.Path.push_back(Position);
	myPlayer->unit_Data.Destination = myPlayer->GetUnitData().Path.front();
	myPlayer->unit_Data.StartPoint = Position;
	myPlayer->unit_Data.StartPointTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
}

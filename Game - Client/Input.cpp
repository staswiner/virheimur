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

Keyboard & Input::GetKeyboard()
{
	Keyboard& keyboard = Keyboard::Instance();
	return keyboard;
}

Mouse & Input::GetMouse()
{
	return Mouse::Instanace();
}

void Input::GetMouseInput()
{
	/*Right Click Would point the place I want to go*/
	Mouse& mouse = Mouse::Instanace();

	if (mouse.RightIsPressed())
	{
		Camera& camera = Camera::GetCamera("Main");

		Session& session = Session::Instance();
		//glNamedFramebufferReadBuffer(Index->PostProcessingFBO,GL_COLOR_ATTACHMENT0);
		vec4 pixel = Index->GetPixel(mouse.GetMouseX(), (int)mouse.GetWindowSize().y - mouse.GetMouseY());

		vector<vec3> PlaneCoord;
		// unused, just for reference
		vec3 CurrentPosition = Data->GetPlayerInformation()[session.CharacterName]->GetUnitData().Position;
		// Get Fragment Plane
		PlaneCoord = ModelsCollection::getInstance()["Land"]->meshes[0].mCollision->GetPlaneCoords(vec3(pixel.r,pixel.g,pixel.b));
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
			vec4 pixel = Index->GetPixel(mouse.GetMouseX(), (int)mouse.GetWindowSize().y - mouse.GetMouseY());

			if (pixel.g == 0 && pixel.b == 0 && !LeftWasPressed)
			{
				// NPCS
				int i = (int)pixel.r;
				auto Shop = UI.root->GetUIElement("Shop");
				Shop->GetUIElement("Shop-Gold")->innerText = to_string(Data->GetPlayerInformation()[
					Session::Instance().CharacterName]->stats.Gold);
				Shop->Show();
			}
			if (pixel.r == 0 && pixel.b == 0 && !LeftWasPressed)
			{
				// Players
				int i = (int)pixel.g;
			}
		}
	}
	// Hover Ingame
	InputToScene.Highlight.clear();

	vec4 pixel = Index->GetPixel(mouse.GetMouseX(), mouse.GetWindowSize().y - mouse.GetMouseY());

	if (pixel.g == 0 && pixel.b == 0 && !LeftWasPressed)
	{
		// NPCS
		int i = (int)pixel.r;
		InputToScene.Highlight.push_back("House1");
	}
	if (pixel.g == 0 && pixel.b == 0 && !LeftWasPressed)
	{
		// Characters
		int i = (int)pixel.r;
		if (i == 5)
		InputToScene.Highlight.push_back("House1");
	}
	// UI checks
	UI.FocusControl();
	if (UI.Pressed == nullptr or not UI.Pressed->visible)
	{
		Camera& camera = Camera::GetCamera("Main");

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
	/*Right Click Would point the place I want to go*/
	Mouse& mouse = Mouse::Instanace();

	if (mouse.RightIsPressed())
	{
		OfflineDataObject& offlineData = OfflineDataObject::Instance();
		vec3 ClickOnMapCoord = GetMouseCoord_MapCoord();
		
		offlineData.Effects.push_back(Effect("Collada", milliseconds(500), ClickOnMapCoord));

		vec3 CurrentPosition = offlineData.player.GetUnitData().Position;

		// Set Destination to player
		Player& myPlayer = offlineData.player;
		// Other variables
		myPlayer.unit_Data.StartPoint = offlineData.player.unit_Data.Position;
		myPlayer.unit_Data.StartPointTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
		// Set Path
		myPlayer.unit_Data.Path.clear();
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
			vector<vec3> BacktrackPath = Stas::Maths::AstarGridB(Data->Map, myPlayer.unit_Data.StartPoint, ClickOnMapCoord);
			for (int i = BacktrackPath.size() - 1; i >= 0; i--)
			{
				myPlayer.unit_Data.Path.push_back(BacktrackPath[i]);
				ReceivedData.RouteChanged = true;
			}
			ReceivedData.Path = &myPlayer.unit_Data.Path;
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
					ReceivedData.Graph = prm.GeneratePoints(Data->Map, myPlayer.unit_Data.StartPoint, ClickOnMapCoord);
					ReceivedData.RouteChanged = true;
				}
				catch (exception ex)
				{
					int i = 0;
				}

				BacktrackPath = prm.FoundPath(ReceivedData.Graph, myPlayer.unit_Data.StartPoint, ClickOnMapCoord);
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
				myPlayer.unit_Data.Path.push_back(BacktrackPath[i]);
			}

			if (myPlayer.unit_Data.Path.size() == 0)
			{
				int i = 0;
			}

			ReceivedData.Path = &myPlayer.unit_Data.Path;
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
			vec4 pixel = Index->GetPixel(mouse.GetMouseX(), (int)mouse.GetWindowSize().y - mouse.GetMouseY());
	
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
	InputToScene.Highlight.clear();

	vec4 pixel = Index->GetPixel(mouse.GetMouseX(), (int)mouse.GetWindowSize().y - mouse.GetMouseY());
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
		Camera& camera = Camera::GetCamera("Main");

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
	char input;
	if ((input = UI.AccessWorldCommands()) > -1)
	{
		/* body of processed commands */
		/*TAGS: #KeyboardInput #CommandsInWorld*/
		switch (input)
		{
		case ' ': ResetCharacterPosition(); ResetCameraPosition(); break;
		case 's': SetPlayerControl(Player::controls::Script); SetCircleScriptIterative(); break; // script
		case 'm': SetPlayerControl(Player::controls::Manual); break; // manual
		case 'd': SetPlayerControl(Player::controls::Direct); break; // direct
		case 'p': OpenProfileUI(); break;
		}
		// end
	}

	OfflineDataObject& offlineData = OfflineDataObject::Instance();
	
	if (offlineData.player.control == Player::controls::Manual)
	{
		ManualControl();
	}

	if (offlineData.player.control == Player::controls::Direct)
	{
		DirectControl();
	}
}

void Input::OnlineRightMouseClick()
{
	Camera& camera = Camera::GetCamera("Main");
	Mouse& mouse = Mouse::Instanace();

	Session& session = Session::Instance();
	//glNamedFramebufferReadBuffer(Index->PostProcessingFBO,GL_COLOR_ATTACHMENT0);
#pragma region FBO Read Pixel

	glBindFramebuffer(GL_FRAMEBUFFER, Index->PostProcessingFBO);
	glReadBuffer(GL_COLOR_ATTACHMENT0);
	vec4 pixel;

	int x = mouse.GetMouseX();
	glReadPixels(mouse.GetMouseX(), mouse.GetWindowSize().y - mouse.GetMouseY(), 1, 1, GL_RGBA, GL_FLOAT, &pixel);
	FBO::UnbindFrameBuffer();

#pragma endregion FBO Read Pixel
	vector<vec3> PlaneCoord;
	PlaneCoord.push_back(vec3(1, 0, 0)); // 1st vector of the plane
	PlaneCoord.push_back(vec3(0, 0, 1)); // second vector of the plane
	PlaneCoord.push_back(vec3(0, 50, 0)); // point on the plane
										  // unused, just for reference
	vec3 CurrentPosition = Data->GetPlayerInformation()[session.CharacterName]->GetUnitData().Position;
	// Get Fragment Plane
	PlaneCoord = ModelsCollection::getInstance()["Land"]->meshes[0].mCollision->GetPlaneCoords(vec3(pixel.r, pixel.g, pixel.b));
	// Get Ray Cast
	RayCast ray(camera.GetProjectionMatrix(), camera.GetCameraMatrix());
	// Intersect Raycast with the plane
	vec3 Destination = ray.PlaneIntersection(PlaneCoord[0], PlaneCoord[1], PlaneCoord[2],
		ray.GetWorldRay(), camera.GetCameraPosition());
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

void Input::OfflineRightMouseClick()
{
}
void Input::SetCircleScript()
{
}

#define ToType(type) *static_cast<type*>

void Input::RunScript()
{
	OfflineDataObject& offlineData = OfflineDataObject::Instance();
	offlineData.player.control = Player::controls::Script;
	offlineData.player.LongPath = false;
	STARTUPINFO siStartInfo;
	PROCESS_INFORMATION piProcessInfo;
	ZeroMemory(&siStartInfo, sizeof(siStartInfo));
	siStartInfo.cb = sizeof(siStartInfo);
	ZeroMemory(&piProcessInfo, sizeof(piProcessInfo));

	//< Players = vector<Player> : Player=class  >
	///< malloc for all players in a single data block and last digit is \0 />
	
	auto Handle = CreateProcess("RobotScript.exe", "", NULL, NULL, FALSE, 0, NULL, NULL, &siStartInfo, &piProcessInfo);
	TCP tcp;
	
	tcp.SendPacket("");
	string autism = to_string(GetLastError());
	
	
	
	WaitForSingleObject(piProcessInfo.hProcess, INFINITE);

	// Create Process # able to reuse same process
	// Send relevant information # hard disk I/O # TCP/IP
	// Wait for it to finish # exactly the length needed + tcp for receive and send
	// Pass output # TCP/IP

	CloseHandle(piProcessInfo.hProcess);
	CloseHandle(piProcessInfo.hThread);

}
// TODO
void Input::OpenProfileUI()
{
	UI.root;
	UIElement* Element = new UIElement("CharacterUI","");
	UI.root->AppendChild(Element);
}

//void Input::SetCircleScript()
//{
//	OfflineDataObject& offlineData = OfflineDataObject::GetInstance();
//	offlineData.player.LongPath = false;
//	offlineData.player.script = [&]() mutable-> void {
//		// TODO: current path, octagon
//		Player& p = offlineData.player;
//		Unit_Data& ud = offlineData.player.unit_Data;
//		vec3 test(3, 2, 1);
//		p.SetMemoryData("Test", &test);
//		if (p.GetMemoryData("Test") != nullptr)
//		{
//			vec3 test2 = ToType(vec3)(p.GetMemoryData("Test"));
//			int i = 0;
//			i++;
//		}
//		// fix to check if passed
//		if (glm::distance(ud.Position.xz(), ud.StartPoint.xz()) >= glm::distance(ud.Destination.xz(), ud.StartPoint.xz())) // passed destination
//		{
//			// TODO: Add first iteration values
//			if (offlineData.player.PathingStarted == false)
//			{
//				offlineData.player.PathingStarted = true;
//				float nextAngle = 0;
//				ud.StartPoint = ud.Destination;
//				ud.Destination = vec3(ud.StartPoint.x + cos(nextAngle) * 1.0f, 0, ud.StartPoint.x + sin(nextAngle) * 1.0f);
//				ud.StartPointTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
//				ud.Path.clear();
//				ud.Path.push_back(ud.StartPoint);
//				ud.Path.push_back(ud.Destination);
//				return;
//			}
//			// set next track
//		//	float currentAngle = -acos(dot(glm::normalize(ud.Destination.xz() - 
//		//		ud.StartPoint.xz()), vec2(0, 1)));
//			//atan2()
//			auto dot = ud.Destination.x * ud.StartPoint.x + ud.Destination.y * ud.StartPoint.y;
//			auto det = ud.Destination.x * ud.StartPoint.y - ud.Destination.y * ud.StartPoint.x;
//			float currentAngle = atan2(det, dot);
//
//			float nextAngle = currentAngle + radians(45.0f);
//			ud.StartPoint = ud.Destination;
//			ud.Destination = vec3(ud.StartPoint.x + cos(nextAngle) * cos(nextAngle) * 1.0f, 0, ud.StartPoint.x + sin(nextAngle) * sin(nextAngle) * 1.0f);
//			ud.StartPointTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
//			ud.Path.clear();
//			ud.Path.push_back(ud.StartPoint);
//			ud.Path.push_back(ud.Destination);
//		}
//	};
//}
// TODO: create a class for script + all of its data for cleanup purposes
void Input::SetCircleScriptIterative()
{
	OfflineDataObject& offlineData = OfflineDataObject::Instance();
	//offlineData.player.LongPath = false;
	//STARTUPINFO siStartInfo;
	//PROCESS_INFORMATION piProcessInfo;
	//auto Handle = CreateProcess(NULL, "", NULL, NULL, TRUE, 0, NULL, NULL, NULL,&piProcessInfo);
	//WaitForSingleObject(piProcessInfo.hProcess, INFINITE);


	Player& p = offlineData.player;
	Unit_Data& ud = offlineData.player.unit_Data;
	offlineData.player.script = [&](Player& p) mutable-> void {
		
		float Angle = 0.0f;
		if (p.GetMemoryData("Angle") != nullptr)
		{
			Angle = ToType(float)(p.GetMemoryData("Angle"));
			if (degrees(Angle) >= 360.0f)
			{
				Angle = radians(0.0f);
			}
			Angle += radians(3.0f);
			p.SetMemoryData("Angle", &Angle, sizeof(Angle));
		}
		// Set Angle Data
		else
		{
			Angle = 0.0f;
			p.SetMemoryData("Angle", &Angle, sizeof(Angle));
		}
		float speed= 0.5f;
		ud.Position += vec3(sin(Angle),0,cos(Angle)) * speed;
		ud.Rotation.y = Angle - radians(90.0f);
		ud.Rotation.xz;
	};
}

void Input::SetPlayerControl(Player::controls control)
{
	OfflineDataObject& offlineData = OfflineDataObject::Instance();
	offlineData.player.control = control;
}

void Input::ManualControl()
{
	Keyboard& keyboard = Keyboard::Instance();
	OfflineDataObject& offlineData = OfflineDataObject::Instance();
	Player& p = offlineData.player;
	if (p.control != Player::controls::Manual)
	{
		return;
	}
	
	float frameTime = Time::Instance().Frame();
	float MovementSpeed = 15.0f * frameTime / 1000.0f;
	float RotationSpeed = 5.0f * frameTime / 1000.0f;
	float angle = -p.unit_Data.Rotation.y;
#define anglex(x) cos(x)
#define angley(x) sin(x)

	if (keyboard.isKeyPressed(Key::Up)) // ↑
	{
		p.unit_Data.Destination = p.unit_Data.StartPoint =
			p.unit_Data.Position = p.unit_Data.Position + vec3(anglex(angle),0, angley(angle)) *
			MovementSpeed;
	}
	if (keyboard.isKeyPressed(Key::Down)) // ↓
	{
		p.unit_Data.Destination = p.unit_Data.StartPoint =
			p.unit_Data.Position = p.unit_Data.Position - vec3(anglex(angle), 0, angley(angle)) *
			MovementSpeed;
	}
	if (keyboard.isKeyPressed(Key::Right)) // →
	{
		p.unit_Data.Rotation.y -= RotationSpeed;
	}
	if (keyboard.isKeyPressed(Key::Left)) // ←
	{
		p.unit_Data.Rotation.y += RotationSpeed;
	}
	// fix values
	if (p.unit_Data.Rotation.y > radians(360.0f))
	{
		p.unit_Data.Rotation.y -= radians(360.0f);
	}
	if (p.unit_Data.Rotation.y < 0.0f)
	{
		p.unit_Data.Rotation.y += radians(360.0f);
	}
}

void Input::DirectControl()
{
	Keyboard& keyboard = Keyboard::Instance();
	OfflineDataObject& offlineData = OfflineDataObject::Instance();
	Player& p = offlineData.player;

	float frameTime = Time::Instance().Frame();
	float MovementSpeed = 15.0f * frameTime / 1000.0f;
	float RotationSpeed = 5.0f * frameTime / 1000.0f;
	float angle = -p.unit_Data.Rotation.y;
#define anglex(x) cos(x)
#define angley(x) sin(x)

	if (keyboard.isKeyPressed(Key::Up)) // ↑
	{
		p.unit_Data.Destination = p.unit_Data.StartPoint =
			p.unit_Data.Position = p.unit_Data.Position + vec3(anglex(angle), 0, angley(angle)) *
			MovementSpeed;
		p.unit_Data.Rotation.y = radians(180.0f);
	}
	if (keyboard.isKeyPressed(Key::Down)) // ↓
	{
		p.unit_Data.Destination = p.unit_Data.StartPoint =
			p.unit_Data.Position = p.unit_Data.Position + vec3(anglex(angle), 0, angley(angle)) *
			MovementSpeed;
		p.unit_Data.Rotation.y = radians(0.0f);
	}
	if (keyboard.isKeyPressed(Key::Right)) // →
	{
		p.unit_Data.Destination = p.unit_Data.StartPoint =
			p.unit_Data.Position = p.unit_Data.Position + vec3(anglex(angle), 0, angley(angle)) *
			MovementSpeed;
		p.unit_Data.Rotation.y = radians(90.0f);
	}
	if (keyboard.isKeyPressed(Key::Left)) // ←
	{
		p.unit_Data.Destination = p.unit_Data.StartPoint =
			p.unit_Data.Position = p.unit_Data.Position + vec3(anglex(angle), 0, angley(angle)) *
			MovementSpeed;
		p.unit_Data.Rotation.y = radians(270.0f);
	}
}

vec3 Input::GetMouseCoord_MapCoord()
{
	Camera& camera = Camera::GetCamera("Main");
	Mouse& mouse = Mouse::Instanace();

	// FBO Read Pixel
	vec4 pixel = Index->GetPixel(mouse.GetMouseX(), (int)mouse.GetWindowSize().y - mouse.GetMouseY());

	vector<vec3> PlaneCoord;
	PlaneCoord.push_back(vec3(1, 0, 0)); // 1st vector of the plane
	PlaneCoord.push_back(vec3(0, 0, 1)); // second vector of the plane
	PlaneCoord.push_back(vec3(0, 50, 0)); // point on the plane
										  // unused, just for reference
	// Get Fragment Plane
	PlaneCoord = ModelsCollection::getInstance()["Land"]->meshes[0].mCollision->GetPlaneCoords(vec3(pixel.r, pixel.g, pixel.b));
	// Get Ray Cast
	RayCast ray(camera.GetProjectionMatrix(), camera.GetCameraMatrix());
	// Intersect Raycast with the plane
	vec3 ClickCoordOnMap = ray.PlaneIntersection(PlaneCoord[0], PlaneCoord[1], PlaneCoord[2],
		ray.GetWorldRay(), camera.GetCameraPosition());
	
	return ClickCoordOnMap;
}

void Input::ResetCharacterPosition()
{
	Core& core = Core::GetInstance();
	if (core.Online)
	{
		Session& session = Session::Instance();
		vec3 Position = ModelsCollection::getInstance()["Land"]->meshes[0].mCollision->OnCollision(vec3(0));
		Player* myPlayer = NewData.GetPlayerInformation()[session.CharacterName]; // also creates the character
		myPlayer->Username = ReceivedData.MyUsername;
		myPlayer->unit_Data.Path.clear();
		myPlayer->unit_Data.Path.push_back(Position);
		myPlayer->unit_Data.Destination = myPlayer->GetUnitData().Path.front();
		myPlayer->unit_Data.StartPoint = Position;
		myPlayer->unit_Data.StartPointTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
	}
	else
	{
		OfflineDataObject& offlineData = OfflineDataObject::Instance();
		offlineData.player.unit_Data.Position = vec3();
		offlineData.player.unit_Data.Rotation = vec3();
	}
}

void Input::ResetCameraPosition()
{
	Camera& camera = Camera::GetCamera("Main");

	camera.ResetCamera();
}

#include "Input.h"



Input::Input(UserInterface& UI,FBO* Index)
	:UI(UI)
{
	this->Index = Index;
}


Input::~Input()
{
}

void Input::TranslateInputOffline()
{
	this->GetMouseInputOffline();

	UI.AcceptInput();
	this->GetKeyboardInput();
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
//	/*Right Click Would point the place I want to go*/
//	Mouse& mouse = Mouse::Instanace();
//
//	if (mouse.RightIsPressed())
//	{
//		Camera& camera = Camera::GetCamera("Main");
//
//		Session& session = Session::Instance();
//		//glNamedFramebufferReadBuffer(Index->PostProcessingFBO,GL_COLOR_ATTACHMENT0);
//		vec4 pixel = Index->GetPixel(mouse.GetMouseX(), (int)mouse.GetWindowSize().y - mouse.GetMouseY());
//
//		vector<vec3> PlaneCoord;
//		// unused, just for reference
//		vec3 CurrentPosition = Data->GetPlayerInformation()[session.CharacterName]->GetUnitData().Position;
//		// Get Fragment Plane
//		PlaneCoord = ModelsCollection::Instance()["Land"]->meshes[0].mCollision->GetPlaneCoords(vec3(pixel.r,pixel.g,pixel.b));
//		// Get Ray Cast
//		RayCast ray(camera.GetProjectionMatrix(), camera.GetCameraMatrix());
//		// Intersect Raycast with the plane
//		vec3 Destination = ray.PlaneIntersection(PlaneCoord[0], PlaneCoord[1], PlaneCoord[2],
//			ray.GetWorldRay(),camera.GetCameraPosition());
//		// Set Destination to player
//		GameObject* myPlayer = NewData.GetPlayerInformation()[session.CharacterName];
//		//myPlayer->Username = session.Username;
//		// Other variables
//		myPlayer->unit_Data.StartPoint = Data->GetPlayerInformation()[session.CharacterName]->unit_Data.Position;
//		myPlayer->unit_Data.StartPointTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
//		// Set Path
//		myPlayer->unit_Data.Path.clear();
//		/*myPlayer->unit_Data.Path.push_back(myPlayer->unit_Data.StartPoint);
//		myPlayer->unit_Data.Path.push_back(Destination);*/
//		//myPlayer->stats.Hp = Data->GetPlayerInformation()[ReceivedData.MyUsername]->stats.Hp - 5;
//	//	myPlayer.GetUnitData().Position = Destination;
//		
//		//{
//#define ASTAR 0
//#define PRM 1
//		int AlgorithmType = PRM;
//		if (AlgorithmType == ASTAR)
//		{
//			vector<vec3> BacktrackPath = Stas::Maths::AstarGridB(Data->Map, myPlayer->unit_Data.StartPoint, Destination);
//			for (int i = BacktrackPath.size() - 1; i >= 0; i--)
//			{
//				myPlayer->unit_Data.Path.push_back(BacktrackPath[i]);
//				ReceivedData.RouteChanged = true;
//			}
//			ReceivedData.Path = &myPlayer->unit_Data.Path;
//		}
//		else if (AlgorithmType == PRM)
//		{
//			PRMalgorithm prm;
//			auto startTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
//
//			if (ReceivedData.Graph)
//			{
//				delete ReceivedData.Graph;
//			}
//			vector<vec3> BacktrackPath;
//			
//			milliseconds FastestRun(100000);
//			milliseconds SlowestRun(0);
//			float averageDistance = 0;
//			int FindingChance = 0;
//			for (int i = 0; i < 1; i++)
//			{
//
//			//	auto startTimeSingle = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
//
//				try
//				{
//					ReceivedData.Graph = prm.GeneratePoints(Data->Map, myPlayer->unit_Data.StartPoint, Destination);
//					ReceivedData.RouteChanged = true;
//				}
//				catch (exception ex)
//				{
//					int i = 0;
//				}
//				BacktrackPath = prm.FoundPath(ReceivedData.Graph, myPlayer->unit_Data.StartPoint, Destination);
//				//BacktrackPath = Stas::Maths::AstarGridB(Data->Map, myPlayer->unit_Data.StartPoint, Destination);
//
//				//auto endTimeSingle = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
//				//auto deltaSingle = endTimeSingle - startTimeSingle;
//				//if (deltaSingle > SlowestRun)
//				//	SlowestRun = deltaSingle;
//
//				//if (deltaSingle < FastestRun)
//				//	FastestRun = deltaSingle;
//
//				//float TotalDistance = 0;
//				//for (int i = 0; i < BacktrackPath.size()-1; i++)
//				//{
//				//	TotalDistance += glm::distance(BacktrackPath[i], BacktrackPath[i + 1]);
//				//}
//				//averageDistance += TotalDistance;
//				//if (BacktrackPath.size() > 0)
//				//	FindingChance++;
//			}
//			/*auto endTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
//			auto deltaTime = endTime - startTime;*/
//			for (int i = BacktrackPath.size() - 1; i >= 0; i--)
//			{
//				myPlayer->unit_Data.Path.push_back(BacktrackPath[i]);
//			}
//			if (myPlayer->unit_Data.Path.size() == 0)
//			{
//				int i = 0;
//			}
//			ReceivedData.Path = &myPlayer->unit_Data.Path;
//		}
//		Data->Effects.push_back(Effect("Collada", milliseconds(500), Destination));
//		
//	}
//	/*Left Click would change focus of User Interface Windows*/
//
//	if (mouse.LeftIsPressed())
//	{
//		UI.LeftPress();
//		LeftWasPressed = true;
//	}
//
//	// on left release
//	if (!mouse.LeftIsPressed() and LeftWasPressed == true)
//	{
//		LeftWasPressed = false;
//		if (UI.LeftClick() == false) // something other than UI was clicked
//		{
//			vec4 pixel = Index->GetPixel(mouse.GetMouseX(), (int)mouse.GetWindowSize().y - mouse.GetMouseY());
//
//			if (pixel.g == 0 && pixel.b == 0 && !LeftWasPressed)
//			{
//				// NPCS
//				int i = (int)pixel.r;
//				auto Shop = UI.root->GetUIElement("Shop");
//				Shop->GetUIElement("Shop-Gold")->innerText = to_string(Data->GetPlayerInformation()[
//					Session::Instance().CharacterName]->stats.Gold);
//				Shop->Show();
//			}
//			if (pixel.r == 0 && pixel.b == 0 && !LeftWasPressed)
//			{
//				// Players
//				int i = (int)pixel.g;
//			}
//		}
//	}
	// Hover Ingame
	//InputToScene.Highlight.clear();
//
	//vec4 pixel = Index->GetPixel(mouse.GetMouseX(), mouse.GetWindowSize().y - mouse.GetMouseY());
	//
	//if (pixel.g == 0 && pixel.b == 0 && !LeftWasPressed)
	//{
	//	// NPCS
	//	int i = (int)pixel.r;
	//	InputToScene.Highlight.push_back("House1");
	//}
	//if (pixel.g == 0 && pixel.b == 0 && !LeftWasPressed)
	//{
	//	// Characters
	//	int i = (int)pixel.r;
	//	if (i == 5)
	//	InputToScene.Highlight.push_back("House1");
	//}
	//// UI checks
	//UI.FocusControl();
	//if (UI.Pressed == nullptr or not UI.Pressed->visible)
	//{
	//	Camera& camera = Camera::GetCamera("Main");
	//
	//	// Allow camera, and game interactions
	//	camera.GetUpdatedCamera();
	//	// Locked camera
	//*	Player* myPlayer = Data->GetPlayerInformation()[ReceivedData.MyUsername];
	//	Unit_Data& unit = myPlayer->unit_Data;
	//	float Rotation;
	//	if (unit.Destination == unit.StartPoint)
	//	{
	//		Rotation = -acos(dot(vec3(0,0,0), vec3(1, 0, 0)));
	//	}
	//	else
	//	{
	//		Rotation = -acos(dot(glm::normalize(unit.Destination - unit.StartPoint), vec3(1, 0, 0)));
	//	}
	//		(unit.Destination.z - unit.StartPoint.z < 0) ?
	//			unit.Rotation.y = radians(360.0f) - unit.Rotation.y
	//			: unit.Rotation.y
	//			;
	//	camera.GetLockedCamera(myPlayer->unit_Data.Position, vec3(0, Rotation, 0));*/
	//}
	
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
		GameObject& myPlayer = *offlineData.level.ActivePlayers[0];

		vec3 CurrentPosition = myPlayer.GetUnitData().Position;
		// Set Destination to player
		// Other variables
		myPlayer.unit_Data.StartPoint = myPlayer.unit_Data.Position;
		myPlayer.unit_Data.StartPointTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
		// Set Path
		myPlayer.unit_Data.Path.clear();
		/*myPlayer->unit_Data.Path.push_back(myPlayer->unit_Data.StartPoint);
		myPlayer->unit_Data.Path.push_back(Destination);*/
		//myPlayer->stats.Hp = Data->GetPlayerInformation()[ReceivedData.MyUsername]->stats.Hp - 5;
		//	myPlayer.GetUnitData().Position = Destination;

		//{
	/*Left Click would change focus of User Interface Windows*/
	}
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
	//InputToScene.Highlight.clear();

	vec4 pixel = Index->GetPixel(mouse.GetMouseX(), (int)mouse.GetWindowSize().y - mouse.GetMouseY());
	if (pixel.g == 0 && pixel.b == 0 && !LeftWasPressed)
	{
		// NPCS
		int i = pixel.r;
		//InputToScene.Highlight.push_back("House1");
	}

	// UI checks
	UI.FocusControl();
	if (UI.Pressed == nullptr or not UI.Pressed->visible)
	{
		Camera& camera = Camera::GetCamera(Camera::eCamera::Main);

		// Allow camera, and game interactions
		if (lockCamera == false)
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
		case ' ': ResetCharacterPosition(); /*ResetCameraPosition(); */break;
		case 's': SetPlayerControl(GameObject::controls::Script); SetCircleScriptIterative(); break; // script
		case 'm': SetPlayerControl(GameObject::controls::Manual); break; // manual
		case 'd': SetPlayerControl(GameObject::controls::Direct); break; // direct
		case 'p': OpenProfileUI(); break;
		case 'r': ReloadShaders(); break;
		case 'l': LockCamera(); break;
		}
		// end
	}

	OfflineDataObject& offlineData = OfflineDataObject::Instance();
	if (offlineData.level.ActivePlayers.size() > 0)
	{
		GameObject& Player = *offlineData.level.ActivePlayers[0];
		if (Player.control == GameObject::controls::Manual)
		{
			ManualControl();
		}

		if (Player.control == GameObject::controls::Direct)
		{
			DirectControl();
		}
	}
}

void Input::ReloadShaders()
{
	OfflineDataObject::Instance().level.ReloadShaders();
	Shader::ReloadAll();
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
	GameObject& Player = *offlineData.level.ActivePlayers[0];

	Player.control = GameObject::controls::Script;
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

// TODO: create a class for script + all of its data for cleanup purposes
void Input::SetCircleScriptIterative()
{
	OfflineDataObject& offlineData = OfflineDataObject::Instance();

	GameObject& Player = *offlineData.level.ActivePlayers[0];
	Unit_Data& ud = Player.unit_Data;
	auto& level = OfflineDataObject::Instance().level;
	vector<vec3> UnorderedList;
	// Player
	UnorderedList.push_back(Player.unit_Data.Position);
	// Mines
	for (auto& m : level.Entities)
	{
		if (m->Name == "Mine")
		{
			UnorderedList.push_back(m->unit_Data.Position);
		}
	}
	Player.script.Create([&, UnorderedList](GameObject& p) mutable-> ScriptState {
		Player.unit_Data.InputForceVectors.clear();

		list<vec3>* pOrderedList;
		if (p.script.GetMemoryData("OrderedList") == nullptr)
		{
			pOrderedList = new list<vec3>(Stas::Algorithms::Approximate::TSP::Christofides(UnorderedList));
			p.script.SetMemoryData("OrderedList", &pOrderedList, sizeof(pOrderedList));
		}
		else
		{
			pOrderedList = ToType(decltype(pOrderedList))(p.script.GetMemoryData("OrderedList"));
		}
		list<vec3>& OrderedList = *pOrderedList;
		// done
		if (OrderedList.size() == 0)
		{
			return ScriptState::Done;
		}


		vec3 movementVector = vec3(0);
		if (glm::distance(OrderedList.front(), p.unit_Data.Position) < 5.0f)
		{
			OrderedList.pop_front();
		}
		if (OrderedList.size() > 0)
		{
			if (OrderedList.front() != p.unit_Data.Position) // prevent normalizing 0 vector
				movementVector = normalize(OrderedList.front() - p.unit_Data.Position);
		}
		

		
		float speed= 100.0f;
		//Player.unit_Data.InputForceVectors.push_back(vec3(sin(Angle), 0, cos(Angle)) * speed);
		Player.unit_Data.InputForceVectors.push_back(movementVector * speed);
		float Angle = -acos(dot(movementVector, vec3(1, 0, 0)));
		if (movementVector.z < 0) Angle = radians(360.0f) - Angle;
		ud.Rotation.y = Angle;// -radians(90.0f);
		return ScriptState::OnGoing;
	});
	//Player.script = [&](GameObject& p) mutable-> void {
	//	// find first mine
	//	// find second mine
	//	// find 3rd mine
	//	// form potential pattern
	//	// test pattern, if does not follow pattern, construct new pattern

	//	// when a pattern is matched, calculate many possible mines ahead, create TSP algorithm between them
	//};
}

void Input::SetPlayerControl(GameObject::controls control)
{
	OfflineDataObject& offlineData = OfflineDataObject::Instance();
	GameObject& Player = *offlineData.level.ActivePlayers[0];
	Player.control = control;
}

void Input::ManualControl()
{
	Keyboard& keyboard = Keyboard::Instance();
	OfflineDataObject& offlineData = OfflineDataObject::Instance();
	GameObject& Player = *offlineData.level.ActivePlayers[0];
	if (Player.control != GameObject::controls::Manual)
	{
		return;
	}
	
	float frameTime = Time::Instance().Frame();
	float scale = 1.0f;
	float MovementSpeed = 600.0f * frameTime / 1000.0f * scale;
	float RotationSpeed = 5.0f * frameTime / 1000.0f;
	float angle = -Player.unit_Data.Rotation.y;
#define anglex(x) cos(x)
#define angley(x) sin(x)
	Player.unit_Data.InputForceVectors.clear();
	if (keyboard.isKeyPressed(Key::Up)) // ↑
	{
		Player.unit_Data.Destination = Player.unit_Data.StartPoint = Player.unit_Data.Position + vec3(anglex(angle),0, angley(angle)) *
			MovementSpeed;
		Player.unit_Data.InputForceVectors.push_back(vec3(anglex(angle), 0, angley(angle)) *
			MovementSpeed);
		Player.Soundtracks["MoveF"]->PlayLoop();
	} 
	else Player.Soundtracks["MoveF"]->Stop();
	if (keyboard.isKeyPressed(Key::Down)) // ↓
	{
		Player.unit_Data.Destination = Player.unit_Data.StartPoint = Player.unit_Data.Position - vec3(anglex(angle), 0, angley(angle)) *
			MovementSpeed;
		Player.unit_Data.InputForceVectors.push_back(-vec3(anglex(angle), 0, angley(angle)) *
			MovementSpeed);
		Player.Soundtracks["MoveB"]->PlayLoop();
	}
	else Player.Soundtracks["MoveB"]->Stop();
	if (keyboard.isKeyPressed(Key::Right)) // →
	{
		Player.unit_Data.Rotation.y -= RotationSpeed;
		Player.Soundtracks["TurnR"]->PlayLoop();
	}
	else Player.Soundtracks["TurnR"]->Stop();
	if (keyboard.isKeyPressed(Key::Left)) // ←
	{
		Player.unit_Data.Rotation.y += RotationSpeed;
		Player.Soundtracks["TurnL"]->PlayLoop();
	}
	else Player.Soundtracks["TurnL"]->Stop();
	// fix values
	if (Player.unit_Data.Rotation.y > radians(360.0f))
	{
		Player.unit_Data.Rotation.y -= radians(360.0f);
	}
	if (Player.unit_Data.Rotation.y < 0.0f)
	{
		Player.unit_Data.Rotation.y += radians(360.0f);
	}
}

void Input::DirectControl()
{
	Keyboard& keyboard = Keyboard::Instance();
	OfflineDataObject& offlineData = OfflineDataObject::Instance();
	GameObject& p = *offlineData.level.ActivePlayers[0];


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

void Input::LockCamera()
{
	if (lockCamera == false)
	{
		this->lockCamera = true;
	}
	else
	{
		this->lockCamera = false;
	}
}

vec3 Input::GetMouseCoord_MapCoord()
{
	Camera& camera = Camera::GetCamera(Camera::eCamera::Current);
	Mouse& mouse = Mouse::Instanace();

	// FBO Read Pixel
	vec4 pixel = Index->GetPixel(mouse.GetMouseX(), (int)mouse.GetWindowSize().y - mouse.GetMouseY());

	vector<vec3> PlaneCoord;
	PlaneCoord.push_back(vec3(1, 0, 0)); // 1st vector of the plane
	PlaneCoord.push_back(vec3(0, 0, 1)); // second vector of the plane
	PlaneCoord.push_back(vec3(0, 50, 0)); // point on the plane
										  // unused, just for reference
	// Get Fragment Plane
	PlaneCoord = ModelsCollection::Instance()["Land"]->meshes[0].mCollision->GetPlaneCoords(vec3(pixel.r, pixel.g, pixel.b));
	// Get Ray Cast
	RayCast ray(camera.GetProjectionMatrix(), camera.GetCameraMatrix());
	// Intersect Raycast with the plane
	vec3 ClickCoordOnMap = ray.PlaneIntersection(PlaneCoord[0], PlaneCoord[1], PlaneCoord[2],
		ray.GetWorldRay(), Camera::GetCamera(Camera::eCamera::Current).Position);
	
	return ClickCoordOnMap;
}

void Input::ResetCharacterPosition()
{
	OfflineDataObject& offlineData = OfflineDataObject::Instance();
	offlineData.level.Reset();
}

void Input::ResetCameraPosition()
{
	Camera& camera = Camera::GetCamera(Camera::eCamera::Current);

	camera.ResetCamera();
}

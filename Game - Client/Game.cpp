#include "Game.h"

PlayerRepository Game::Players;
PlayerRepository Game::NewPlayers;
PlayerRepository Game::ReceivedPlayers;
GlobalDataObject Game::NewData;
GlobalDataObject Game::ReceivedData(ReceivedPlayers);
GlobalDataObject Game::InputToScene;
GlobalDataObject Game::Data(Players);
FBO Game::Index;

UserInterface Game::UI;

Game::Game(Scene& scene, Network& network, Input& input, GameLogic& logic)
	: scene(scene),
	network(network),
	input(input),
	logic(logic)
{
	Online = false;
	Core & core = Core::GetInstance();
	core.Online = false;
	State = Online?0:2;

}


Game::~Game()
{
	if (Online)
	{
		Receiver.detach();
	}
	//network.Send("FIN","127.0.0.1","27045");
	if (not Online)
	{
		/// local server process deletion
		//CloseHandle(pi.hProcess);
		//CloseHandle(pi.hThread);
		/// other workaround
	}

}

void Game::Initialize()
{
#pragma region Network
	if (Online)
	{
		network.InitializeConnection();
		// Authentication
		/*ReadAuthentication();
		Data.MyUsername = Username;*/
		Receiver = std::thread(&Network::BeginReceive, &network);
	}
#pragma endregion Network
#pragma region Offline Network Simulator
	if (not Online)
	{
		/// create local server instance
	//	// set the size of the structures
	//	ZeroMemory(&si, sizeof(si));
	//	si.cb = sizeof(si);
	//	ZeroMemory(&pi, sizeof(pi));
	////	CreateProcess("Local_Server_CS.exe","",NULL,NULL,FALSE,0,NULL,NULL,&si,&pi);
	//	network.InitializeLocalConnection();
	//	//ReadAuthentication();
	//	Receiver = std::thread(&Network::BeginReceive, &network);
		/// other workaround
	}
#pragma endregion
	// Initialize 3D Graphics
	scene.Initialize();
	if (Online)
	{
		selectionState.Initialize(&State);
		loginState.Initialize(&State);
		characterCreationState.Initialize(&State);
	}
	// Sets NewData (spawn) 


}
int i = 0;
void Game::Loop()
{
#define is ==
	// Frame Time
	Time& time = Time::GetST();
	time.CalculateFrame();


	static char LastState = State;
	if (State != LastState)
	{
		StateChanged = true;
		LastState = State;
	}
	else
	{
		StateChanged = false;
	}
	switch (State)
	{
	case 0:LoginScreen(); break;
	case 1:SelectionScreen(); break;
	case 2:(Online ? GameScreen() : GameScreenOffline()); break;
	case 3:CharacterCreationScreen(); break;
	case 4:TestGround(); break;
	case 5:
	case 6:
	case 7:
	case 8:
	default:break;
	}
#undef is
}

void Game::ThreadedLoop()
{
	while(1)
	scene.DrawThreaded();
}


void Game::LoginScreen()
{
	//LoginUserInput();
	//ApplyGameLogic();

	//LoginUpdateNetwork();
	//UpdateVariables(ProjectionMatrix, ViewMatrix);
	//GetGameOnlineGameState();
	//DrawScene();
	loginState.Input();
	loginState.Draw(this->m_hdc);
}

void Game::SelectionScreen()
{
	if (StateChanged)
		selectionState.Reload();
	selectionState.Input();
	selectionState.Draw(this->m_hdc);
}

void Game::GameScreen()
{
	// Accepts input
	try {

		UserInput();
	}
	catch (exception ex)
	{
		int i = 0;
	}
	// Sets last frame updates to transfer
	/*try {

	AddToNewData();
	}
	catch (exception ex)
	{
	int i = 0;
	}*/
	// Sends 'NewData' object to the server
	try {

		UpdateNetwork();
	}
	catch (exception ex)
	{
		int i = 0;
	}

	// Creates 'Data' object as a combination of NewData and ReceivedData
	try {

		CombineData();
	}
	catch (exception ex)
	{
		int i = 0;
	}
	// proceeds logic of the final 'Data' object
	try {

		ApplyGameLogic();
	}
	catch (exception ex)
	{
		int i = 0;
	}

	// Draws 'Data' object
	try {
		DrawScene();
	}
	catch (exception ex)
	{
		int i = 0;
	}
}
void Game::GameScreenOffline()
{
	// Accepts input
	try {

		UserInput();
	}
	catch (exception ex)
	{
		int i = 0;
	}

	// Creates 'Data' object as a combination of NewData and ReceivedData
	try {

		CombineData();
	}
	catch (exception ex)
	{
		int i = 0;
	}
	// proceeds logic of the final 'Data' object
	try {

		ApplyGameLogic();
	}
	catch (exception ex)
	{
		int i = 0;
	}

	// Draws 'Data' object
	try {
		DrawScene();
	}
	catch (exception ex)
	{
		int i = 0;
	}
}
void Game::TestGround()
{
	TCP tcp;
	tcp.SendPacket("Hello world hi<EOF>");
	string Receive = tcp.ReceivePacketsAsync();
 	OutputDebugString(Receive.c_str());
}
void Game::GenerateForm()
{
}
void Game::CharacterCreationScreen()
{
	characterCreationState.Input();
	characterCreationState.Draw(this->m_hdc);
}

void Game::LoginUserInput()
{
}
void Game::AddToNewData()
{
	for (auto p : Data.GetPlayerInformation())
	{
		Unit_Data& uData = p.second->unit_Data;
		/*if (uData.PathChanged)
		{
			NewData.GetPlayerInformation()[p.first].unit_Data.StartPointTime = uData.StartPointTime;
			NewData.GetPlayerInformation()[p.first].unit_Data.StartPoint = uData.StartPoint;
			NewData.GetPlayerInformation()[p.first].unit_Data.Destination = uData.Destination;
			uData.PathChanged = false;
		}*/
	}
}

void Game::UserInput()
{
	NewData = ( Online? input.TranslateInput(Data) : input.TranslateInputOffline(Data));
	// Camera
	Camera& camera = input.GetCamera();
	FrameData& frameData = FrameData::GetInstance();
	frameData.ProjectionMatrix = camera.GetProjectionMatrix();
	frameData.ViewMatrix = camera.GetCameraMatrix();
}
void Game::UserInputOffline()
{
	GlobalDataObject Data;
	Data.GetPlayerInformation();
}

void Game::ApplyGameLogic()
{
	// Alters Data object 
	Core& core = Core::GetInstance();
	if (core.Online)
	{
		logic.Proceed(Data);
	}
	else
	{
		logic.ProcessDataOffline();
	}
}

void Game::GetGameOnlineGameState()
{
	string Data = network.Receive();
	//string Data = network->Receive();
	//logic.BuildData();
}

void Game::DrawScene()
{
	scene.Frame();
}

void Game::UpdateNetwork()
{
	//network.SetNewData( this->NewData );
	network.SendNewData(this->NewData);
}

void Game::CombineData()
{
	// NewData
	//	MyChampion : Destination
	// ReceivedData
	//	AllChampions : Destination, StartTime`
	// =
	// Data
	// Received Data
//	Data.GetPlayerInformation() = ReceivedData.GetPlayerInformation();
	// New Data
//	Data.GetPlayerInformation() = NewData.GetPlayerInformation();
	//for(auto p : NewData.GetPlayerInformation())
	//{
	//	Data.GetPlayerInformation()[p.first] = p.second;
	//}
	// Received Data
	for (auto p : ReceivedData.GetPlayerInformation())
	{
		Data.GetPlayerInformation()[p.first] = p.second;
	}

}

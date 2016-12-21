#include "Game.h"

PlayerRepository Game::Players;
PlayerRepository Game::NewPlayers;
PlayerRepository Game::ReceivedPlayers;
GlobalDataObject Game::NewData;
GlobalDataObject Game::ReceivedData(ReceivedPlayers);
GlobalDataObject Game::Data(Players);
FBO Game::Index;

UserInterface Game::UI;

Game::Game(Scene& scene, Network& network, Input& input, GameLogic& logic)
	: scene(scene),
	network(network),
	input(input),
	logic(logic)
{
	Loggedin = true;
}


Game::~Game()
{
	Receiver.detach();
	//network.Send("FIN","127.0.0.1","27045");
}

void Game::Initialize()
{
#pragma region Network
	network.InitializeConnection();
	// Authentication
	//network.Send("Authentication Came2fame Ilovemyreann<3");
	ReadAuthentication();
	Data.MyUsername = Username;
	Receiver = std::thread(&Network::BeginReceive, &network);
	network.Send("Authentication " + Username + " " + Password);
#pragma endregion Network
	// Initialize 3D Graphics
	scene.Initialize();
	loginState.Initialize();
	// Sets NewData (spawn) 


}
int i = 0;
void Game::Loop()
{
	if (!Loggedin)
	{
		LoginScreen();
	}
	else
	{
		// Accepts input
		UserInput();
		// Sets last frame updates to transfer
		AddToNewData();
		// Sends 'NewData' object to the server
		UpdateNetwork();
		// Updates Variables
		UpdateVariables(ProjectionMatrix, ViewMatrix);
		// Creates 'Data' object as a combination of NewData and ReceivedData
		CombineData();
		// proceeds logic of the final 'Data' object
		ApplyGameLogic();
		GetGameOnlineGameState();
		// Draws 'Data' object
		DrawScene();
	}
}

void Game::ThreadedLoop()
{
	while(1)
	scene.DrawThreaded();
}

void Game::LoginScreen()
{
	LoginUserInput();
	ApplyGameLogic();

	//LoginUpdateNetwork();
	//UpdateVariables(ProjectionMatrix, ViewMatrix);
	//GetGameOnlineGameState();
	DrawScene();
	loginState.Draw();
}

void Game::LoginUserInput()
{
}

void Game::UpdateVariables(mat4 & ProjectionMatrix, mat4 & ViewMatrix)
{
	this->ProjectionMatrix = ProjectionMatrix;
	this->ViewMatrix = ViewMatrix;
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
	NewData = input.TranslateInput(Data);
	// Camera
	Camera& camera = input.GetCamera();
	ViewMatrix = camera.GetCameraMatrix();
	ProjectionMatrix = camera.GetProjectionMatrix();
}

void Game::ApplyGameLogic()
{
	// Alters Data object 
	logic.Proceed(Data,ProjectionMatrix,ViewMatrix);
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

void Game::ReadAuthentication()
{
	string line;
	ifstream myfile("Authentication.txt");
	if (myfile.is_open())
	{
		getline(myfile, line);
		Username = line;
		getline(myfile, line);
		Password = line;
		myfile.close();
	}
	else
		exit(2);
}

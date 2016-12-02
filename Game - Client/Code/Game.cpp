#include "Game.h"


GlobalDataObject Game::Data;
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
	input.SetInitialCharacterData(network.GetNewData()); // unsafe


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
		UserInput();
		ApplyGameLogic();

		UpdateNetwork();
		UpdateVariables(ProjectionMatrix, ViewMatrix);
		GetGameOnlineGameState();
		DrawScene();
	}
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

void Game::UserInput()
{
	NewData = input.TranslateInput();
	Camera& camera = input.GetCamera();
	ViewMatrix = camera.GetCameraMatrix();
	ProjectionMatrix = camera.GetProjectionMatrix();
}

void Game::ApplyGameLogic()
{
	logic.Proceed(NewData,ProjectionMatrix,ViewMatrix);
}

void Game::GetGameOnlineGameState()
{
	string Data = network.Receive();
	//string Data = network->Receive();
	logic.BuildData();
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

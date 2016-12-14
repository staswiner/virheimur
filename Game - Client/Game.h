#pragma once
#include "Scene.h"
#include "GameLogic.h"
#include "Input.h"
#include "Network.h"
#include "LoginState.h"
#include "UserInterface.h"
#include <thread>
class Game
{
public:
	Game(Scene& scene = *(new Scene(Data, UI, &Index)), Network& network = *(new Network(ReceivedData)),
		Input& input = *(new Input(Data,UI, &Index)), GameLogic& logic = *(new GameLogic(Data)));
	~Game();
	void Initialize();
	void Loop();
	void SetHDC(HDC& hdc) { this->scene.SetWindowHDC(hdc); }
private:
	// Major States
	void LoginScreen();
	void GameState();

#pragma region LoginState
	void LoginUserInput();
#pragma endregion LoginState
#pragma region GameState
	void UpdateVariables(mat4& ProjectionMatrix,mat4& ViewMatrix);
	void AddToNewData();
	void UserInput();
	void ApplyGameLogic();
	void GetGameOnlineGameState();
	void DrawScene();
	void UpdateNetwork();
	void CombineData();
#pragma endregion GameState
	Scene& scene;
	Network& network;
	Input& input;
	static FBO Index;
	GameLogic& logic;
	LoginState loginState;
	static UserInterface UI;
	static GlobalDataObject NewData;
	static GlobalDataObject ReceivedData;
	static GlobalDataObject Data;
	mat4 ProjectionMatrix;
	mat4 ViewMatrix;
	std::thread Receiver;

	void ReadAuthentication();
	string Username;
	string Password;
	bool Loggedin;
};


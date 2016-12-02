#pragma once
#include "Scene.h"
#include "GameLogic.h"
#include "Input.h"
#include "Network.h"
#include "LoginState.h"
#include <thread>
class Game
{
public:
	Game(Scene& scene = *(new Scene(Data)), Network& network = *(new Network(Data)),
		Input& input = *(new Input(Data)), GameLogic& logic = *(new GameLogic(Data)));
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
	void UserInput();
	void ApplyGameLogic();
	void GetGameOnlineGameState();
	void DrawScene();
	void UpdateNetwork();
#pragma endregion GameState
	Scene& scene;
	Network& network;
	Input& input;
	GameLogic& logic;
	LoginState loginState;
	static GlobalDataObject Data;
	GlobalDataObject NewData;
	mat4 ProjectionMatrix;
	mat4 ViewMatrix;
	std::thread Receiver;

	void ReadAuthentication();
	string Username;
	string Password;
	bool Loggedin;
};


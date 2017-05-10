#pragma once

#include "LoginState.h"
#include "SelectionState.h"
#include "UserInterface.h"
#include "CharacterCreationState.h"
#include "TCP.h"
#include "GameState.h"
#include <process.h>
#include <thread>
__declspec(align(16)) class Game
{
public:
	Game(Scene& scene = *(new Scene(UI, &Index)),
		Input& input = *(new Input(UI, &Index)), GameLogic& logic = *(new GameLogic()));
	~Game();
	void Initialize();
	void Loop();
	void SetHDC(HDC& hdc) { this->scene.SetWindowHDC(hdc); this->m_hdc = hdc; }
	
private:
	// Major States
	void LoginScreen();
	void SelectionScreen();
	void GameScreen();
	void GameScreenOffline();
	void TestGround();
	void GenerateForm();
	void CharacterCreationScreen();

#pragma region LoginState
	void LoginUserInput();
#pragma endregion LoginState
#pragma region GameState
	void AddToNewData();
	void UserInput();
	void UserInputOffline();
	void ApplyGameLogic();
	void GetGameOnlineGameState();
	void DrawScene();
#pragma endregion GameState
	Scene& scene;
	Input& input;
	static FBO Index;
	GameLogic& logic;
	LoginState loginState;
	SelectionState selectionState;
	CharacterCreationState characterCreationState;
	static UserInterface UI;
	std::thread Receiver;
	HDC m_hdc;
	char State; // 0 Login, 1 Selection, 2 game
	bool StateChanged;
	bool Online = true;

	// process running variables
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
};


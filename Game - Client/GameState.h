#pragma once
#include "Input.h"
#include "Scene.h"
#include "GameLogic.h"
#include "Network.h"

//class GameState
//{
//public:
//	GameState(Scene& scene = *(new Scene(Data, UI, &Index)), Network& network = *(new Network(ReceivedData)),
//		Input& input = *(new Input(Data, UI, &Index)), GameLogic& logic = *(new GameLogic(Data)));
//	~GameState();
//	void Initialize(char* State);
//	void Inputfunc();
//	void Draw(HDC hdc);
//	void Draw3D();
//	void CreateNewCharacter();
//	void ChangeCharacter(bool direction);
//private:
//	UIElement* GenerateForm();
//	UserInterface UI;
//	HDC m_hdc;
//	vec2 LeftBot;
//	vec2 RightTop;
//	MultiSampleFBO mAntiAliasing;
//	vector<Player*> Characters;
//	vector<Player*>::iterator SelectedPlayer;
//	Scene& scene;
//	Input& input;
//	GameLogic& gameLogic;
//	Network& network;
//
//	static FBO Index;
//	static UserInterface UI;
//	static GlobalDataObject NewData;
//	static GlobalDataObject ReceivedData;
//	static GlobalDataObject Data;
//	static PlayerRepository Players;
//	static PlayerRepository NewPlayers;
//	static PlayerRepository ReceivedPlayers;
//	char* State;
//};
//

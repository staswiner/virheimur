#pragma once
#include "Game.h"

class MainLoop
{
private:
public:
	Game game;
	MainLoop()
	{

	}
	~MainLoop()
	{

	}
	void GameLoop()
	{
		game.Loop();
	}
	void Initialize()
	{
		game.Initialize();
	}
};

//#pragma once
////#define _WINSOCKAPI_
//#define WIN32_LEAN_AND_MEAN
//#include <vector>
//#include "MathGrass.h"
//#include "ShaderBuilder.h"
//#include "UserInterface.h"
//#include "FPS.h"
//
//
//using namespace std;
//#define Offline_Flag 1
//class MainLoop
//{
//public:
//	/// Variables
//	static HDC m_hDC;
//	static bool IsLoaded;
//	/// Methods
//	MainLoop();
//	/*
//	``Sets up Connection To Server, Starts OpenGL engines``
//	*/
//	void Initalize();
//	void Initialize();
//	/*
//	Load Models mostly
//	*/
//	void LoadGame();
//	/*
//	``Bind Objects to Graphic Card``
//	*/
//	void BindGame();
//	/*
//	``Releases Data, Joins Threads``
//	*/
//	~MainLoop();
//	/*
//	``Compiles Scene and Draws it``
//	*/
//	void Draw_Scene();
//	void Loop();
//	/*
//	``[Static] Sets Projection Matrix``
//	*/
//	void SetProjectionMatrix(mat4&);
//	/*
//	``Collision, Returns Destination Point``
//	*/
//	vec3 Collision(vec3 WorldRay);
//	vec3 GetCameraPosition(mat4& projectionMat, mat4& cameraMat);
//	future<void> LoadModels;
//	Game game;
//private:
//	void test();
//	/*
//	``Draws the background and Game Units``
//	*/
//	void Draw_All_Static_Objects_And_Units();
//	/*
//	``Draws To Depth Buffer``
//	*/
//	void Draw_To_Depth_Buffer();
//	/*
//	``Draws All Dynamic Units Stored And Passed from the DataBase``
//	*/
//	void Draw_All_Units();
//	void Draw_All_Units( Shader&);
//	/*
//	``Sends Input to Server to receive Updated Unit Locations``
//	*/
//	void ServerClient_DataLoop();
//	/*
//	``Compiles Scene and Draws it``
//	*/
//	void SendData();
//	/*
//	"Receive ClientID" to Generate the client with a new ID
//	"Receive Data" to Receive lost data
//	*/
//	void GenerateConnection(string);
//	/*
//	``Draws SkyBox``
//	*/
//	void DrawSky();
//	void DrawGround(Shader&);
//	void Draw2DObjects();
//	void DrawSky(Shader&);
//	void Shadow_DrawGround(Shader&);
//	void DrawSea();
//	void DrawEntities();
//	void DrawPreBuffer();
//	
//
//	void SetCameraView();
//	Ground_Collision* mGround_Collision;
//	
//	/*
//	Draws Loading Screen While Game Is Loading
//	*/
//	void Draw_Loading_Screen();
//	Loading_Screen tLoading_Screen;
//
//	///World Defining Matrices
//	static mat4 ProjectionMatrix;
//	static mat4 ViewMatrix;
//		   mat4 ModelMatrix;
//
//
//	Shader* GaussicShader;
//	Model* Katarina;
//	MathGrass* mMGrass;
//	Loader* mSkyBox;
//	Loader* mGround;
//	Loader* mGrass;
//	Sea mSea;
//	vector<Loader*> mUnits;
//	vector<Loader*> m2Dobjects;
//	_2D_Interface *Bar;
//	Inventory *inventory;
//	Shadow_Mapping *shadow;
//	ChampionChat* championChat;
//
//	FBO mHBlur;
//	FBO mVBlur;
//	FBO mHBlurS;
//	FBO mVBlurS;
//	FBO mRadialBlur;
//	FBO mCombine;
//	FBO LastLayer;
//	FBO mBright;
//	FBO mSkyFbo;
//	FBO mGammaCorrection;
//	MultiSampleFBO mAntiAliasing;
//public:	FBO mPostProcessing;
//		PreEffect mPreEffect;
//		FBO mGaussicEffect;
//private:
//	void DrawScene_Depth();
//	void DrawScene_Refraction();
//	void DrawScene_Reflection();
//	void DrawScene_PreEffect();
//	void DrawGaussicEffect();
//	void Draw_All_Units_Gaussic();
//	void DrawScene_PostProcessing();
//	void Set_Unit_Data();
//	vector<Unit_Data> m_Unit_Data[2];
//	int Channel = 0;
//	vector<GrassObjects*> m_GrassObjects;
//	/// static covered Classes
//	Mouse mouse;
//	Keyboard keyboard;
//	Loaded_Models m_Loaded_Models;
//	Model* Soldier;
//
//	static Camera camera;
//	vec3 LightPosition;
//	TransferedData UpdatedData;
//
//	thread Connect;
//	Client client;
//	future<void> SocketLoop;
//	future<bool> DataUpdateRequest;
//	static unsigned int ClientID;
//
//	/* who the fuck knows if i'll ever need it?!
//	*/
//	Unit_Data TranslatedData(string, unsigned int); // Unused Method
//	void CheckUnits(); // TODO
//	int Counter = 0;
//	friend float FindMatch(float x, float z);
//
//	void OfflineInitialize();
//	void OfflineDataLoop();
//
//	Text text;
//	void UserInput();
//	void DrawUI();
//	UserInterface UI;
//	FPS fps;
//
//};
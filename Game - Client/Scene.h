#pragma once
#include <map>
#include "Graphics_Header.h"
#include "FBO.h"
#include "Shader.h"
#include "ShaderBuilder.h"
#include "Camera.h"
#include "Sea.h"
#include "Player.h"
#include "Shadow_Mapping.h"
#include "MultiSampleFBO.h"
#include "Ground_Collision.h"
#include "ChampionChat.h"
#include "FPS.h"
#include "UserInterface.h"
#include "GlobalDataObject.h"
#include "Minimap.h"
#include "MenuPanel.h"
#include "LoginState.h"
#include "UIElement.h"
#include "Cursor.h"
#include "SeaAnimated.h"
#include "NPC.h"
#include "Default.h"
using namespace glm;
class Scene
{
public:
	//Scene() {}
	Scene(GlobalDataObject&,UserInterface&,FBO* Index,GlobalDataObject&);
	~Scene();
	GlobalDataObject& Data;
	GlobalDataObject& InputToScene;

	void Frame();
	void DrawThreaded();
	void Initialize();
	void SetProjectionMatrix(mat4&);
	void SetWindowHDC(HDC&);
private:
	void GenerateForm();

	void Draw_Units();
	void Draw_Scene();

	void DrawScene_Depth();
	void DrawScene_Refraction();
	void DrawScene_Reflection();
	void DrawScene_NoEffect();
	void DrawScene_PostProcessing();

	/*small functions*/
	void DrawEntities();
	void SetCameraView();
	void Shadow_DrawGround(Shader&);
	void Outline();
	void DrawSeaAnimated();
	void DrawColladaShadow();
	void Draw_Skeletal();
	void DrawUI();
	
	void DrawSky();
	void DrawGround(Shader&);
	void DrawSky(Shader&);
	void DrawSea();
	void DrawPreBuffer();
	void DrawCollada();
	void DrawWater();
	void DrawOutlineObjects();
	void DrawIndexColor();

	void DrawColladaDistance();
	
	Camera camera;
	Mouse mouse;
	mat4 ProjectionMatrix;
	mat4 ViewMatrix;
	HDC m_HDC;
	map<string, FBO> mFBO;
	FBO* IndexFBO;
	MultiSampleFBO mAntiAliasing;

	Model Soldier;
	Sea mSea;
	Shadow_Mapping *shadow;
	vec3 LightPosition = vec3(30,50,0);

	Loaded_Models loaded_Models;
	//SkyBox* skyBox;
	GLuint Channel;
	FPS fps;
	UserInterface& UI;
	Cursor cursor;
	ChampionChat* championChat;
	vector<Player> Players[2];
	Minimap minimap;
	vector<vec3> Obstacles;
	Grass grass;
	SeaAnimated seaAnim;
	vector<NPC> NPCs;
	vector<string> OutlineObjects;

	int counter = 0;
	//static GlobalDataObject Data;
	// develop this please
	//vector<Objects*> ObjectsToDraw
};


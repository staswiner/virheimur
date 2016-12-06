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
using namespace glm;
class Scene
{
public:
	//Scene() {}
	Scene(GlobalDataObject&,UserInterface&);
	~Scene();
	GlobalDataObject& Data;

	void Frame();
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
	void DrawScene_PostProcessing();

	/*small functions*/
	void DrawEntities();
	void SetCameraView();
	void Shadow_DrawGround(Shader&);
	void Draw_All_Units(Shader& shader);
	void DrawAllUnits();
	void Draw_Skeletal();
	void DrawUI();

	
	void DrawSky();
	void DrawGround(Shader&);
	void Draw2DObjects();
	void DrawSky(Shader&);
	void DrawSea();
	void DrawPreBuffer();
	void DrawCollada();
	
	Camera camera;
	Mouse mouse;
	mat4 ProjectionMatrix;
	mat4 ViewMatrix;
	HDC m_HDC;
	map<string, FBO> mFBO;
	MultiSampleFBO mAntiAliasing;

	Model Soldier;
	Sea mSea;
	Shadow_Mapping *shadow;
	vec3 LightPosition;

	Loaded_Models loaded_Models;
	SkyBox* skyBox;
	GLuint Channel;
	FPS fps;
	UserInterface& UI;
	Text text;
	ChampionChat* championChat;
	vector<GrassObjects*> m_GrassObjects;
	vector<Player> Players[2];
	Minimap minimap;
	vector<vec3> Obstacles;
	//static GlobalDataObject Data;
	// develop this please
	//vector<Objects*> ObjectsToDraw
};


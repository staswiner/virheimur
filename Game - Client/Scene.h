#pragma once
#include <map>
#include "Graphics_Header.h"
#include "FBO.h"
#include "Shader.h"
#include "ShaderBuilder.h"
#include "Camera.h"
#include "Sea.h"
#include "GameObject.h"
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
#include "NPC.h"
#include "Default.h"
#include "FrameData.h"
#include "Level.h"
#include "Music.h"
#include "XML.h"
using namespace glm;
class Scene
{
public:
	//Scene() {}
	Scene(UserInterface&,FBO* Index);
	~Scene();
	void* operator new(size_t size){
		return _mm_malloc(size, 16);
	}
	void operator delete(void* p){
		_mm_free(p);
	}
	
	void Frame();
	void Initialize();
	void SetWindowHDC(HDC&);
	Music* music;

private:
	void GenerateForm();
	void LoadForm(XML::Element & XML_Element, UIElement * uiElement);

	void Draw_Units();
	void Draw_Scene();

	void DrawScene_Depth();
	void DrawScene_Refraction();
	void DrawScene_Reflection();
	void DrawScene_NoEffect();
	
	/*small functions*/
	void Shadow_DrawGround(Shader&);
	void Outline();
	void DrawUI();

	void DrawOutlineObjects();
	void DrawIndexColor();

	HDC m_HDC;
	map<string, FBO> mFBO;
	FBO* IndexFBO;
	MultiSampleFBO mAntiAliasing;

	Sea mSea;
	Shadow_Mapping *shadow;

	//SkyBox* skyBox;
	GLuint Channel;
	FPS fps;
	UserInterface& UI;
	Cursor cursor;
	ChampionChat* championChat;
	Minimap minimap;
	vector<vec3> Obstacles;
	Grass grass;
	vector<NPC> NPCs;
	vector<string> OutlineObjects;
	int counter = 0;
	//static GlobalDataObject Data;
	// develop this please
	//vector<Objects*> ObjectsToDraw
};


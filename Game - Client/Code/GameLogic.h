#pragma once
#include "Ground_Collision.h"
#include "Camera.h"
#include "Graphics_Header.h"
//#include "tinyxml2.h"
//#include <msxml.h>
#include "RayCast.h"
#include "GameData.h"
#include "GlobalDataObject.h"
#include "InGameInteractions.h"
class GameLogic
{
public:
	GameLogic(GDO& Data);
	~GameLogic();
	void Proceed(GDO& NewData,mat4& ProjectionMatrix, mat4& ViewMatrix);
	void ChainCommands();
	void BuildData();
private:
	Keyboard keyboard;
	Mouse mouse;
	//GameData Data;
	GDO& Data;
	InGameInteractions inGameInteractions;


};


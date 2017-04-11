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
#include "FrameData.h"
#include <chrono>
__declspec(align(16)) class GameLogic
{
public:
	GameLogic(GDO& Data);
	~GameLogic();
	void* operator new(size_t size) {
		return _mm_malloc(size, 16);
	}
	void operator delete(void* p) {
		_mm_free(p);
	}

	void Proceed(GDO& NewData);
	void ProcessDataOffline();
	void ChainCommands();
	void BuildData();
private:
	void ProcessPlayerMovement();
	Keyboard keyboard;
	Mouse mouse;
	//GameData Data;
	GDO& Data;
	InGameInteractions inGameInteractions;
	Loaded_Models loaded_Models;


};


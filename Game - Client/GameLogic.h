#pragma once
#include <chrono>
//#include "tinyxml2.h"
//#include <msxml.h>
#include "Ground_Collision.h"
#include "Camera.h"
#include "Graphics_Header.h"
#include "RayCast.h"
#include "GameData.h"
#include "GlobalDataObject.h"
#include "InGameInteractions.h"
#include "FrameData.h"
#include "Time.h"

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
#define TODO_FUNCTION
	TODO_FUNCTION void CalculateCollision();
	TODO_FUNCTION void ProcessForces();
private:
	void ProcessPlayerMovement();
	//GameData Data;
	GDO& Data;
	InGameInteractions inGameInteractions;


};


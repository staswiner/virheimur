#pragma once
#include "UserInterface.h"
#include "Camera.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "RayCast.h"
#include "GlobalDataObject.h"
#include "PRMalgorithm.h"
#include "Loaded_Models.h"
#include "FBO.h"
#include <chrono>
using namespace std::chrono;
class Input
{
public:
	Input(GlobalDataObject&,UserInterface&,FBO* Index);
	~Input();
	void SetInitialCharacterData(GDO);
	GlobalDataObject& TranslateInput(GlobalDataObject& Data);
	Camera& GetCamera();
	Keyboard& GetKeyboard();
	Mouse& GetMouse();

private:
	void GetMouseInput();
	Camera camera;
	Keyboard keyboard;
	Mouse mouse;
	GlobalDataObject& ReceivedData;
	GlobalDataObject* Data;
	GlobalDataObject NewData;
	// the Interface object in focus 
	int Focus;
	int HoverFocus;
	UserInterface& UI;
	FBO* Index;
	Loaded_Models loaded_Models;
};


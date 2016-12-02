#pragma once
#include "UserInterface.h"
#include "Camera.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "RayCast.h"
#include "GlobalDataObject.h"
#include "PRMalgorithm.h"
class Input
{
public:
	Input(GlobalDataObject&,UserInterface&);
	~Input();
	void SetInitialCharacterData(GDO);
	GlobalDataObject& TranslateInput();
	Camera& GetCamera();
	Keyboard& GetKeyboard();
	Mouse& GetMouse();

private:
	void GetMouseInput();
	Camera camera;
	Keyboard keyboard;
	Mouse mouse;
	GlobalDataObject& Data;
	GlobalDataObject NewData;
	// the Interface object in focus 
	int Focus;
	int HoverFocus;
	UserInterface& UI;
};


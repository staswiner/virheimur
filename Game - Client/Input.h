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
#include "Session.h"
#include "Time.h"
#include <Windows.h>
#include <memory>
#include <sys/stat.h>
#include <sys/types.h>

using namespace std::chrono;

class Input
{
public:
	Input(GlobalDataObject&, UserInterface&, FBO* Index, GlobalDataObject&);
	~Input();
	void SetInitialCharacterData(GDO);
	GlobalDataObject& TranslateInput(GlobalDataObject& Data);
	GlobalDataObject & TranslateInputOffline(GlobalDataObject & Data);
	Keyboard& GetKeyboard();
	Mouse& GetMouse();

private:
	void GetMouseInput();
	void GetMouseInputOffline();
	void GetKeyboardInput();
	void OnlineRightMouseClick();
	void OfflineRightMouseClick();
	void SetCircleScript();
	void RunScript();
	void OpenProfileUI();
	void SetCircleScriptIterative();
	void SetPlayerControl(GameObject::controls control);
	void ManualControl();
	void DirectControl();
	vec3 GetMouseCoord_MapCoord();
	GlobalDataObject& ReceivedData;
	GlobalDataObject& InputToScene;
	GlobalDataObject* Data;
	GlobalDataObject NewData;
	// the Interface object in focus 
	int Focus;
	int HoverFocus;
	UserInterface& UI;
	FBO* Index;
	bool LeftWasPressed = false;
	void ResetCharacterPosition();
	void ResetCameraPosition();

private:
	// service functions
	void RightClickPathAlgorithm(vec3 ClickOnMapCoord);
};

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
	Input(UserInterface&, FBO* Index);
	~Input();
	void TranslateInputOffline();
	Keyboard& GetKeyboard();
	Mouse& GetMouse();

private:
	void GetMouseInput();
	void GetMouseInputOffline();
	void GetKeyboardInput();
	void ReloadShaders();
	void OfflineRightMouseClick();
	void SetCircleScript();
	void RunScript();
	void OpenProfileUI();
	void SetCircleScriptIterative();
	void SetPlayerControl(GameObject::controls control);
	void ManualControl();
	void DirectControl();
	void LockCamera();
	vec3 GetMouseCoord_MapCoord();
	// the Interface object in focus 
	int Focus;
	int HoverFocus;
	UserInterface& UI;
	FBO* Index;
	bool LeftWasPressed = false;
	void ResetCharacterPosition();
	void ResetCameraPosition();

	bool lockCamera = false;
};

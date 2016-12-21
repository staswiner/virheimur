#pragma once
#include "glm\glm\mat4x4.hpp"
#include "glm\glm\mat3x3.hpp"
#include "glm\glm\vec4.hpp"
#include "glm\glm\vec3.hpp"
#include "glm\glm\vec2.hpp"
#include "glm\glm\gtc\matrix_transform.hpp"
#include "Mouse.h"
#include "Keyboard.h"
#include "GL\freeglut.h"
#include <sstream>
#include <string>
#include <vector>
#include <map>

using namespace glm;
using namespace std;
class CameraStates;
class Camera
{
private:
	void WheelScroll();
	void MouseDrag();
	void MouseMove();
	void KeyboardInput();
	void CalculateCameraValues();
	mat4 CameraRotationMatrix();
	mat4 CameraRotationMatrix_z();
	mat4 CameraTranslationMatrix();
	/*time*/
	
	static unsigned int PreviousDelta;
	/*variables*/
	static vec3 CameraPosition;
	static vec3 CameraDestination;

	static vec3 MouseCameraAngle;
	static bool LeftIsPressed;
	static vec2 MouseHoldPosition;
	static vec2 LastSavedMouseOffset;

	mat4 ProjectionMatrix;
	CameraStates& cameraStates;
public:
	Camera();
	~Camera();
	mat4 GetUpdatedCamera();
	mat4 GetLockedCamera(vec3 PlayerPos, vec3 PlayerAngle);
	vec3 GetCameraPosition();
	vec3 GetCameraRotation();
	mat4 GetProjectionMatrix();
	void SetProjectionMatrix(mat4&);
	void SetCameraPosition(vec3);
	void InvertPitch();
	mat4 GetCameraMatrix();
	void ZoomInto(vec3 CameraPos, vec3 TargetPos);
	static void CalculateTimeDelta();


	static vec3 CameraPositionCalculated;
	static unsigned int Delta;
	/*static mat4 CameraRotation;
	static mat4 CameraTranslation;*/
	Mouse mouse;
	Keyboard keyboard;

	int Lock;

		
};

class CameraStates
{
private:
	CameraStates();
	~CameraStates();

	map<string, vector<string>> States;
	string Lock;
public:
	static CameraStates& Instance()
	{
		static CameraStates instance;
		return instance;
	}
	void SetState(string);
	bool IsInState(string);


};
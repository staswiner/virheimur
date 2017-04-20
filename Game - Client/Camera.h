#pragma once
#include "glm\glm\mat4x4.hpp"
#include "glm\glm\mat3x3.hpp"
#include "glm\glm\vec4.hpp"
#include "glm\glm\vec3.hpp"
#include "glm\glm\vec2.hpp"
#include "glm\glm\gtc\matrix_transform.hpp"
#include "Mouse.h"
#include "Keyboard.h"
#include "Default.h"
#include "GL\freeglut.h"
#include <sstream>
#include <string>
#include <vector>
#include <map>

using namespace glm;
using namespace std;
class CameraStates;
__declspec(align(16)) class Camera
{
private:
	Camera();
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
	vec3 CameraPosition;
	vec3 CameraDestination;

	vec3 MouseCameraAngle;
	static bool LeftIsPressed;
	static vec2 MouseHoldPosition;
	static vec2 LastSavedMouseOffset;

	mat4 ProjectionMatrix;
	CameraStates& cameraStates;
	static map<string, Camera*> Cameras;
public:
	~Camera();
	static Camera& GetCamera(string Name)
	{
		static map<string, Camera*> Cameras;
		if (Cameras.find(Name) == Cameras.end())
		{
			Cameras[Name] = new Camera();
		}
		return *Cameras[Name];
	}
	void ResetCamera();
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

	int Lock;
	// Core functions
	void* operator new(size_t size)
	{
		return _mm_malloc(size, 16);
	}
		
	void operator delete(void* p)
	{
		_mm_free(p);
	}
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
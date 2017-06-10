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
#include "Time.h"
#include <sstream>
#include <string>
#include <vector>
#include <map>

using namespace glm;
using namespace std;
class CameraStates;
__declspec(align(16)) class Camera
{
public:
	enum class eCamera
	{
		Current,
		Main,
		Custom
	};
private:
	Camera();
	void WheelScroll();
	void MouseDrag();
	void MouseMove();
	void KeyboardInput();
	void CalculateCameraValues();
	mat4 CameraRotationMatrix();
	mat4 CameraTranslationMatrix();
	/*time*/
	
	static unsigned int PreviousDelta;

	static bool LeftIsPressed;
	static vec2 MouseHoldPosition;
	static vec2 LastSavedMouseOffset;


	CameraStates& cameraStates;
	static map<eCamera, Camera*> Cameras;
public:
	
	~Camera();
	static Camera& GetCamera(eCamera Name)
	{
		static map<eCamera, Camera*> Cameras;
		if (Cameras.find(Name) == Cameras.end())
		{
			Cameras[Name] = new Camera();
		}
		return *Cameras[Name];
	}
	Camera& operator=(Camera&& rhs) noexcept
	{
		if (this != &rhs) { // no-op on self-move-assignment (delete[]/size=0 also ok)
			Lock = std::exchange(rhs.Lock,false);
			scale = rhs.scale;
			Position = rhs.Position;
			CameraDestination = rhs.CameraDestination;

			Rotation = rhs.Rotation;

			ProjectionMatrix = rhs.ProjectionMatrix;
			ViewMatrix = rhs.ViewMatrix;
		}
		return *this;
	}
	void ResetCamera();
	void SetCustomCameraValues(vec3 CameraPos, vec3 CameraRotation);
	mat4 GetUpdatedCamera();
	mat4 GetLockedCamera(vec3 PlayerPos, vec3 PlayerAngle);
	mat4 GetProjectionMatrix();
	void SetProjectionMatrix(mat4&);
	void InvertPitch();
	mat4 GetCameraMatrix();
	void ZoomInto(vec3 CameraPos, vec3 TargetPos);

	/*variables*/
	vec3 Position;
	vec3 CameraDestination;
	vec3 Rotation;
	mat4 ViewMatrix;
	mat4 ProjectionMatrix;

	int Lock;
	float scale = 1.0f;

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
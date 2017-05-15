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
	GameLogic();
	~GameLogic();
	void* operator new(size_t size) {
		return _mm_malloc(size, 16);
	}
	void operator delete(void* p) {
		_mm_free(p);
	}

	void Proceed();
	void ProcessDataOffline();
	void ChainCommands();
	void BuildData();
#define TODO_FUNCTION
	TODO_FUNCTION void CalculateCollision();
	void ProcessForces();

	// World Physics
	rp3d::CollisionWorld world;
	void RegisterCollisionBodies();
	void UpdateCollisionBodies();
	void CheckCollision();
private:
	void ProcessPlayerMovement();
	void ProcessMineDetection();
	//GameData Data;
	InGameInteractions inGameInteractions;

	union MyUnion
	{

	};
};
struct Velocity1 {
	int v;
};
#define MATH_LITERAL(name, function) \
constexpr long double operator"" name##(long double a) { function } \
constexpr unsigned long long int operator"" name##(unsigned long long int a) { function }

MATH_LITERAL(h, return 60.0f * a;);
MATH_LITERAL(min, return a;);
MATH_LITERAL(sec, return a / 60.0f;);

constexpr long double operator"" m(long double a) { return a; }
constexpr long double operator"" mps(long double a) { return a; }
constexpr long double operator"" cm(long double a) { return a / 100.0f; }
constexpr long double operator"" ²(long double a) { return a * a; }
constexpr unsigned long long int operator"" ²(unsigned long long int a) { return a * a; }
constexpr long double operator"" a(long double a) { return a; }
constexpr long double operator"" mm(long double a) { return a / 1000.0a; }


//Velocity1 operator"" _roy(unsigned long long int a) { Velocity1 v; v.v = a; return v; }
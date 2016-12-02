#pragma once
#include "Mouse.h"
#include "Graphics_Header.h"
#include "RayCast.h"
#include "Ground_Collision.h"
using namespace glm;
class InGameInteractions
{
private:
	Mouse mouse;
	Camera camera;
	vec3 Collision(vec3 WorldRay);
	vec3 InGameInteractions::GetCameraPosition();
	mat4 ProjectionMatrix;
	mat4 ViewMatrix;
public:
	InGameInteractions();
	~InGameInteractions();
	void Proceed(mat4& ProjectionMatrix,mat4& ViewMatrix);
};


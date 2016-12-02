#pragma once
#include "Mouse.h"
#include "glm\glm\vec3.hpp"
#include "glm\glm\vec4.hpp"
#include "glm\glm\mat4x4.hpp"
#include "glm\glm\mat3x3.hpp"
#include "glm\glm\gtc\matrix_inverse.hpp"
#include "glm\glm\vector_relational.hpp"
#include "glm\glm\geometric.hpp"
#include "Camera.h"
using namespace glm;
class RayCast
{
public:
	RayCast(mat4&, mat4&);
	~RayCast();

	vec3 GetWorldRay();
	vec3 PlaneIntersection(vec3 PlaneVec1, vec3 PlaneVec2, vec3 PlanePoint, vec3 Direction, vec3 CameraPos);
private:
	//vec3 GetCameraPosition();
	vec4 ClipToCoords();
	Mouse mouse;
	mat4 ProjectionMatrix;
	mat4 CameraMatrix;
};


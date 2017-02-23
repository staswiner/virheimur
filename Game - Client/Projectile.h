#pragma once
#include "GLM_Headers.h"
using namespace glm;
class Projectile
{
public:
	Projectile();
	~Projectile();

	float CreationTime;
	vec3 Start;
	vec3 End;
	vec3& BindEnd;

};


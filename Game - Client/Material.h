#pragma once
#include "Graphics_Header.h"

using namespace glm;

struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};
#pragma once
#include "glm\glm\vec3.hpp"
#include <stdlib.h>
using namespace glm;
class GrassObjects
{
public:
	GrassObjects();
	~GrassObjects();
	unsigned int m_StartTime;
	vec3 m_Position;
};


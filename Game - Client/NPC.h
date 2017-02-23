#pragma once
#include <string>
#include "GLM_Headers.h"
using namespace std;
using namespace glm;
class NPC
{
public:
	NPC();
	~NPC();
	string Name;
	int npcID;
	vec3 Position;
	vec3 Rotation;
};


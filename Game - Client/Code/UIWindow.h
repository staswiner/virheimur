#pragma once
#include "glm/glm/vec2.hpp"
using namespace glm;
class UIWindow
{
public:
	UIWindow();
	~UIWindow();
	int TargetID;
	vec2 LeftTop;
	vec2 RightBot;
};


#pragma once
#include "Maths.h"
#include "Loader.h"
#include <vector>
#include "glm\glm\vec3.hpp"
using namespace std;
using namespace glm;
class Ground_Collision
{
public:
	void SetGround(map<pair<int, int>, float>&);
	static Ground_Collision& Instance()
	{
		static Ground_Collision instance;
		return instance;
	}
	~Ground_Collision();
	vec3 Calculate_Ground_Collision(vec3);
private:
	Ground_Collision();
	map<pair<int, int>, float> mGroundHeights;
};


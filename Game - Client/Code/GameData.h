#pragma once
#include <vector>
#include <map>
#include "glm\glm\vec3.hpp"
using namespace glm;
using namespace std;
class GameData
{
private:
	struct Character
	{
		vec3 Position;

	};
public:
	GameData();
	~GameData();
	vector<Character> Characters;
};


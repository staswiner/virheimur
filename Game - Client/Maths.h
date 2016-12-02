#pragma once
#include <math.h>
#include <vector>
#include <map>
#include <utility>
#include <algorithm>
#include <list>
#include <set>

#include "GL\glew.h"
#include "glm\glm\vec2.hpp"
#include "glm\glm\vec3.hpp"
#include "glm\glm\vec4.hpp"
#include "glm\glm\mat4x4.hpp"
#include "glm\glm\gtc\matrix_transform.hpp"
using namespace glm;
using namespace std;
namespace Stas
{
	class Maths
	{
	public:
		Maths();
		~Maths();
		static float barryCentric(vec3, vec3, vec3, vec2);
		static float Mod(float, float);
		//static vector<vec3> Dijekstra(map<vec3,pair<vec3, float>> Nodes,vec3 Start,vec3 Destination);
		static vector<vec3>* Dijkstra(const map<vec3, map<vec3, int, bool(*)(const vec3&, const vec3&)>
			, bool(*)(const vec3&, const vec3&)> &graph, vec3 source, vec3 target);
		static vector<vec3>* Astar(const map<vec3, map<vec3, int, bool(*)(const vec3&, const vec3&)>
			, bool(*)(const vec3&, const vec3&)> &graph, vec3 source, vec3 target);
		static bool vec3Compare(const vec3&, const vec3&);
		static bool IsIn(vec2 TopLeft, vec2 BotRight, vec2 TestSample);
	};
}


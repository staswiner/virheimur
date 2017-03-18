#pragma once
#include <math.h>
#include <queue>
#include <vector>
#include <map>
#include <utility>
#include <algorithm>
#include <list>
#include <set>
#include <chrono>
#include <functional>

#include "GL\glew.h"
#include "glm\glm\vec2.hpp"
#include "glm\glm\vec3.hpp"
#include "glm\glm\vec4.hpp"
#include "glm\glm\mat4x4.hpp"
#include "glm\glm\gtc\matrix_transform.hpp"
using namespace glm;
using namespace std;
//#define (A) isInstanceOf(B) (dynamic_cast<A*>(B))
namespace Stas
{
	struct MinimapData
	{
		u8vec4* Map;
		int Width;
		int Height;
	};
	class Maths
	{
	public:
		Maths();
		~Maths();
		static float barryCentric(vec3, vec3, vec3, vec2);
		static float Mod(float, float);
		//static vector<vec3> Dijekstra(map<vec3,pair<vec3, float>> Nodes,vec3 Start,vec3 Destination);
		static vector<vec3> Dijkstra(const map<vec3, map<vec3, int, bool(*)(const vec3&, const vec3&)>
			, bool(*)(const vec3&, const vec3&)> &graph, vec3 source, vec3 target);
		//vector<vec3> DijkstraB(std::map<vec3, vector<vec3>, std::function<bool(const vec3&lhs, const vec3&rhs)>>
		//	&graph, vec3 source, vec3 target) = delete;
		static vector<vec3> Astar(const map<vec3, map<vec3, int, bool(*)(const vec3&, const vec3&)>
			, bool(*)(const vec3&, const vec3&)> &graph, vec3 source, vec3 target);
		static unsigned long long llrand();
		static bool vec3Compare(const vec3&, const vec3&);
		static bool IsIn(vec2 TopLeft, vec2 BotRight, vec2 TestSample);
		struct node {
			node(vec3 pos) {
				this->parent = nullptr;
				this->pos = pos;
				this->f = numeric_limits<float>::infinity();
				this->g = numeric_limits<float>::infinity();
				this->h = numeric_limits<float>::infinity();
				this->List = 0;
			}
			node() {
				this->parent = nullptr;
				this->f = numeric_limits<float>::infinity();
				this->g = numeric_limits<float>::infinity();
				this->h = numeric_limits<float>::infinity();
				this->List = 0;
			}
			vec3 pos;
			node *parent;
			float f, g, h;
			int List; // 0 none, 1 open, 2 closed
		};
		static vector<vec3> AstarGridB(MinimapData & minimapData, vec3 source, vec3 target);
	private:
		static vector<vec3> AstarB(
			std::map<vec3, pair<node*, vector<node*>>, std::function<bool(const vec3& lhs, const vec3& rhs)>>
			& graph, vec3 source, vec3 target);
		
	};

}


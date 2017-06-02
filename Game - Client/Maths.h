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
#include "Defines.h"
#include "glm\glm\vec2.hpp"
#include "glm\glm\vec3.hpp"
#include "glm\glm\vec4.hpp"
#include "glm\glm\mat4x4.hpp"
#include "glm\glm\gtc\matrix_transform.hpp"
#include "reactphysics3d.h"

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
		class Vectors {
		private:
			Vectors() = delete;
			~Vectors() = delete;
		public:
			struct Point
			{
				Point()
				{
					this->point = vec3(0); this->valid = false;
				}
				Point(vec3 Point, bool Valid)
				{
					this->point = Point;
					this->valid = Valid;
				}
				vec3 point;
				bool valid;
				operator vec3() {
					return this->point;
				}
			};
			struct Line {
				Line(vec3 Start, vec3 End, bool)
				{
					this->direction = End - Start;
					this->point = Start;
				}
				Line(vec3 Direction, vec3 Point)
				{
					this->direction = Direction;
					this->point = Point;
				}
				vec3 direction;
				vec3 point;
				bool valid;
			};
			struct Plane {
				Plane(vec3 Normal, vec3 Point)
				{
					this->normal = Normal;
					this->point = Point;
				}
				Plane(vec3 v1, vec3 v2, vec3 Point)
				{
					this->normal = cross(v1, v2);
					this->point = Point;
				}
				vec3 normal;
				vec3 point;
				bool valid;
			};
			struct Circle {
				vec3 Center;
				float radius;
				bool valid;
			};
			struct Sphere {
				vec3 Center;
				float radius;
				bool valid;
			};
			struct BoundryBox {
				vec3 Vertices[8];
				bool valid;
			};
			static Point IntersectionTwoLines(Line line1, Line line2);
			static Maths::Vectors::Point IntersectionPlaneLine(Plane plane1, Line line2);
			static Maths::Vectors::Point IntersectionPlanePoint(Plane plane, Point point);
			static void IntersectionTwoPlanes(Plane plane1, Plane plane2);
			static void IntersectionSpherePlane(Sphere circle1, Plane plane2);
			static void IntersectionSphereLine(Sphere circle1, Line line2);
			static Circle IntersectionTwoSpheres(Sphere circle1, Sphere circle2);
			static void IntersectionTwoBB(BoundryBox bb1, BoundryBox bb2);
			static float DistanceIntersectionTwoBB(BoundryBox bb1, BoundryBox bb2);
			/*		static void IntersectionBBSphere(Circle circle1, Circle circle2);
			static void IntersectionTwoSpheres(Circle circle1, Circle circle2);*/

		};
	public:
		static float barryCentric(vec3, vec3, vec3, vec2);
		static float Mod(float, float);
		//static vector<vec3> Dijekstra(map<vec3,pair<vec3, float>> Nodes,vec3 Start,vec3 Destination);
		static vector<vec3> Dijkstra(const map<vec3, map<vec3, float, bool(*)(const vec3&, const vec3&)>
			, bool(*)(const vec3&, const vec3&)> &graph, vec3 source, vec3 target);
		//vector<vec3> DijkstraB(std::map<vec3, vector<vec3>, std::function<bool(const vec3&lhs, const vec3&rhs)>>
		//	&graph, vec3 source, vec3 target) = delete;
		static vector<vec3> Astar(const map<vec3, map<vec3, float, bool(*)(const vec3&, const vec3&)>
			, bool(*)(const vec3&, const vec3&)> &graph, vec3 source, vec3 target);
		template<typename T>
		static vector<T> TSP(vector<T> UnorderedList);
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
		Maths() = delete;
		~Maths() = delete;

	};

	//namespace Algorithms
	//{
	//	class Approximate
	//	{
	//	public:
	//		// returns ordered TSP list O(n²)
	//		template<typename T>
	//		static vector<T> TSPgreedy(vector<T> UnorderedList);
	//		
	//	};
	//}
}
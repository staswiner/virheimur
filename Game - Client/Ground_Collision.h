#pragma once
#include "Maths.h"
#include "Collision.h"
#include <algorithm>
using namespace std;
using namespace glm;

class Ground_Collision : public Collision
{
public:
	// singletone examlpe
	using Collision::Collision;
	Ground_Collision();
	Ground_Collision(vector<Stas::Vertex> Vertices);
	/*static Ground_Collision& Instance()
	{
		static Ground_Collision instance;
		return instance;
	}*/
	~Ground_Collision();
	vec3 OnCollision(vec3 Position);
	vector<vec3> GetPlaneCoords(vec3 Index);

	vec3 GetNormalRotation(vec2);
	vec3 GetNormal(vec3);
private:
	map<vec2, float, bool(*)(const vec2&, const vec2&)> AlteredVertices;
	float FindCorrectTriangleHeight(vec2 Position);
	vector<vec3> FindCorrectTriangle(vec2 Position);
};

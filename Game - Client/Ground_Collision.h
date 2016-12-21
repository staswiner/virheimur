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
	Ground_Collision(vector<vec3> Vertices,vector<vec3> Normals);
	/*static Ground_Collision& Instance()
	{
		static Ground_Collision instance;
		return instance;
	}*/
	~Ground_Collision();
	vec3 OnCollision(vec3 Position);
	vector<vec3> GetPlaneCoords(vec3 Index);
private:
	map<vec2, float, bool(*)(const vec2&, const vec2&)>* AlteredVertices;
	vector<vec3> Normals;
};


#pragma once
#include "Maths.h"
#include "Collision.h"

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
private:
	map<pair<float, float>, float> AlteredVertices;
};


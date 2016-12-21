#pragma once
#include <vector>
#include <map>
#include "glm\glm\vec3.hpp"
#include "Structures.h"
using namespace std;
using namespace glm;
class Collision
{
public:
	Collision();
	explicit Collision(vector<vec3> Vertices);
	~Collision();

	virtual bool InCollision(vec3 Position);
	virtual vec3 OnCollision(vec3 Position);
	virtual vector<vec3> GetPlaneCoords(vec3);

protected:
	vector<vec3> Vertices;

};


#include "Collision.h"



Collision::Collision()
{
}


Collision::Collision(vector<vec3> Vertices)
{
	this->Vertices = Vertices;
}

Collision::~Collision()
{
}

bool Collision::InCollision(vec3 Position)
{
	return false;
}

vec3 Collision::OnCollision(vec3 Position)
{
	return vec3();
}

vector<vec3> Collision::GetPlaneCoords(vec3)
{
	return vector<vec3>();
}

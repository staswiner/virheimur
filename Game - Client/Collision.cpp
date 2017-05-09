#include "Collision.h"



Collision::Collision()
{
}


//Collision::Collision(vector<Stas::Vertex> Vertices)
//{
//	this->Vertices = Vertices;
//}

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

vec3 Collision::GetNormalRotation(vec2)
{
	return vec3();
}

vec3 Collision::GetNormal(vec3)
{
	return vec3();
}

vector<vec3> Collision::GetCollisionPath(vec3, vec3)
{
	return vector<vec3>();
}

vector<Stas::Vertex>& Collision::GetVertices()
{
	return this->Vertices;
}

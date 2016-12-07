#include "Collision.h"



Collision::Collision()
{
}


Collision::Collision(vector<Stas::Vertex> Vertices)
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

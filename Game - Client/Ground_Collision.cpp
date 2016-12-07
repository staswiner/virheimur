#include "Ground_Collision.h"


Ground_Collision::Ground_Collision()
{

}

Ground_Collision::Ground_Collision(vector<Stas::Vertex> Vertices)
{
	for (auto v : Vertices)
	{
		AlteredVertices[make_pair(v.Position.x,v.Position.y)] = v.Position.y;
	}
}

Ground_Collision::~Ground_Collision()
{
}
vec3 Ground_Collision::OnCollision(vec3 CurrentPosition)
{
	vec3 UnitPosition = CurrentPosition;
	float Delta = AlteredVertices.begin()->first.first-(++AlteredVertices.begin())->first.first;

	vec3 InTriangle = vec3(Stas::Maths::Mod(UnitPosition.x, 20.0f), 0, Stas::Maths::Mod(UnitPosition.z, 20.0f));
	vec3 TriangleCoord0 = UnitPosition;
	vec3 TriangleCoord1 = UnitPosition;
	vec3 TriangleCoord2 = vec3(UnitPosition.x + 20.0f, 0, UnitPosition.z + 20.0f);
	if (InTriangle.x > 1.0 - InTriangle.z)
		TriangleCoord1.x += 20.0f;
	else
		TriangleCoord1.z += 20.0f;
	TriangleCoord0.y = AlteredVertices.lower_bound(make_pair(UnitPosition.x, UnitPosition.z))->second;
	TriangleCoord1.y = AlteredVertices.lower_bound(make_pair(UnitPosition.x+ Delta, UnitPosition.z))->second;
	TriangleCoord2.y = AlteredVertices.lower_bound(make_pair(UnitPosition.x, UnitPosition.z + Delta))->second;

	UnitPosition.y = Stas::Maths::barryCentric(TriangleCoord0, TriangleCoord1, TriangleCoord2, vec2(UnitPosition.x, UnitPosition.z));


	return UnitPosition;
}
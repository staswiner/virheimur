#include "Ground_Collision.h"
bool vec2compare(const vec2& lhs, const vec2& rhs)
{
	if (lhs.x == rhs.x)
	{
		return lhs.y < rhs.y;
	}
	return lhs.x < rhs.x;
}


Ground_Collision::Ground_Collision()
{

}

Ground_Collision::Ground_Collision(vector<vec3> Vertices,vector<vec3> Normals)
{
	AlteredVertices = new map<vec2, float, bool(*)(const vec2&, const vec2&)>(vec2compare);
	this->Vertices = Vertices;
	this->Normals = Normals;
	/*	[](const vec2& lhs, const vec2& rhs)->bool {
	if (lhs.x == rhs.x)
	{
		return lhs.y < rhs.y;
	}
	return lhs.x < rhs.x; });*/
	// Requires 1 element
	// ran, 0508250510
	for (auto v : Vertices)
	{
		vec2 NewEntry = vec2(int(v.x / 2) * 2, int(v.z / 2) * 2);
	//		NewEntry.x = int(NewEntry.x)/1;
		(*AlteredVertices)[NewEntry] = v.y;
		// Test if value has unnecesary offset
	}
}


Ground_Collision::~Ground_Collision()
{
}

vec3 Ground_Collision::OnCollision(vec3 CurrentPosition)
{
	vec3 UnitPosition = CurrentPosition;
	float Delta = 0.1f;// AlteredVertices.begin()->first.first - (++AlteredVertices.begin())->first.first;
	vec3 RoundedValues(int(UnitPosition.x / 2) * 2, int(UnitPosition.y / 2) * 2, int(UnitPosition.z / 2) * 2);
	vec3 InTriangle = vec3(Stas::Maths::Mod(UnitPosition.x, Delta), 0, Stas::Maths::Mod(UnitPosition.z, Delta));
	vec3 TriangleCoord0 = RoundedValues;
	vec3 TriangleCoord1 = RoundedValues + vec3(0, 0, 2);
	vec3 TriangleCoord2 = RoundedValues + vec3(2, 0, 0);
	
	if (auto it = AlteredVertices->find(vec2(TriangleCoord0.x, TriangleCoord0.z)) == AlteredVertices->end())
	{
		int i = 0;
	}
	//auto it = AlteredVertices->lower_bound(vec2(TriangleCoord0.x,TriangleCoord0.z));
	TriangleCoord0.y = AlteredVertices->find(vec2(TriangleCoord0.x, TriangleCoord0.z)) != AlteredVertices->end() 
		? AlteredVertices->at(vec2(TriangleCoord0.x, TriangleCoord0.z)) : 0;
	TriangleCoord1.y = AlteredVertices->find(vec2(TriangleCoord1.x, TriangleCoord1.z)) != AlteredVertices->end()
		? AlteredVertices->at(vec2(TriangleCoord1.x, TriangleCoord1.z)) : 0;
	TriangleCoord2.y = AlteredVertices->find(vec2(TriangleCoord2.x, TriangleCoord2.z)) != AlteredVertices->end()
		? AlteredVertices->at(vec2(TriangleCoord2.x, TriangleCoord2.z)) : 0;
	//if (InTriangle.x > 1.0 - InTriangle.z)
	//	TriangleCoord1.x += Delta;
	//else
	//	TriangleCoord1.z += Delta;
	//if ()
	/*auto top = AlteredVertices->lower_bound(vec2(TriangleCoord0.x, TriangleCoord0.z));
	auto bottom = AlteredVertices->upper_bound(vec2(TriangleCoord0.x-5, TriangleCoord0.z));
	map<vec2,float,bool (*)(const vec2&, const vec2&)> vRange(bottom, top,
		[](const vec2& lhs, const vec2& rhs)->bool
	{return lhs.y < rhs.y; });
	if (vRange.size() != 0)
	{
		auto it = vRange.lower_bound(vec2(TriangleCoord0.x, TriangleCoord0.z));
		TriangleCoord0.y = it->second;
	}
	else
	{
		TriangleCoord0.y = top->second;
	}*/
	//auto it = range.upper_bound(vec2(TriangleCoord0.x, TriangleCoord0.z));
	//TriangleCoord0.y = it->second;
	//TriangleCoord1.y = AlteredVertices.lower_bound(vec2(TriangleCoord1.x, TriangleCoord1.z))->second;
	//TriangleCoord2.y = AlteredVertices.lower_bound(vec2(TriangleCoord2.x, TriangleCoord2.z))->second;
	//TriangleCoord1.y = AlteredVertices.lower_bound(vec2(UnitPosition.x+ Delta, UnitPosition.z))->second;
	//TriangleCoord2.y = AlteredVertices.lower_bound(vec2(UnitPosition.x, UnitPosition.z + Delta))->second;

	UnitPosition.y = Stas::Maths::barryCentric(TriangleCoord0, TriangleCoord1, TriangleCoord2, vec2(UnitPosition.x, UnitPosition.z));


	return UnitPosition;
}

vector<vec3> Ground_Collision::GetPlaneCoords(vec3 Index)
{
	vector<vec3> ReturnPlane;
	// 1st vector of the plane
	// second vector of the plane
	// point on the plane
	//if (Vertices.size() > Index.x && Index.x > 0)
	{
		ReturnPlane.push_back(Vertices[Index.x]- Vertices[Index.y]);
		ReturnPlane.push_back(Vertices[Index.z]- Vertices[Index.y]);
		ReturnPlane.push_back(Vertices[Index.x]);
	
	}
	/*else
	{
		ReturnPlane.push_back(vec3(1, 0, 0));
		ReturnPlane.push_back(vec3(0, 0, 1));
		ReturnPlane.push_back(vec3(0, 0, 0));
	}*/
	return ReturnPlane;
}
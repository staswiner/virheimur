#include "Ground_Collision.h"

Ground_Collision::Ground_Collision()
{

}

Ground_Collision::Ground_Collision(vector<Stas::Vertex> Vertices)
{
	AlteredVertices = map<vec2, float, bool(*)(const vec2&, const vec2&)>([](const vec2& lhs, const vec2& rhs)->bool {
		if (lhs.x >= (rhs.x - 0.001f) && lhs.x <= (rhs.x + 0.001f))
		{
			return lhs.y < rhs.y;
		}
		return lhs.x < rhs.x;
	});
	
	this->Vertices = Vertices;
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
		//vec2 NewEntry = vec2(int(v.Position.x / 2) * 2, int(v.Position.z / 2) * 2);
	//		NewEntry.x = int(NewEntry.x)/1;
		AlteredVertices[v.Position.xy] = v.Position.z;
		// Test if value has unnecesary offset
	}
}


Ground_Collision::~Ground_Collision()
{
}

vec3 Ground_Collision::OnCollision(vec3 CurrentPosition)
{
	vec3 UnitPosition = CurrentPosition;
	float Height = FindCorrectTriangle(CurrentPosition.xz);
	UnitPosition.y = Height;
	//if (auto it = AlteredVertices->find(vec2(TriangleCoord0.x, TriangleCoord0.z)) == AlteredVertices->end())
	//{
	//	int i = 0;
	//}
	//TriangleCoord0.y = AlteredVertices->lower_bound(vec2(TriangleCoord0.x, TriangleCoord0.z))->second;
	////auto it = AlteredVertices->lower_bound(vec2(TriangleCoord0.x,TriangleCoord0.z));
	//TriangleCoord0.y = AlteredVertices->find(vec2(TriangleCoord0.x, TriangleCoord0.z)) != AlteredVertices->end() 
	//	? AlteredVertices->at(vec2(TriangleCoord0.x, TriangleCoord0.z)) : 0;
	//TriangleCoord1.y = AlteredVertices->find(vec2(TriangleCoord1.x, TriangleCoord1.z)) != AlteredVertices->end()
	//	? AlteredVertices->at(vec2(TriangleCoord1.x, TriangleCoord1.z)) : 0;
	//TriangleCoord2.y = AlteredVertices->find(vec2(TriangleCoord2.x, TriangleCoord2.z)) != AlteredVertices->end()
	//	? AlteredVertices->at(vec2(TriangleCoord2.x, TriangleCoord2.z)) : 0;

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

	//UnitPosition.y = Stas::Maths::barryCentric(TriangleCoord0, TriangleCoord1, TriangleCoord2, vec2(UnitPosition.x, UnitPosition.z));


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
		ReturnPlane.push_back(Vertices[Index.x].Position- Vertices[Index.y].Position);
		ReturnPlane.push_back(Vertices[Index.z].Position- Vertices[Index.y].Position);
		ReturnPlane.push_back(Vertices[Index.x].Position);
	
	}

	/*else
	{
		ReturnPlane.push_back(vec3(1, 0, 0));
		ReturnPlane.push_back(vec3(0, 0, 1));
		ReturnPlane.push_back(vec3(0, 0, 0));
	}*/
	return ReturnPlane;
}

vec3 Ground_Collision::GetNormalRotation(vec3 CurrentPosition)
{
	vec3 UnitPosition = CurrentPosition;
	float Delta = 0.1f;// AlteredVertices.begin()->first.first - (++AlteredVertices.begin())->first.first;
	vec3 RoundedValues(int(UnitPosition.x / 2) * 2, int(UnitPosition.y / 2) * 2, int(UnitPosition.z / 2) * 2);

	vec3 TriangleCoord0 = RoundedValues;
	vec3 TriangleCoord1 = RoundedValues + vec3(0, 0, 2);
	vec3 TriangleCoord2 = RoundedValues + vec3(2, 0, 0);

	//if (auto it = AlteredVertices->find(vec2(TriangleCoord0.x, TriangleCoord0.z)) == AlteredVertices->end())
	//{
	//	int i = 0;
	//}
	////auto it = AlteredVertices->lower_bound(vec2(TriangleCoord0.x,TriangleCoord0.z));
	//TriangleCoord0.y = AlteredVertices->find(vec2(TriangleCoord0.x, TriangleCoord0.z)) != AlteredVertices->end()
	//	? AlteredVertices->at(vec2(TriangleCoord0.x, TriangleCoord0.z)) : 0;
	//TriangleCoord1.y = AlteredVertices->find(vec2(TriangleCoord1.x, TriangleCoord1.z)) != AlteredVertices->end()
	//	? AlteredVertices->at(vec2(TriangleCoord1.x, TriangleCoord1.z)) : 0;
	//TriangleCoord2.y = AlteredVertices->find(vec2(TriangleCoord2.x, TriangleCoord2.z)) != AlteredVertices->end()
	//	? AlteredVertices->at(vec2(TriangleCoord2.x, TriangleCoord2.z)) : 0;

	//vec3 TriangleNormal = cross(TriangleCoord0 - TriangleCoord1, TriangleCoord0 - TriangleCoord2);
	//vec3 NormalAngle = vec3(
	//	sqrt(TriangleNormal.x*TriangleNormal.x + TriangleNormal.y*TriangleNormal.y + TriangleNormal.z*TriangleNormal.z),
	//	atan(TriangleNormal.y / TriangleNormal.x),
	//	acos(TriangleNormal.z)
	//);
	vec3 NormalAngle; // delete
	return NormalAngle;
}

float Ground_Collision::FindCorrectTriangle(vec2 Position) // fix to 1 triangle back
{
	float unitDifference = abs(AlteredVertices.begin()->first.y - (++AlteredVertices.begin())->first.y);
	Position = vec2(Position.x,-Position.y);
	vec2 PositionLow = Position - vec2(unitDifference);

	vec2 PositionDownRight = PositionLow + vec2(unitDifference);
	vec2 PositionDownLeft = PositionLow + vec2(0,unitDifference);
	vec2 PositionUpRight = PositionLow + vec2(unitDifference,0);
	vec2 PositionUpLeft = PositionLow;
	
	vec2 xPositionDownRight = AlteredVertices.lower_bound(PositionDownRight)->first;
	vec2 xPositionDownLeft = AlteredVertices.lower_bound(PositionDownLeft)->first;
	vec2 xPositionUpRight = AlteredVertices.lower_bound(PositionUpRight)->first;
	vec2 xPositionUpLeft = AlteredVertices.lower_bound(PositionUpLeft)->first;

	vec2 yPositionDownRight = AlteredVertices.lower_bound(vec2(xPositionDownRight.x, PositionDownRight.y))->first;
	vec2 yPositionDownLeft = AlteredVertices.lower_bound(vec2(xPositionDownLeft.x, PositionDownLeft.y))->first;
	vec2 yPositionUpRight = AlteredVertices.lower_bound(vec2(xPositionUpRight.x, PositionUpRight.y))->first;
	vec2 yPositionUpLeft = AlteredVertices.lower_bound(vec2(xPositionUpLeft.x, PositionUpLeft.y))->first;

	float yRightDown	= AlteredVertices.lower_bound(yPositionDownRight)->second;
	float yLeftDown		= AlteredVertices.lower_bound(yPositionDownLeft)->second;
	float yRightUp		= AlteredVertices.lower_bound(yPositionUpRight)->second;
	float yLeftUp		= AlteredVertices.lower_bound(yPositionUpLeft)->second;

	vec3 PositionDownRight3	(yPositionDownRight.x,	yRightDown,		yPositionDownRight.y);
	vec3 PositionDownLeft3	(yPositionDownLeft.x,	yLeftDown,		yPositionDownLeft.y);
	vec3 PositionUpRight3	(yPositionUpRight.x,	yRightUp,		yPositionUpRight.y);
	vec3 PositionUpLeft3	(yPositionUpLeft.x,		yLeftUp,		yPositionUpLeft.y);

	vec2 DifferenceFromStart = Position - yPositionUpLeft;
	float Height;
	if (DifferenceFromStart.x + DifferenceFromStart.y < unitDifference)
	{
		// left top
		Height = Stas::Maths::barryCentric(PositionUpLeft3, PositionUpRight3, PositionDownLeft3, Position);
	}
	else
	{
		// right down
		Height = Stas::Maths::barryCentric(PositionDownLeft3, PositionDownRight3, PositionUpRight3, Position);
	}
	// if Nan
	return Height;
}

/*
15,25
--
10 10
10 20
*
10 30
20 10
20 20
20 30
30 10
30 20
30 30
*/


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
// Returns Height between Current Position.xz
vec3 Ground_Collision::OnCollision(vec3 CurrentPosition)
{
	vec3 UnitPosition = CurrentPosition;
	float Height = FindCorrectTriangleHeight(CurrentPosition.xz);
	UnitPosition.y = Height;

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

vec3 Ground_Collision::GetNormalRotation(vec2 Position)
{
	Position = vec2(Position.x, -Position.y);
	vector<vec3> Triangle = FindCorrectTriangle(Position);

	vec3 TriangleNormal = cross(Triangle[0] - Triangle[1], Triangle[0] - Triangle[2]);
	TriangleNormal = Triangle[0] - Triangle[1];
	float x = sqrt(TriangleNormal.x*TriangleNormal.x + TriangleNormal.y*TriangleNormal.y + TriangleNormal.z*TriangleNormal.z);
	float y = atan(TriangleNormal.y / TriangleNormal.x);
	float z = acos(TriangleNormal.z / x);
	vec3 NormalAngle = vec3(x,y,z);
	return NormalAngle;
}

vec3 Ground_Collision::GetNormal(vec3 Position)
{
	vector<vec3> Triangle = FindCorrectTriangle(vec2(Position.x, -Position.z));

	vec3 TriangleNormal = normalize(cross(Triangle[0] - Triangle[1], Triangle[0] - Triangle[2]));
	return TriangleNormal;
}

vector<vec3> Ground_Collision::GetCollisionPath(vec3 Position, vec3 PreviousPosition)
{
	float unitDifference = abs(AlteredVertices.begin()->first.y - (++AlteredVertices.begin())->first.y);
	vec3 Direction = Position - PreviousPosition; // Direction towards Position
	vector<vec3> CollisionPath;
	for (vec3 pos = PreviousPosition; dot(pos-Position,pos-PreviousPosition) > 0; pos+=(unitDifference * normalize(Direction)))
	{
		CollisionPath.push_back(OnCollision(pos));
	}
	return CollisionPath;
}

float Ground_Collision::FindCorrectTriangleHeight(vec2 Position) // fix to 1 triangle back
{
	Position = vec2(Position.x, -Position.y);

	vector<vec3> CorrectTriangle = FindCorrectTriangle(Position);
	float Height;

	Height = Stas::Maths::barryCentric(CorrectTriangle[0], CorrectTriangle[1],
		CorrectTriangle[2], Position);
	// if Nan
	return Height;
}

vector<vec3> Ground_Collision::FindCorrectTriangle(vec2 Position)
{
	float unitDifference = abs(AlteredVertices.begin()->first.y - (++AlteredVertices.begin())->first.y);
	vec2 PositionLow = Position - vec2(unitDifference);

	vec2 PositionDownRight = PositionLow + vec2(unitDifference);
	vec2 PositionDownLeft = PositionLow + vec2(0, unitDifference);
	vec2 PositionUpRight = PositionLow + vec2(unitDifference, 0);
	vec2 PositionUpLeft = PositionLow;

	vec2 xPositionDownRight = AlteredVertices.lower_bound(PositionDownRight)->first;
	vec2 xPositionDownLeft = AlteredVertices.lower_bound(PositionDownLeft)->first;
	vec2 xPositionUpRight = AlteredVertices.lower_bound(PositionUpRight)->first;
	vec2 xPositionUpLeft = AlteredVertices.lower_bound(PositionUpLeft)->first;

	vec2 yPositionDownRight = AlteredVertices.lower_bound(vec2(xPositionDownRight.x, PositionDownRight.y))->first;
	vec2 yPositionDownLeft = AlteredVertices.lower_bound(vec2(xPositionDownLeft.x, PositionDownLeft.y))->first;
	vec2 yPositionUpRight = AlteredVertices.lower_bound(vec2(xPositionUpRight.x, PositionUpRight.y))->first;
	vec2 yPositionUpLeft = AlteredVertices.lower_bound(vec2(xPositionUpLeft.x, PositionUpLeft.y))->first;

	float yRightDown = AlteredVertices.lower_bound(yPositionDownRight)->second;
	float yLeftDown = AlteredVertices.lower_bound(yPositionDownLeft)->second;
	float yRightUp = AlteredVertices.lower_bound(yPositionUpRight)->second;
	float yLeftUp = AlteredVertices.lower_bound(yPositionUpLeft)->second;

	vec3 PositionDownRight3(yPositionDownRight.x, yRightDown, yPositionDownRight.y);
	vec3 PositionDownLeft3(yPositionDownLeft.x, yLeftDown, yPositionDownLeft.y);
	vec3 PositionUpRight3(yPositionUpRight.x, yRightUp, yPositionUpRight.y);
	vec3 PositionUpLeft3(yPositionUpLeft.x, yLeftUp, yPositionUpLeft.y);

	vec2 DifferenceFromStart = Position - yPositionUpLeft;
	vector<vec3> ReturnTriangle;
	if (DifferenceFromStart.x + DifferenceFromStart.y < unitDifference)
	{
		// left top
		ReturnTriangle = { PositionUpLeft3, PositionUpRight3, PositionDownLeft3 };
	}
	else
	{
		// right down
		ReturnTriangle = { PositionDownLeft3, PositionDownRight3, PositionUpRight3 };
	}
	return ReturnTriangle;
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


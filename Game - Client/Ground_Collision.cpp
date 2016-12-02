#include "Ground_Collision.h"


Ground_Collision::Ground_Collision()
{

}

void Ground_Collision::SetGround(map<pair<int, int>, float>& GroundHeights)
{
	this->mGroundHeights = GroundHeights;
}


Ground_Collision::~Ground_Collision()
{
}
vec3 Ground_Collision::Calculate_Ground_Collision(vec3 CurrentPosition)
{
	vec3 UnitPosition = CurrentPosition;
	if (UnitPosition.x < -1000.0f || UnitPosition.x > 1000.0f || UnitPosition.z < -1000.0f || UnitPosition.z > 1000.0f)
	{
		return vec3();
	}
	vec3 Rounded_UnitPosition = vec3(UnitPosition.x - Stas::Maths::Mod(UnitPosition.x, 20.0f), 0, UnitPosition.z - Stas::Maths::Mod(UnitPosition.z, 20.0f));

	vec3 InTriangle = vec3(Stas::Maths::Mod(UnitPosition.x, 20.0f), 0, Stas::Maths::Mod(UnitPosition.z, 20.0f));
	vec3 TriangleCoord0 = Rounded_UnitPosition;
	vec3 TriangleCoord1 = Rounded_UnitPosition;
	vec3 TriangleCoord2 = vec3(Rounded_UnitPosition.x + 20.0f, 0, Rounded_UnitPosition.z + 20.0f);
	if (InTriangle.x > 1.0 - InTriangle.z)
		TriangleCoord1.x += 20.0f;
	else
		TriangleCoord1.z += 20.0f;
	TriangleCoord0.y = mGroundHeights.find(pair<int, int>((int)TriangleCoord0.x, (int)TriangleCoord0.z))->second;
	TriangleCoord1.y = mGroundHeights.find(pair<int, int>((int)TriangleCoord1.x, (int)TriangleCoord1.z))->second;
	TriangleCoord2.y = mGroundHeights.find(pair<int, int>((int)TriangleCoord2.x, (int)TriangleCoord2.z))->second;

	UnitPosition.y = Stas::Maths::barryCentric(TriangleCoord0, TriangleCoord1, TriangleCoord2, vec2(UnitPosition.x, UnitPosition.z));


	// water
	if (UnitPosition.y < 0.0f)
		UnitPosition.y = 0.0f;
	return UnitPosition;
}
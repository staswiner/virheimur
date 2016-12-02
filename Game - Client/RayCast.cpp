#include "RayCast.h"



RayCast::RayCast(mat4& ProjectionMatrix, mat4& CameraMatrix)
{
	this->ProjectionMatrix = ProjectionMatrix;
	this->CameraMatrix = CameraMatrix;
}


RayCast::~RayCast()
{
}
vec3 RayCast::GetWorldRay()
{
	mat4 iCameraMat = inverse(CameraMatrix);
	mat4 iProjectionMat = inverse(ProjectionMatrix);
	vec4 toEye = inverse(ProjectionMatrix) * ClipToCoords();
	toEye = vec4(toEye.x, toEye.y, -1.0f, 0.0f);
	vec4 WorldRay4 = inverse(CameraMatrix) * toEye;
	vec3 WorldRay(WorldRay4);
	WorldRay = normalize(WorldRay);
	return WorldRay;
}
//vec3 RayCast::GetCameraPosition()
//{
//	Camera camera;
//	vec3 CameraPosition = camera.GetCameraPosition();
//	vec3 CameraRotation = camera.GetCameraRotation();
//	/*********/
//	vec4 CameraPositionTransformed = inverse(CameraMatrix) * inverse(ProjectionMatrix) * 
//		vec4(CameraPosition, 1.0f);
//	CameraPositionTransformed /= CameraPositionTransformed.w;
//	CameraPosition = vec3(CameraPositionTransformed);
//	return CameraPosition;
//}
vec3 RayCast::PlaneIntersection(vec3 PlaneVec1, vec3 PlaneVec2, vec3 PlanePoint, vec3 direction, vec3 CameraPos)
{
	CameraPos *= -1;
	vec3 PlaneNormal = glm::cross(PlaneVec1, PlaneVec2);
	float D = (glm::dot(PlanePoint - CameraPos,PlaneNormal) / (glm::dot(direction,PlaneNormal)));
	vec3 Intersection = D*direction + CameraPos;
	return Intersection;


		/* get camera position in worldspace (goes under projection and camera matrices )*/
		//vec3 CameraPositionInWorldSpace = GetCameraPosition();
		///* gets interaction between worldray and y = 0 surface */
		//float scaler = CameraPositionInWorldSpace.y / direction.y;
		//return (CameraPositionInWorldSpace - direction * scaler);


	/*float CameraDistanceFromPlane;
	this->CameraMatrix;
	vec3 CameraPosition;*/
	//vec3 PointOnPlane = PlaneVec1 + (PlaneVec2 - PlaneVec1)
	//float n1, n2, n3;
	//vec3 l1, l2, pp, cp, d;
	////PlaneVec1.x * n1 + PlaneVec2.x * n2 + PlanePoint.x = CameraPos.x + direction.x * n3;
	////PlaneVec1.y * n1 + PlaneVec2.y * n2 + PlanePoint.y = CameraPos.y + direction.y * n3;
	////PlaneVec1.z * n1 + PlaneVec2.z * n2 + PlanePoint.z = CameraPos.z + direction.z * n3;
	//#define dn1 ((CameraPos.x + direction.x*n3 - PlaneVec2.x*dn2 - PlanePoint.x) / PlaneVec1.x)
	//#define dn2 ((l1.x / (-l1.y*l2.x + l2.y*l1.x)) * (l1.x*((cp.y + d.y*n3 + pp.y) - 
	//l1.y*(cp.x + d.x*n3 - pp.x)) / l1.x))
	////PlaneVec1.y * ((CameraPos.x + direction.x*n3 - PlaneVec2.x*dn2 - PlanePoint.x) / PlaneVec1.x)
	////	+ PlaneVec2.y * n2 + PlanePoint.y = CameraPos.y + direction.y * n3;
	////(CameraPos.y + direction.y * n3 - PlaneVec2.y * n2 - pp.y) * l1.x ;
	//n3 * d.z = cp.z - pp.z;
	//l1.z * ((CameraPos.x + direction.x*n3 - PlaneVec2.x*((l1.x / ((-l1.y*l2.x + l2.y*l1.x)) * (l1.x*((cp.y + d.y*n3 + pp.y)) -
	//	l1.y*(cp.x + d.x*n3 - pp.x)) / l1.x)) - PlanePoint.x) / PlaneVec1.x) + l2 * ((l1.x / (-l1.y*l2.x + l2.y*l1.x)) * (l1.x*((cp.y + d.y*n3 + pp.y) -
	//	l1.y*(cp.x + d.x*n3 - pp.x)) / l1.x)) + pp.z = cp.z + d.z * n3;
	//l1.z * (cp.x +d.x*n3-l2.x*())


}
vec4 RayCast::ClipToCoords()
{
	float wX = mouse.GetWindowSize().x;
	float wY = mouse.GetWindowSize().y;
	float x = (2.0f * mouse.GetMouseX()) / mouse.GetWindowSize().x - 1.0f;
	float y = (2.0f * mouse.GetMouseY()) / mouse.GetWindowSize().y - 1.0f;
	y *= -1;
	vec4 RayClipped = vec4(x, y, -1.0, 1.0);
	return RayClipped;
}
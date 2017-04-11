#include "InGameInteractions.h"



InGameInteractions::InGameInteractions()
{
}


InGameInteractions::~InGameInteractions()
{
}

void InGameInteractions::Proceed(mat4& ProjectionMatrix, mat4& ViewMatrix)
{
	this->ProjectionMatrix = ProjectionMatrix;
	this->ViewMatrix = ViewMatrix;
	if (mouse.RightIsPressed())
	{
		vec3 WorldRay = RayCast(ProjectionMatrix, ViewMatrix).GetWorldRay();
		vec3 Destination = Collision(WorldRay);
		//Ground_Collision& groundCollision = Ground_Collision::Instance();
		//vec3 GroundDestination = groundCollision.OnCollision(Destination);
		//m_Unit_Data[Channel][0].SetPosition(GroundDestination);
	}
}
vec3 InGameInteractions::Collision(vec3 WorldRay)
{
	///*----------Camera---------*/	
	/// intercaction
	WorldRay = RayCast(ProjectionMatrix, ViewMatrix).GetWorldRay();
	vec3 mapUp(0, 0, 1);
	vec3 mapRight(1, 0, 0);
	vec3 mapProduct = glm::cross(mapUp, mapRight);
	/* get camera position in worldspace (goes under projection and camera matrices )*/
	vec3 CameraPositionInWorldSpace = GetCameraPosition();
	/* gets interaction between worldray and y = 0 surface */
	float scaler = CameraPositionInWorldSpace.y / WorldRay.y;
	return (CameraPositionInWorldSpace - WorldRay * scaler);
}
vec3 InGameInteractions::GetCameraPosition()
{
	Camera& camera = Camera::GetCamera("Main");

	vec3 CameraPosition = camera.GetCameraPosition();
	vec3 CameraRotation = camera.GetCameraRotation();
	/*********/
	vec4 CameraPositionTransformed = inverse(ViewMatrix) * inverse(ProjectionMatrix) * vec4(CameraPosition, 1.0f);
	CameraPositionTransformed /= CameraPositionTransformed.w;
	CameraPosition = vec3(CameraPositionTransformed);
	return CameraPosition;
}
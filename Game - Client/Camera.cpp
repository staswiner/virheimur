#include "Camera.h"


bool Camera::LeftIsPressed = false;
vec2 Camera::MouseHoldPosition;
vec2 Camera::LastSavedMouseOffset;
unsigned int Camera::PreviousDelta;

Camera::Camera()
	:cameraStates(CameraStates::Instance())
{
	ResetCamera();
}


Camera::~Camera()
{
}

void Camera::ResetCamera()
{
	Position = vec3(0, -5, -20);
	CameraDestination = vec3(0, -5, -20);
	Rotation = vec3();
}

void Camera::SetCustomCameraValues(vec3 CameraPos, vec3 CameraRotation)
{
	this->Position = CameraPos;
	this->Rotation = CameraRotation;
	GetCameraMatrix();
}

mat4 Camera::GetUpdatedCamera()
{
	WheelScroll();
	MouseDrag();
	MouseMove();
	KeyboardInput();
	CalculateCameraValues();
	return GetCameraMatrix();
}
mat4 Camera::GetLockedCamera(vec3 Player, vec3 PlayerAngle)
{
	CameraDestination = -Player + vec3(0,-50,0);
	//MouseCameraAngle = PlayerAngle + vec3(Default::GetInstance().PI/2.0,0,0);
	//MouseCameraAngle *= 180 / Default::GetInstance().PI;
	MouseDrag();
	CalculateCameraValues();

	return GetCameraMatrix();
}
mat4 Camera::GetProjectionMatrix()
{
	Mouse& mouse = Mouse::Instanace();

	this->ProjectionMatrix=glm::perspective(
		glm::radians(70.0f), 
		(GLfloat)mouse.GetWindowSize().x / (GLfloat)mouse.GetWindowSize().y, 
		1.0f, 
		1000.0f);

	return this->ProjectionMatrix;
}
void Camera::SetProjectionMatrix(mat4 & projectionMatrix)
{
	this->ProjectionMatrix = projectionMatrix;
}
void Camera::InvertPitch()
{
	this->Rotation.x *= -1;
}
mat4 Camera::GetCameraMatrix()
{
	this->ViewMatrix = CameraRotationMatrix() * CameraTranslationMatrix();
	return this->ViewMatrix;
}
void Camera::ZoomInto(vec3 CameraPos, vec3 TargetPos)
{
	Mouse& mouse = Mouse::Instanace();

	if (mouse.GetCommands().size() > 0)
	{
		cameraStates.SetState("Zoom");
		mouse.GetCommands().clear();
	}

	if (distance((-TargetPos), Position) > 40.0f && cameraStates.IsInState("Zoom"))
	{
		this->CameraDestination = (-TargetPos) - ( 40.0f * normalize((-TargetPos) - Position));

	}
	
	//mat4 Matrix = lookAt(CameraPos,TargetPos,vec3(0,1,0));
	//return Matrix;
}
void Camera::WheelScroll()
{
	Mouse& mouse = Mouse::Instanace();

	int WheelDelta = mouse.GetWheelDelta() / 120;

	
	if (WheelDelta != 0)
	{
		cameraStates.SetState("Wheel Move");
		//CameraDestination.z += (int)(WheelDelta * (int)Camera::Delta) / 16.67f * 6.0f;
		CameraDestination.y += (int)(WheelDelta * (int)Time::Instance().Frame()) / 16.67f * 2.0f * scale;
	}
}
void Camera::MouseDrag()
{
	Mouse& mouse = Mouse::Instanace();
	if (mouse.LeftIsPressed())
	{
		if (LeftIsPressed == false)
		{
			LeftIsPressed = true;
			MouseHoldPosition = vec2(mouse.GetMouseX(), mouse.GetMouseY());
			LastSavedMouseOffset.x = Rotation.y;
			LastSavedMouseOffset.y = Rotation.x;
		}
		if (LeftIsPressed == true)
		{
			Rotation.x = mouse.GetMouseY() - MouseHoldPosition.y + LastSavedMouseOffset.y;
			Rotation.y = mouse.GetMouseX() - MouseHoldPosition.x + LastSavedMouseOffset.x;
		}
	}
	if (Rotation.x > 360.0f)
		Rotation.x -= 360.0f;
	if (Rotation.y > 360.0f)
		Rotation.y -= 360.0f;
	if (Rotation.x < 0.0f)
		Rotation.x += 360.0f;
	if (Rotation.y < 0.0f)
		Rotation.y += 360.0f;

	if (!mouse.LeftIsPressed())
	{
		LeftIsPressed = false;
	}
}
void Camera::MouseMove()
{
	Mouse& mouse = Mouse::Instanace();
	if (mouse.GetMouseX() >= 0 && mouse.GetMouseY() >= 0 && mouse.IsInWindow())
	{
		cameraStates.SetState("Side Move");
	}
	// move to sides
	if ( mouse.GetMouseX() >= 0 && mouse.GetMouseY() >= 0 && mouse.IsInWindow() &&
		cameraStates.IsInState("Side Move"))
	{
		int SceenOffset = 75;
		int EndOffset = 0;
		const int PI = 3.1415926535897f;
		float CameraMovementSpeed = Time::Instance().Frame() / 16.67f / 2.0f
			//* (-CameraPosition.z / 40.0f);
			* 1.0f * 
			scale;
		if (mouse.GetMouseY() > mouse.GetWindowSize().y - SceenOffset && mouse.GetMouseY() < mouse.GetWindowSize().y - EndOffset ) //&& CameraPosition.y < 900) // up
		{
			CameraDestination.z -= CameraMovementSpeed * cos((Rotation.y) / 180 * PI);
			CameraDestination.x += CameraMovementSpeed * sin((Rotation.y) / 180 * PI);
		}
		if (mouse.GetMouseY() < SceenOffset && mouse.GetMouseY() > EndOffset ) //&& CameraPosition.y > -900) // down
		{
			CameraDestination.z += CameraMovementSpeed * cos((Rotation.y) / 180 * PI);
			CameraDestination.x -= CameraMovementSpeed * sin((Rotation.y) / 180 * PI);
		}
		if (mouse.GetMouseX() > mouse.GetWindowSize().x - SceenOffset && mouse.GetMouseX() < mouse.GetWindowSize().x - EndOffset) // && CameraPosition.x < 900) // left
		{
			CameraDestination.z -= CameraMovementSpeed * sin((Rotation.y) / 180 * PI);
			CameraDestination.x -= CameraMovementSpeed * cos((Rotation.y) / 180 * PI);
		}
		if (mouse.GetMouseX() < SceenOffset && mouse.GetMouseX() > EndOffset )// && CameraPosition.x > -900) // right
		{
			CameraDestination.z += CameraMovementSpeed * sin((Rotation.y) / 180 * PI);
			CameraDestination.x += CameraMovementSpeed * cos((Rotation.y) / 180 * PI);
		}
	}
	//CameraPositionCalculated = CameraPosition;
}
void Camera::KeyboardInput()
{
	// move to sides
	int SceenOffset = 75;
	int EndOffset = 0;
	const int PI = 3.1415926535897f;
	float CameraMovementSpeed = Time::Instance().Frame() / 16.67f / 2.0f
		//* (-CameraPosition.z / 40.0f);
		* 1.0f;
	///Keyboard camera move
	//if (keyboard.isKeyPressed(UP)) // up
	//{
	//	CameraDestination.z += CameraMovementSpeed * cos((MouseCameraAngle.y) / 180 * PI);
	//	CameraDestination.x -= CameraMovementSpeed * sin((MouseCameraAngle.y) / 180 * PI);
	//}
	//if (keyboard.isKeyPressed(DOWN)) // down
	//{
	//	CameraDestination.z -= CameraMovementSpeed * cos((MouseCameraAngle.y) / 180 * PI);
	//	CameraDestination.x += CameraMovementSpeed * sin((MouseCameraAngle.y) / 180 * PI);
	//}
	//if (keyboard.isKeyPressed(RIGHT)) // left
	//{
	//	MouseCameraAngle.y++;
	//}
	//if (keyboard.isKeyPressed(LEFT))// && CameraPosition.x > -900) // right
	//{
	//	MouseCameraAngle.y--;
	//}
}
void Camera::CalculateCameraValues()
{
	float CameraSpeed = 20.0f;
	if (abs(CameraDestination.z - Position.z) > 0.1f)
	{
		Position.z -= (Position.z - CameraDestination.z) / CameraSpeed;
	}
	if (abs(CameraDestination.y - Position.y) > 0.1f)
	{
		Position.y -= (Position.y - CameraDestination.y) / CameraSpeed;
	}
	if (abs(CameraDestination.x - Position.x) > 0.1f)
	{
		Position.x -= (Position.x - CameraDestination.x) / CameraSpeed;
	}
	// fixes camera movement
	std::ostringstream oss;
	oss << Position.x << " " << Position.y << " " << Position.z << std::endl;
	OutputDebugString(oss.str().c_str());
}
mat4 Camera::CameraRotationMatrix()
{
	mat4 CameraRotation;
	CameraRotation = glm::rotate(CameraRotation, glm::radians(Rotation.x), vec3(1, 0, 0));
	CameraRotation = glm::rotate(CameraRotation, glm::radians(Rotation.y), vec3(0, 1, 0));
	CameraRotation = glm::rotate(CameraRotation, glm::radians(Rotation.z), vec3(0, 0, 1));
	return CameraRotation;
}
mat4 Camera::CameraTranslationMatrix()
{
	mat4 CameraTranslation;
	CameraTranslation = glm::translate(CameraTranslation, Position);
	return CameraTranslation;
}

CameraStates::CameraStates()
{
	vector<string> Array;
	States["Zoom"].push_back("Zoom");
	States["Side Move"].push_back("Side Move");
	States["Side Move"].push_back("Wheel Move");
	States["Wheel Move"].push_back("Side Move");
	States["Wheel Move"].push_back("Wheel Move");
}
CameraStates::~CameraStates()
{
}

void CameraStates::SetState(string state)
{
	Lock = state;
}

bool CameraStates::IsInState(string state)
{
	bool returnVal = false;
	for each (string s in States[Lock])
	{
		if (s == state)
			returnVal = true;
	}
	return returnVal;
}

#include "Camera.h"


vec3 Camera::CameraPositionCalculated;
bool Camera::LeftIsPressed = false;
vec2 Camera::MouseHoldPosition;
vec2 Camera::LastSavedMouseOffset;
unsigned int Camera::Delta;
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
	CameraPosition = vec3(0, -5, -20);
	CameraDestination = vec3(0, -5, -20);
	MouseCameraAngle = vec3();
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
vec3 Camera::GetCameraPosition()
{
	return this->CameraPosition;
}
vec3 Camera::GetCameraRotation()
{
	return this->MouseCameraAngle;
}
mat4 Camera::GetProjectionMatrix()
{
	this->ProjectionMatrix=glm::perspective(
		glm::radians(70.0f), 
		(GLfloat)this->mouse.GetWindowSize().x / (GLfloat)this->mouse.GetWindowSize().y, 
		1.0f, 
		1000.0f);

	return this->ProjectionMatrix;
}
void Camera::SetProjectionMatrix(mat4 & projectionMatrix)
{
	this->ProjectionMatrix = projectionMatrix;
}
void Camera::SetCameraPosition(vec3 CameraPosition)
{
	this->CameraPositionCalculated = CameraPosition;
}
void Camera::InvertPitch()
{
	this->MouseCameraAngle.x *= -1;
}
mat4 Camera::GetCameraMatrix()
{
	return CameraRotationMatrix() * CameraTranslationMatrix();
}
void Camera::ZoomInto(vec3 CameraPos, vec3 TargetPos)
{
	if (mouse.GetCommands().size() > 0)
	{
		cameraStates.SetState("Zoom");
		mouse.GetCommands().clear();
	}

	if (distance((-TargetPos), CameraPosition) > 40.0f && cameraStates.IsInState("Zoom"))
	{
		this->CameraDestination = (-TargetPos) - ( 40.0f * normalize((-TargetPos) - CameraPosition));

	}
	
	//mat4 Matrix = lookAt(CameraPos,TargetPos,vec3(0,1,0));
	//return Matrix;
}
void Camera::WheelScroll()
{
	int WheelDelta = mouse.GetWheelDelta() / 120;

	if (WheelDelta != 0)
	{
		cameraStates.SetState("Wheel Move");
		//CameraDestination.z += (int)(WheelDelta * (int)Camera::Delta) / 16.67f * 6.0f;
		CameraDestination.y += (int)(WheelDelta * (int)Camera::Delta) / 16.67f * 1.0f;
	}
}
void Camera::MouseDrag()
{
	if (mouse.LeftIsPressed())
	{
		if (LeftIsPressed == false)
		{
			LeftIsPressed = true;
			MouseHoldPosition = vec2(mouse.GetMouseX(), mouse.GetMouseY());
			LastSavedMouseOffset.x = MouseCameraAngle.y;
			LastSavedMouseOffset.y = MouseCameraAngle.x;
		}
		if (LeftIsPressed == true)
		{
			MouseCameraAngle.x = mouse.GetMouseY() - MouseHoldPosition.y + LastSavedMouseOffset.y;
			MouseCameraAngle.y = mouse.GetMouseX() - MouseHoldPosition.x + LastSavedMouseOffset.x;
		}
	}
	if (MouseCameraAngle.x > 360.0f)
		MouseCameraAngle.x -= 360.0f;
	if (MouseCameraAngle.y > 360.0f)
		MouseCameraAngle.y -= 360.0f;
	if (MouseCameraAngle.x < 0.0f)
		MouseCameraAngle.x += 360.0f;
	if (MouseCameraAngle.y < 0.0f)
		MouseCameraAngle.y += 360.0f;

	if (!mouse.LeftIsPressed())
	{
		LeftIsPressed = false;
	}
}
void Camera::MouseMove()
{
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
		float CameraMovementSpeed = Camera::Delta / 16.67f / 2.0f 
			//* (-CameraPosition.z / 40.0f);
			* 1.0f;
		if (mouse.GetMouseY() > mouse.GetWindowSize().y - SceenOffset && mouse.GetMouseY() < mouse.GetWindowSize().y - EndOffset ) //&& CameraPosition.y < 900) // up
		{
			CameraDestination.z -= CameraMovementSpeed * cos((MouseCameraAngle.y) / 180 * PI);
			CameraDestination.x += CameraMovementSpeed * sin((MouseCameraAngle.y) / 180 * PI);
		}
		if (mouse.GetMouseY() < SceenOffset && mouse.GetMouseY() > EndOffset ) //&& CameraPosition.y > -900) // down
		{
			CameraDestination.z += CameraMovementSpeed * cos((MouseCameraAngle.y) / 180 * PI);
			CameraDestination.x -= CameraMovementSpeed * sin((MouseCameraAngle.y) / 180 * PI);
		}
		if (mouse.GetMouseX() > mouse.GetWindowSize().x - SceenOffset && mouse.GetMouseX() < mouse.GetWindowSize().x - EndOffset) // && CameraPosition.x < 900) // left
		{
			CameraDestination.z -= CameraMovementSpeed * sin((MouseCameraAngle.y) / 180 * PI);
			CameraDestination.x -= CameraMovementSpeed * cos((MouseCameraAngle.y) / 180 * PI);
		}
		if (mouse.GetMouseX() < SceenOffset && mouse.GetMouseX() > EndOffset )// && CameraPosition.x > -900) // right
		{
			CameraDestination.z += CameraMovementSpeed * sin((MouseCameraAngle.y) / 180 * PI);
			CameraDestination.x += CameraMovementSpeed * cos((MouseCameraAngle.y) / 180 * PI);
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
	float CameraMovementSpeed = Camera::Delta / 16.67f / 2.0f
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
	if (abs(CameraDestination.z - CameraPosition.z) > 0.1f)
	{
		CameraPosition.z -= (CameraPosition.z - CameraDestination.z) / CameraSpeed;
	}
	if (abs(CameraDestination.y - CameraPosition.y) > 0.1f)
	{
		CameraPosition.y -= (CameraPosition.y - CameraDestination.y) / CameraSpeed;
	}
	if (abs(CameraDestination.x - CameraPosition.x) > 0.1f)
	{
		CameraPosition.x -= (CameraPosition.x - CameraDestination.x) / CameraSpeed;
	}
	// fixes camera movement
	mat4 cameraMat = CameraRotationMatrix();
	CameraPositionCalculated = vec3(/*CameraRotationMatrix() * */vec4(CameraPosition, 0.0f));
	std::ostringstream oss;
	oss << CameraPosition.x << " " << CameraPosition.y << " " << CameraPosition.z << std::endl;
	OutputDebugString(oss.str().c_str());
}
mat4 Camera::CameraRotationMatrix()
{
	mat4 CameraRotation;
	CameraRotation = glm::rotate(CameraRotation, glm::radians(MouseCameraAngle.x), vec3(1, 0, 0));
	CameraRotation = glm::rotate(CameraRotation, glm::radians(MouseCameraAngle.y), vec3(0, 1, 0));
	CameraRotation = glm::rotate(CameraRotation, glm::radians(MouseCameraAngle.z), vec3(0, 0, 1));
	return CameraRotation;
}
mat4 Camera::CameraRotationMatrix_z()
{
	mat4 CameraRotation;
//	CameraRotation = glm::rotate(CameraRotation, glm::radians(MouseCameraAngle.x), vec3(1, 0, 0));
	CameraRotation = glm::rotate(CameraRotation, glm::radians(MouseCameraAngle.y), vec3(0, 1, 0));
	//CameraRotation = glm::rotate(CameraRotation, glm::radians(MouseCameraAngle.z), vec3(0, 0, 1));
	return CameraRotation;
}
mat4 Camera::CameraTranslationMatrix()
{
	mat4 CameraTranslation;
	CameraTranslation = glm::translate(CameraTranslation, CameraPositionCalculated);
	return CameraTranslation;
}
void Camera::CalculateTimeDelta()
{
	int NewTime = glutGet(GLUT_ELAPSED_TIME); //1000, 1050	
	static int Time = NewTime;
	int loopNumber = 20;

	Camera::Delta = (NewTime - Time);
	Camera::PreviousDelta = Camera::Delta;

	Time = NewTime; // 1000
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

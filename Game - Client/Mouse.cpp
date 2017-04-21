
#include "Mouse.h"

Mouse::Mouse()
	:
	leftIsPressed(false),
	rightIsPressed(false),
	x(-1),
	y(-1),
	delta(0),
	isInWindow(true)
{}

void Mouse::OnMouseMove(int x, int y)
{
	this->x = x;
	this->y = y;
}
void Mouse::OnWheelMove(int delta)
{
	//if (this->delta == delta)
	//{
	//	this->delta == 0;
	//}
	this->delta = delta;
	switch (this->delta)
	{
	case +120: this->z--; break;
	case -120: this->z++; break;
	case 0: break;
	}
}
void Mouse::OnLeftPressed()
{
	leftIsPressed = true;
}
void Mouse::OnLeftReleased()
{
	leftIsPressed = false;
}
void Mouse::OnRightPressed()
{
	rightIsPressed = true;
}
void Mouse::OnRightReleased()
{
	rightIsPressed = false;
}

void Mouse::SetInWindow(const bool InWindow)
{
	isInWindow = InWindow;
}

int Mouse::GetMouseX() const
{
	return x;
}
int Mouse::GetMouseY() const
{
	return y;
}
glm::vec2 Mouse::GetMouseCoords() const
{
	return glm::vec2(x,y);
}
int Mouse::GetWheelDelta() const
{
	return delta;
}
bool Mouse::LeftIsPressed() const
{
	return leftIsPressed;
}
bool Mouse::RightIsPressed() const
{
	return rightIsPressed;
}
bool Mouse::IsInRectangle(int Top, int Left, int Bot, int Right) const
{
	if (this->x > Top && this->x < Bot && this->y > Left && this->y < Right)
		return true;
	return false;
}
void Mouse::SetWindowSize(const int x, const int y)
{
	WindowSize = glm::vec2(x, y);
}
glm::vec2 Mouse::GetWindowSize() const
{
	return WindowSize;
}

list<int>& Mouse::GetCommands()
{
	return Commands;
}

void Mouse::PushCommand(int input)
{
	Commands.push_back(input);
}

///****mouse cover class***/
//staticMouse Mouse::sMouse;
//Mouse::Mouse()
//{
//
//}
//void Mouse::OnMouseMove(int x, int y)
//{
//	sMouse.OnMouseMove(x, y);
//}
//void Mouse::OnWheelMove(int delta)
//{
//	sMouse.OnWheelMove(delta);
//}
//void Mouse::OnLeftPressed() 
//{
//	sMouse.OnLeftPressed();
//}
//void Mouse::OnLeftReleased()
//{
//	sMouse.OnLeftReleased();
//}
//void Mouse::OnRightPressed()
//{
//	sMouse.OnRightPressed();
//}
//void Mouse::OnRightReleased()
//{
//	sMouse.OnRightReleased();
//}
//
//int Mouse::GetMouseX() const
//{
//	return sMouse.GetMouseX();
//}
//int Mouse::GetMouseY() const
//{
//	return sMouse.GetMouseY();
//}
//glm::vec2 Mouse::GetMouseCoords() const
//{
//	return sMouse.GetMouseCoords();
//}
//int Mouse::GetWheelDelta() const
//{
//	return sMouse.GetWheelDelta();
//}
//bool Mouse::LeftIsPressed() const
//{
//	return sMouse.LeftIsPressed();
//}
//bool Mouse::RightIsPressed() const
//{
//	return sMouse.RightIsPressed();
//}
//bool Mouse::IsInWindow() const
//{
//	return sMouse.IsInWindow();
//}
//
//bool Mouse::IsInRectangle(int Top, int Left, int Bot, int Right) const
//{
//	if (this->sMouse.IsInRectangle(Top, Left, Bot, Right))
//		return true;
//	return false;
//}
//
//list<int>& Mouse::GetCommands()
//{
//	return sMouse.GetCommands();
//}
//
//void Mouse::PushCommand(int input)
//{
//	sMouse.PushCommand(input);
//}
//
//void Mouse::SetWindowSize(const int x, const int y)
//{
//	sMouse.SetWindowSize(x, y);
//}
//glm::vec2 Mouse::GetWindowSize() const
//{
//	return sMouse.GetWindowSize();
//}
//void Mouse::SetInWindow(const bool InWindow)
//{
//	sMouse.SetInWindow(InWindow);
//}
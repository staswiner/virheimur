
#include "Mouse.h"

staticMouse::staticMouse()
	:
	leftIsPressed(false),
	rightIsPressed(false),
	x(-1),
	y(-1),
	delta(0),
	isInWindow(true)
{}

void staticMouse::OnMouseMove(int x, int y)
{
	this->x = x;
	this->y = y;
}
void staticMouse::OnWheelMove(int delta)
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
void staticMouse::OnLeftPressed()
{
	leftIsPressed = true;
}
void staticMouse::OnLeftReleased()
{
	leftIsPressed = false;
}
void staticMouse::OnRightPressed()
{
	rightIsPressed = true;
}
void staticMouse::OnRightReleased()
{
	rightIsPressed = false;
}

void staticMouse::SetInWindow(const bool InWindow)
{
	isInWindow = InWindow;
}

int staticMouse::GetMouseX() const
{
	return x;
}
int staticMouse::GetMouseY() const
{
	return y;
}
int staticMouse::GetWheelDelta() const
{
	return delta;
}
bool staticMouse::LeftIsPressed() const
{
	return leftIsPressed;
}
bool staticMouse::RightIsPressed() const
{
	return rightIsPressed;
}
bool staticMouse::IsInRectangle(int Top, int Left, int Bot, int Right) const
{
	if (this->x > Top && this->x < Bot && this->y > Left && this->y < Right)
		return true;
	return false;
}
void staticMouse::SetWindowSize(const int x, const int y)
{
	WindowSize = glm::vec2(x, y);
}
glm::vec2 staticMouse::GetWindowSize() const
{
	return WindowSize;
}

list<int>& staticMouse::GetCommands()
{
	return Commands;
}

void staticMouse::PushCommand(int input)
{
	Commands.push_back(input);
}

/****mouse cover class***/
staticMouse Mouse::sMouse;
Mouse::Mouse()
{

}
void Mouse::OnMouseMove(int x, int y)
{
	sMouse.OnMouseMove(x, y);
}
void Mouse::OnWheelMove(int delta)
{
	sMouse.OnWheelMove(delta);
}
void Mouse::OnLeftPressed() 
{
	sMouse.OnLeftPressed();
}
void Mouse::OnLeftReleased()
{
	sMouse.OnLeftReleased();
}
void Mouse::OnRightPressed()
{
	sMouse.OnRightPressed();
}
void Mouse::OnRightReleased()
{
	sMouse.OnRightReleased();
}

int Mouse::GetMouseX() const
{
	return sMouse.GetMouseX();
}
int Mouse::GetMouseY() const
{
	return sMouse.GetMouseY();
}
int Mouse::GetWheelDelta() const
{
	return sMouse.GetWheelDelta();
}
bool Mouse::LeftIsPressed() const
{
	return sMouse.LeftIsPressed();
}
bool Mouse::RightIsPressed() const
{
	return sMouse.RightIsPressed();
}
bool Mouse::IsInWindow() const
{
	return sMouse.IsInWindow();
}

bool Mouse::IsInRectangle(int Top, int Left, int Bot, int Right) const
{
	if (this->sMouse.IsInRectangle(Top, Left, Bot, Right))
		return true;
	return false;
}

list<int>& Mouse::GetCommands()
{
	return sMouse.GetCommands();
}

void Mouse::PushCommand(int input)
{
	sMouse.PushCommand(input);
}

void Mouse::SetWindowSize(const int x, const int y)
{
	sMouse.SetWindowSize(x, y);
}
glm::vec2 Mouse::GetWindowSize() const
{
	return sMouse.GetWindowSize();
}
void Mouse::SetInWindow(const bool InWindow)
{
	sMouse.SetInWindow(InWindow);
}
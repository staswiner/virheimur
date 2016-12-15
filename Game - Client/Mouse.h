#pragma once
#include "glm/glm/vec2.hpp"
#include <list>

using namespace std;

class staticMouse
{
public:
	staticMouse();
	int GetMouseX() const;
	int GetMouseY() const;
	glm::vec2 GetMouseCoords() const;
	int GetWheelDelta() const;
	bool LeftIsPressed() const;
	bool RightIsPressed() const;
	bool IsInWindow() const { return isInWindow; }
	bool IsInRectangle(int Top, int Left, int Bot, int Right) const;

	void OnMouseMove(int x, int y);
	void OnWheelMove(int delta);
	void OnLeftPressed();
	void OnLeftReleased();
	void OnRightPressed();
	void OnRightReleased();
	void SetInWindow(const bool);

	void SetWindowSize(const int x, const int y);
	glm::vec2 GetWindowSize() const;
	list<int>& GetCommands();
	void PushCommand(int);

private:
	int x;
	int y;
	int z;
	int delta;
	bool leftIsPressed;
	bool rightIsPressed;
	bool isInWindow;
	glm::vec2 WindowSize;
	list<int> Commands;
};
class Mouse
{
public:
	Mouse();
	static staticMouse sMouse;
	void OnMouseMove(int x, int y);
	void OnWheelMove(int delta);
	void OnLeftPressed();
	void OnLeftReleased();
	void OnRightPressed();
	void OnRightReleased();
	void SetInWindow(const bool);


	int GetMouseX() const;
	int GetMouseY() const;
	glm::vec2 GetMouseCoords() const;
	int GetWheelDelta() const;
	bool LeftIsPressed() const;
	bool RightIsPressed() const;
	bool IsInWindow() const;
	bool IsInRectangle(int Top, int Left, int Bot, int Right) const;
	list<int>& GetCommands();
	void PushCommand(int);

	void SetWindowSize(const int x, const int y);
	glm::vec2 GetWindowSize() const;
};
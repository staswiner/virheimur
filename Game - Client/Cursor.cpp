#include "Cursor.h"



Cursor::Cursor()
{
}


Cursor::~Cursor()
{
}

void Cursor::Initialize()
{
	CursorEl = new UIElement("Cursor", "Interface/cursor.png", 0);
	//GreyCover->TopLeft = Position;
	//GreyCover->SetByTrueSize(Position);
	//GreyCover->innerText = "PAUSE";
}

void Cursor::Draw()
{
	Mouse mouse;
	CursorEl->TopLeft = vec2(mouse.GetMouseX(), mouse.GetMouseY());
	CursorEl->SetByTrueSize(CursorEl->TopLeft);
	CursorEl->Draw();

}

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
	//Mouse& mouse = Mouse::Instanace();
	//CursorEl->Top = mouse.GetMouseY();
	//CursorEl->Left = mouse.GetMouseX();
	//CursorEl->SetByTrueSize(vec2(CursorEl->Top, CursorEl->Left));
	//CursorEl->Draw();

}

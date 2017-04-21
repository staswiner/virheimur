
#include "Button.h"

Button::Button(vec2 StartP, vec2 EndP, int index, string a_Text)
	:StartP(StartP),
	EndP(EndP),
	index(index),
	s_Text(a_Text)
{
//	m_Text = new Text("Fonts/Font.jpg");
}


Button::~Button()
{
}

void Button::Initialize()
{
	NotSelectedButton.Initialize("Interface/Button.png");
	SelectedButton.Initialize("Interface/ButtonSelected.jpg");
}


void Button::SelectText()
{
}


void Button::Draw()
{
	 Mouse& mouse = Mouse::Instanace();

	vec2 CurrentStartP = vec2(StartP.x - 10.0f * m_isSelected, StartP.y - 10.0f * m_isSelected);
	vec2 CurrentEndP = vec2(EndP.x + 10.0f * m_isSelected, EndP.y + 10.0f * m_isSelected);
	if (m_isSelected)
	{
		SelectedButton.Draw(CurrentStartP, CurrentEndP);
	}
	else
		NotSelectedButton.Draw(CurrentStartP, CurrentEndP);
	// Adds line
	string outString = s_Text;
	// prints text to the textbox
	//m_Text->Draw(outString, 20 /*+ 5 * m_isSelected,*/,
	//	vec2(StartP.x + 15,
	//		(StartP.y + EndP.y) / 2 - 10));



}

bool Button::OnSelection()
{
	 Mouse& mouse = Mouse::Instanace();
	if (mouse.GetMouseX() > this->StartP.x && mouse.GetMouseX() < this->EndP.x &&
		mouse.GetMouseY() > this->StartP.y && mouse.GetMouseY() < this->EndP.y &&
		mouse.LeftIsPressed())
	{
		return true;
	}


	return false;
}

int Button::GetIndex() const
{
	return index;
}


bool Button::isSelected() const
{
	return m_isSelected;
}

void Button::isSelected(const bool a_isSelected)
{
	m_isSelected = a_isSelected;
}


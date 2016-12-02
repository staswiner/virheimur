
#include "Textbox.h"

int Textbox::TimePassed = 0;
Textbox::Textbox(vec2 StartP, vec2 EndP,int index,int maxChars)
	:StartP(StartP),
	EndP(EndP),
	index(index),
	maxChars(maxChars)
{
	m_Text = new Text("Fonts/Font.jpg");
}


Textbox::~Textbox()
{
}

void Textbox::Initialize()
{
	NotSelectedTextbox.Initialize("Interface/Textbox.jpg");
	SelectedTextbox.Initialize("Interface/TextboxSelected.jpg");
}

void Textbox::EraseChar()
{
	if (s_Text.size() > 0)
		this->s_Text.pop_back();
}

void Textbox::SelectText()
{
}

void Textbox::InputChar(char input)
{
	if (this->s_Text.size() + 1 < (GLuint)maxChars)
	{
		TimePassed = 0;
		this->s_Text.push_back(input);
	}
}

void Textbox::Draw()
{
	Mouse mouse;
	vec2 CurrentStartP = vec2(StartP.x - 10.0f * m_isSelected, StartP.y - 10.0f * m_isSelected);
	vec2 CurrentEndP = vec2(EndP.x + 10.0f * m_isSelected, EndP.y + 10.0f * m_isSelected);
	if (m_isSelected)
	{
		CalculateDelta();
		SelectedTextbox.Draw(CurrentStartP, CurrentEndP);
	}
	else
		NotSelectedTextbox.Draw(CurrentStartP, CurrentEndP);
	// Adds line
	string outString = s_Text;
	if (m_isSelected && TimePassed < 250)
		outString += '_';
	// prints text to the textbox
	//m_Text->Draw(outString, 20 /*+ 5 * Selected,*/,
	//	vec2(StartP.x + 15,
	//		(StartP.y + EndP.y) / 2 - 10));



}

bool Textbox::OnSelection()
{
	Mouse mouse;
	if (mouse.GetMouseX() > this->StartP.x && mouse.GetMouseX() < this->EndP.x &&
		mouse.GetMouseY() > this->StartP.y && mouse.GetMouseY() < this->EndP.y &&
		mouse.LeftIsPressed())
	{
		TimePassed = 0;
		return true;
	}


	return false;
}

int Textbox::GetIndex() const
{
	return index;
}

bool Textbox::isSelected() const
{
	return m_isSelected;
}

void Textbox::isSelected(const bool a_isSelected)
{
	m_isSelected = a_isSelected;
}


void Textbox::CalculateDelta()
{
	int NewTime = glutGet(GLUT_ELAPSED_TIME); //1000, 1050
	static int Time = NewTime;
	TimePassed += (NewTime - Time) / 2;
	Time = NewTime; 
	TimePassed %= 500;
}


EmptyTextbox::EmptyTextbox(vec2 StartP, vec2 EndP, int index, int maxChars)
	:Textbox(StartP, EndP, index, maxChars)
{
}

EmptyTextbox::~EmptyTextbox()
{
}

void EmptyTextbox::Initialize()
{
}

void EmptyTextbox::InputChar(char input)
{
}

void EmptyTextbox::EraseChar()
{
}

void EmptyTextbox::SelectText()
{
}

void EmptyTextbox::Draw()
{
}

bool EmptyTextbox::OnSelection()
{
	return false;
}

int EmptyTextbox::GetIndex() const
{
	return 0;
}

bool EmptyTextbox::isSelected() const
{
	return false;
}

void EmptyTextbox::isSelected(const bool)
{
	m_isSelected = false;
}

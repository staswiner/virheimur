#pragma once
#include "Graphics_Header.h"
#include "ImageLoader.h"
#include "Text.h"
#include <string>
using namespace std;
class Button // TODO: make a simple object class like c#
{
public:
	Button(vec2 StartP, vec2 EndP, int index, string Text);
	~Button();
	virtual void Initialize();
	virtual void SelectText();
	virtual void Draw();
	virtual bool OnSelection();
	virtual int GetIndex() const;
	virtual bool isSelected() const;
	virtual void isSelected(const bool);
protected:
	Text* m_Text;
	const vec2 StartP;
	const vec2 EndP;
	const string s_Text;
	int index;
	ImageLoader NotSelectedButton;
	ImageLoader SelectedButton;
	bool m_isSelected;

};

//#pragma once
//#include "Graphics_Header.h"
//#include "ImageLoader.h"
//#include "Text.h"
//#include <string>
//using namespace std;
//class Textbox
//{
//public:
//	Textbox(vec2 StartP, vec2 EndP, int index, int maxChars);
//	~Textbox();
//	virtual void Initialize();
//	virtual void InputChar(char input);
//	virtual void EraseChar();
//	virtual void SelectText();
//	virtual void Draw();
//	virtual bool OnSelection();
//	virtual int GetIndex() const;
//	virtual bool isSelected() const;
//	virtual void isSelected(const bool);
//protected:
//	Text* m_Text;
//	const vec2 StartP;
//	const vec2 EndP;
//	const int maxChars;
//	int index;
//	string s_Text;
//	ImageLoader NotSelectedTextbox;
//	ImageLoader SelectedTextbox;
//	void CalculateDelta();
//	static int TimePassed;
//	bool m_isSelected;
//};
//class EmptyTextbox : public Textbox
//{
//public:
//	EmptyTextbox(vec2 StartP, vec2 EndP, int index,int maxChars);
//	~EmptyTextbox();
//	void Initialize();
//	void InputChar(char input);
//	void EraseChar();
//	void SelectText();
//	void Draw();
//	bool OnSelection();
//	int GetIndex() const;
//	bool isSelected() const;
//	void isSelected(const bool);
//};

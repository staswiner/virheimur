#pragma once
#include <vector>
#include <functional>
#include "Maths.h"
#include "Text.h"
#include "ImageLoader.h"
#include "FBO.h"
using namespace std;
class UIElement
{
public:
	struct Element {
		Element() {}
		Element(string ID, int z_index = 1) { this->z_index = z_index; this->ID = ID; }
		int z_index;
		string ID;
		bool operator<(const UIElement::Element& rhs) const
		{
			if (this->z_index == rhs.z_index)
			{
				return this->ID < rhs.ID;
			}
			return this->z_index > rhs.z_index;
		}
	};
	struct Font {
		GLuint size = 20;
		vec3 color = vec3(0);
	};
	struct Style {
		Font font;
		vec3 maskColor = vec3(1);
		float opacity = 1.0f;
		bool MaskedText = false;
	};
public:
	UIElement(string Name, string Filename, int z_index=1);
	UIElement(string Name);
	~UIElement();
	void AddHoverEvent(std::function<void(UIElement*)> onhover);
	void AddHoverDoneEvent(std::function<void(UIElement*)> onhoverdone);
	void AddReturnDefaultEvent(std::function<void(UIElement*)> onreturndefault);
	void AddClickEvent(std::function<void(UIElement*)> onclick);
	void AddPressEvent(std::function<void(UIElement*)> onpress);
	void AddTextChangedEvent(std::function<void(UIElement*)> ontextchanged);
	UIElement* GetHover(vec2 MouseCoords);
	UIElement* GetClick(vec2 MouseCoords);
	virtual void OnHover();
	virtual void OnHoverDone();
	virtual void OnReturnDefault();
	virtual void OnClick();
	virtual void OnPress();
	virtual void OnTextChanged();
	virtual void Hide();
	void Show();
	void Destroy();

	UIElement* FocusNext();
	void AppendChild(UIElement*);
	void RemoveChild(UIElement*);
	void RemoveChild(string Name);
	void Draw();
	void SetByTrueSize(vec2 TopLeft);
	void SetByTrueSize();
	UIElement* GetUIElement(string Name);
	static void SetDrawTarget(UIElement*);
	void ChangePicture(string Filename);
	void InitFramebuffer(FBO& Framebuffer);
	void InitFramebuffer();
	void RemoveFBO();
	int Top;
	int Bottom;
	int Left;
	int Right;
	int TrueWidth;
	int TrueHeight;
	int PicturePadding;
	vec2 TextPosition;
	string innerText;
	Style style;
	UIElement* Parent;
	bool visible = true;
	bool writable = false;
	
	FBO* frameBufferObject;
protected:
	std::function<void(UIElement*)> hover;
	std::function<void(UIElement*)> hoverdone;
	std::function<void(UIElement*)> returndefault;
	std::function<void(UIElement*)> click;
	std::function<void(UIElement*)> press;
	std::function<void(UIElement*)> textchanged;
	void UpdateParentSize(int Top, int Left, int Bottom, int Right);
	void LoadPicture(string Filename);
	void DrawFrameBuffer();
	void BindFramebuffer();

	Element Name;
protected:
	int Width, Height;
	ImageLoader* UIImage;
	map<Element,UIElement*> Children;
	bool IsRoot;
	bool IsWriteableTo;
	static map <string, ImageLoader*> Repository;
};

namespace UI {
	class Textbox : public UIElement {
	public:
		Textbox(string Name); 						  
	
	};
	class Button : public UIElement {
	public:
		Button(string Name);
	};
	class DrawingArea : public UIElement {
	public:
		DrawingArea(string Name);
		void Resize();
	};
}
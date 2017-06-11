#include "UIElement.h"


bool SortElement(const UIElement::Element& lhs, const UIElement::Element& rhs)
{
	if (lhs.z_index == rhs.z_index)
	{
		return lhs.ID < rhs.ID;
	}
	return lhs.z_index < rhs.z_index;
}

map<string, ImageLoader*> UIElement::Repository;

UIElement::UIElement(string Name,string Filename,int z_index)
{
	if (Filename == "")
	{
		this->IsRoot = true;
	}
	else
	{
		this->IsRoot = false;
		this->LoadPicture(Filename);
		this->TrueWidth = UIImage->GetTrueSize().x;
		this->TrueHeight = UIImage->GetTrueSize().y;
		this->Width = this->TrueWidth;
		this->Height = this->TrueHeight;
	}

	this->Name = Element(Name,z_index);
	this->Parent = nullptr;
}

UIElement::UIElement(string Name)
{

}

UIElement::~UIElement()
{
}

void UIElement::AddHoverEvent(std::function<void(UIElement*)> onhover)
{
	this->hover.push_back( onhover );
}

void UIElement::AddHoverDoneEvent(std::function<void(UIElement*)> onhoverdone)
{
	this->hoverdone.push_back( onhoverdone );
}

void UIElement::AddReturnDefaultEvent(std::function<void(UIElement*)> onreturndefault)
{
	this->returndefault.push_back( onreturndefault );
}

void UIElement::AddClickEvent(std::function<void(UIElement*)> onclick)
{
	this->click.push_back( onclick );
}

void UIElement::AddPressEvent(std::function<void(UIElement*)> onpress)
{
	this->press.push_back( onpress );
}

void UIElement::AddTextChangedEvent(std::function<void(UIElement*)> ontextchanged)
{
	this->textchanged.push_back( ontextchanged );
}

UIElement* UIElement::GetHover(vec2 MouseCoords)
{
	for (auto uie : Children)
	{
		UIElement * focus;
		if (focus = uie.second->GetHover(MouseCoords))
		{
			return focus;
		}
	}
	if (Stas::Maths::IsIn(vec2(this->Left,this->Top), vec2(this->Right,this->Bottom), MouseCoords))
	{
		return this;
	}
	return nullptr;
}

UIElement* UIElement::GetClick(vec2 MouseCoords)
{
	for (auto uie : Children)
	{
		UIElement * focus;
		if (focus = uie.second->GetClick(MouseCoords))
		{
			return focus;
		}
	}
	if (Stas::Maths::IsIn(vec2(this->Left, this->Top), vec2(this->Right, this->Bottom), MouseCoords))
	{
		return this;
	}
	return nullptr;
	std::bind(&UIElement::Destroy, this);

}

void UIElement::OnHover()
{
	// checks if function bind to anything
	for (auto f : hover)
	{
		f(this);
	}
}

void UIElement::OnHoverDone()
{
	// checks if function bind to anything
	for (auto f : hoverdone)
	{
		f(this);
	}
}

void UIElement::OnReturnDefault()
{
	for (auto f : returndefault)
	{
		f(this);
	}
}

void UIElement::OnClick()
{
	// checks if function bind to anything
	for (auto f : click)
	{
		f(this);
	}
}

void UIElement::OnPress()
{
	// checks if function bind to anything
	for (auto f : press)
	{
		f(this);
	}
}

void UIElement::OnTextChanged()
{
	// checks if function bind to anything
	for (auto f : textchanged)
	{
		f(this);
	}
}

void UIElement::Hide()
{
	for (auto& uie : Children)
	{
		uie.second->Hide();
	}
	this->visible = false;
}

void UIElement::Show()
{
	for (auto& uie : Children)
	{
		uie.second->Show();
	}
	this->visible = true;
}

void UIElement::Destroy()
{
	for (auto uie = this->Children.begin(); uie!= this->Children.end();uie++)
	{
		uie->second->Destroy();
	}
	delete this;
}

UIElement* UIElement::FocusNext()
{
	if (this->Children.size() > 0)
	{
		return this->Children.begin()->second;
	}
	else if ((++this->Parent->Children.find(this->Name)) != this->Parent->Children.end())
	{

		UIElement* brother = (++this->Parent->Children.find(this->Name))->second;
		return brother;
	}
	else
	{
		return Parent;
	}
}

void UIElement::AppendChild(UIElement * child)
{
	Children[child->Name] = child;
	child->Parent = this;
}

void UIElement::RemoveChild(UIElement * Element)
{
	for (auto uie : Element->Children)
	{
		RemoveChild(uie.second);
		Parent->Children.erase(this->Name);
		delete this;
	}
}

void UIElement::RemoveChild(string Name)
{
	//// check for this element
	//if (Name == this->Name.ID)
	//	return this;
	// Find element
	UIElement * RootDelete = nullptr;
	for (auto uie : Children)
	{
		if (uie.second->Name.ID == Name)
		{
			RootDelete = uie.second;
			break;
		}
	}
	// No Such Element
	if (!RootDelete)
		return;
	// check for children
	RemoveChild(RootDelete);
}

void UIElement::Draw()
{
	if (visible == false)
		return;
	// back to front, draws parent before child
	if (this->IsRoot == false)
	{
		float FontSize = (float)this->style.font.size;
		vec2 margin(20.0f,((Bottom - Top) + FontSize/2.0f)/2.0f);
		TextPosition = vec2(this->Left,this->Top) + margin;
		this->UIImage->Draw(vec2(this->Left,this->Top), vec2(this->Right,this->Bottom));

		if (this->frameBufferObject)
		{
			DrawFrameBuffer();
		}

		Text::LoadTextShader(vec3(0, 0, 0));
		Text& text = Text::getInstance();
		// Mask text
		string NewInnerText;
		if (this->style.MaskedText)
		{
			NewInnerText.resize(this->innerText.size(), '*');
		}
		else
		{
			NewInnerText = this->innerText;
		}
		text.RenderText(NewInnerText, this->TextPosition.x, this->TextPosition.y,
			(this->Right - this->Left) - margin.x*2, FontSize, style.font.color);
	}
	// proceeds to drawing children
	for (auto uie : Children)
	{
		uie.second->Draw();
	}
}

void UIElement::SetByTrueSize(vec2 TopLeft)
{
	this->Bottom = TopLeft.y + TrueHeight;
	this->Right = TopLeft.x + TrueWidth;
}

void UIElement::SetByTrueSize()
{
	this->Bottom = Top + TrueHeight;
	this->Right = Left + TrueWidth;
}

UIElement* UIElement::GetUIElement(string Name)
{
	// check for this element
	if (Name == this->Name.ID)
		return this;
	// check for children
	for (auto uie : Children)
	{
		UIElement * element = uie.second->GetUIElement(Name);
		if (element != nullptr)
			return element;
	}
	// end of branch
	return nullptr;
}
void UIElement::SetDrawTarget(UIElement * element)
{
	element->BindFramebuffer();
}
void UIElement::ChangePicture(string Filename)
{
	this->LoadPicture(Filename);
	this->TrueWidth = UIImage->GetTrueSize().x;
	this->TrueHeight = UIImage->GetTrueSize().y;
}
void UIElement::InitFramebuffer(FBO & Framebuffer)
{
	this->frameBufferObject = new FBO();
	this->Width = this->Right - this->Left;
	this->Height = this->Bottom - this->Top;
	this->frameBufferObject->Initialize(
		Mouse::Instanace().GetWindowSize().x / this->Width, 
		Mouse::Instanace().GetWindowSize().y / this->Height, 
		&Shader::At("PostProcessing"));
	Framebuffer = *this->frameBufferObject;
}
void UIElement::InitFramebuffer()
{
	this->frameBufferObject = new FBO();
	this->Width = this->Right - this->Left;
	this->Height = this->Bottom - this->Top;
	this->frameBufferObject->Initialize(
		Mouse::Instanace().GetWindowSize().x / this->Width,
		Mouse::Instanace().GetWindowSize().y / this->Height,
		&Shader::At("PostProcessing"));
}
void UIElement::BindFramebuffer()
{
	this->frameBufferObject->BindFrameBuffer();
}
void UIElement::RemoveFBO()
{
	this->frameBufferObject = nullptr;
}
void UIElement::Set_Top(int Top)
{
	this->Top = Top;
	if (this->Bottom.assigned) this->Height = this->Bottom - this->Top;
	else { this->Bottom = this->Top - this->TrueHeight; this->Width = this->TrueHeight; }
}
void UIElement::Set_Bottom(int Bottom)
{
	this->Bottom = Bottom;
	if (this->Top.assigned) this->Height = this->Bottom - this->Top;
	else { this->Top = this->Bottom + this->TrueHeight; this->Width = this->TrueHeight; }
}
void UIElement::Set_Left(int Left)
{
	this->Left = Left;
	if (this->Right.assigned) this->Width = this->Right - this->Left;
	else { this->Right = this->Left + this->TrueWidth; this->Width = this->TrueWidth; }
}
void UIElement::Set_Right(int Right)
{
	this->Right = Right;
	if (this->Left.assigned) this->Width = this->Right - this->Left;
	else { this->Left = this->Right - this->TrueWidth; this->Width = this->TrueWidth; }
}
void UIElement::Set_Width(int Width)
{
	this->Width = Width;
	if (this->Left.assigned) this->Right = this->Left + this->Width;
	if (this->Right.assigned) this->Left = this->Right - this->Width;
}
void UIElement::Set_Height(int Height)
{
	this->Height = Height;
	if (this->Top.assigned) this->Bottom = this->Top + this->Height;
	if (this->Bottom.assigned) this->Top = this->Bottom - this->Height;
}
void UIElement::Set_PicturePadding(int Padding)
{
}
void UIElement::Set_Position(string PositionFormat)
{
	int Delimiters[3];
	Delimiters[0] = PositionFormat.find(',');
	Delimiters[1] = PositionFormat.find(',',Delimiters[0]+1);
	Delimiters[2] = PositionFormat.find(',',Delimiters[1]+1);

	// Left, Top, Right, Bot
	string Left_str = PositionFormat.substr(0, Delimiters[0]);
	string Top_str = PositionFormat.substr(Delimiters[0]+1, Delimiters[1] - Delimiters[0] - 1);
	string Right_str = PositionFormat.substr(Delimiters[1]+1, Delimiters[2] - Delimiters[1] - 1);
	string Bot_str = PositionFormat.substr(Delimiters[2]+1);

	this->Set_Left(stoi(Left_str));
	this->Set_Right(stoi(Right_str));
	this->Set_Top(stoi(Top_str));
	this->Set_Bottom(stoi(Bot_str));
}
// this function only increases size, might be bad if sizes need to get back to normal
void UIElement::UpdateParentSize(int Top, int Left, int Bottom, int Right)
{
	if (this->Parent != nullptr)
		this->Parent->UpdateParentSize(Top,Left,Bottom,Right);
	// Left
	if (this->Left > Left)
		this->Left = Left;
	// Top
	if (this->Top > Top)
		this->Top = Top;	
	// Right
	if (this->Right < Right)
		this->Right = Right;
	// Bot
	if (this->Bottom < Bottom)
		this->Bottom = Bottom;
}

void UIElement::LoadPicture(string Filename)
{
	if (Repository.find(Filename) == Repository.end())
	{
		Repository[Filename] = new ImageLoader();
		Repository[Filename]->Initialize(Filename);
	}
	this->UIImage = Repository[Filename];
}

void UIElement::DrawFrameBuffer()
{
	ShaderBuilder::LoadShader(*this->frameBufferObject->shader)->
		Add_vec4("ScreenCoordinates", vec4(0,0,
			Mouse::Instanace().GetWindowSize().x,Mouse::Instanace().GetWindowSize().y)).
		Add_vec4("FBO_Coordinates", vec4(this->Left + PicturePadding, 
			this->Top + PicturePadding, this->Right - PicturePadding, 
			this->Bottom - PicturePadding));

	this->frameBufferObject->DrawFrameBuffer();
}







void ags()
{ // 1|1
	{ // 2|1
		{ 
			// 3|1
		}
	}
	{ // 2|2
		{
			//3|2
		}
	}
	{
		//2|3
	}
	// ScopeID = {depth|index}
	// tokenID | type | ScopeID [[deprecated]]| address | value
	//
	//
	//
	//
	//
	//
}

UI::Textbox::Textbox(string Name) :
	UIElement(Name, "Interface/Textbox.png") 
{
#define Default
	/*this->Bottom = Default 0;
	this->Top = Default 0;
	this->Left = Default 0;
	this->Right = Default 0;
	this->TrueWidth = Default 0;
	this->TrueHeight = Default 0;*/
	this->innerText = Default "";
	this->writable = Default true;
	this->visible = Default true;
	this->TextPosition = Default vec2(0);
	this->style.font = Default Font();
	this->style.maskColor = Default vec3(0);
	this->style.MaskedText = Default false;
	this->style.opacity = Default 100;
	this->PicturePadding = Default 0;
}

UI::Button::Button(string Name) :
UIElement(Name, "Interface/Textbox.png")
{
#define Default
	/*this->Bottom = Default 0;
	this->Top = Default 0;
	this->Left = Default 0;
	this->Right = Default 0;
	this->TrueWidth = Default 0;
	this->TrueHeight = Default 0;*/
	this->innerText = Default "";
	this->writable = Default false;
	this->visible = Default true;
	this->TextPosition = Default vec2(0);
	this->style.font = Default Font();
	this->style.maskColor = Default vec3(0);
	this->style.MaskedText = Default false;
	this->style.opacity = Default 100;
	this->PicturePadding = Default 0;
	
}


UI::DrawingArea::DrawingArea(string Name) :
UIElement(Name, "Interface/Textbox.png")
{
#define Default
	/*this->Bottom = Default 0;
	this->Top = Default 0;
	this->Left = Default 0;
	this->Right = Default 0;
	this->TrueWidth = Default 0;
	this->TrueHeight = Default 0;*/
	this->innerText = Default "";
	this->writable = Default true;
	this->visible = Default true;
	this->TextPosition = Default vec2(0);
	this->style.font = Default Font();
	this->style.maskColor = Default vec3(0);
	this->style.MaskedText = Default false;
	this->style.opacity = Default 100;
	this->PicturePadding = Default 2;

}

void UI::DrawingArea::Resize()
{
	this->Width = this->Right - this->Left;
	this->Height = this->Bottom - this->Top;
	//this->frameBufferObject->Resize(this->Width, this->Height);
	this->InitFramebuffer();
}

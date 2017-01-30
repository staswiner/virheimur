#include "UserInterface.h"



UserInterface::UserInterface()
{
}


UserInterface::~UserInterface()
{
}

void UserInterface::GenerateForm(UIElement * root)
{
	this->root = root;
}


void UserInterface::AcceptInput()
{
	CleanWindows();
	list<pair<int,time_t>>& Letters = keyboard.getLetters();
	//Inputs[Commands.front().first];
	if (Letters.size() > 0)
	{
		if (Pressed == nullptr or not Pressed->visible)
		{
			InWorldCommands.push_back(Letters.front().first);
			Letters.pop_front();
		}
		else
		{
			char input = Letters.front().first;
			string& innerText = Pressed->innerText;
			switch (input)
			{
			case '\b': innerText.size() > 0 ? innerText.pop_back() : nullptr; break;
			case '\t': FocusNext(); break;
			case 'p': OpenStatWindow(); StatWindowOpen ? StatWindowOpen = false : StatWindowOpen = true;
			default: innerText.push_back(input); Pressed->OnTextChanged(); break;
			}
			Letters.pop_front();
		}
	}
	//ChampionChat championChat(Shader::At("Champion Chat"));
	///*tempWindows.push_back(pair<unique_ptr<ChampionChat>, GLuint>
	//	(make_unique<ChampionChat>(championChat),time(NULL)));*/
	//tempWindows.push_back({ make_unique<ChampionChat>(championChat), time(NULL) });
	

}

void UserInterface::CleanWindows()
{
	time_t curTime = time(NULL);
	for (GLuint i = 0; i < tempWindows.size(); i++)
	{
		if (curTime - tempWindows[i].second > 5)
		{
			tempWindows.erase(tempWindows.begin() + i);
			i--;
		}
	}
}
void IsOver(int x, int y) {}
void UserInterface::FocusControl()
{
	int x = mouse.GetMouseX();
	int y = mouse.GetMouseY();
	
	if (Pressed != Focused && Focused!=nullptr)
	{
		Focused->OnHoverDone();
	}
	Focused = root->GetHover(vec2(x, y));
	if (Pressed != Focused && Focused != nullptr)
	{
		Focused->OnHover();
	}
	// Apply Hover Function of the element
	// The Onclick function will be activated from Input class

}

bool UserInterface::LeftClick()
{
	bool returnValue = false;
	if (Pressed != nullptr)
	{
		Pressed->OnReturnDefault();
	}
	Pressed = Focused;
	if (Pressed != nullptr)
	{
		Pressed->OnClick();
		returnValue = true;
	}
	return returnValue;
}
void UserInterface::LeftPress()
{
	if (Pressed != nullptr)
	{
		Pressed->OnReturnDefault();
	}
	Pressed = Focused;
	if (Pressed != nullptr)
		Pressed->OnPress();
}

void UserInterface::FocusNext()
{
	Pressed->OnReturnDefault();
	Pressed = Pressed->FocusNext();
	Pressed->OnClick();
}
void UserInterface::OpenStatWindow()
{
	if (StatWindowOpen)
	{
		root->RemoveChild("StatsWindow");
	}
	else
	{
		vec2 Position;
		UIElement* StatsWindow = new UIElement("StatsWindow", "Interface/StatsWindow.png");
		Position = vec2(710, 300);
		StatsWindow->TopLeft = Position;
		StatsWindow->SetByTrueSize(Position);
		root->AppendChild(StatsWindow);

		for (int i = 0; i < 4; i++)
		{
			UIElement* StatsField = new UIElement("StatsField" + i, "Interface/StatsField.png");
			Position = vec2(710, 300 + (i * 50));
			StatsField->TopLeft = Position;
			StatsField->SetByTrueSize(Position);
			StatsField->AddHoverEvent([]
			(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/StatsFieldHovered.png"); });
			StatsField->AddHoverDoneEvent([]
			(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/StatsField.png"); });
			StatsField->AddReturnDefaultEvent([]
			(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/StatsField.png"); });
			StatsField->AddClickEvent([]
			(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/StatsFieldSelected.png"); });
			StatsWindow->AppendChild(StatsField);
		}
	}
}

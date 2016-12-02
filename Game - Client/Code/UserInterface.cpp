#include "UserInterface.h"



UserInterface::UserInterface()
{
}


UserInterface::~UserInterface()
{
}

void UserInterface::AcceptInput()
{
	CleanWindows();
	list<pair<int,time_t>>& Letters = keyboard.getLetters();
	//Inputs[Commands.front().first];
	if (Letters.size() > 0)
	{
		char input = Letters.front().first;
		switch (input)
		{
		case '\b': Chat.size() > 0 ? Chat.pop_back() : nullptr; break;
		default: Chat.push_back(input); break;
		}
		Letters.pop_front();
	}
	ChampionChat championChat(Shader::At("Champion Chat"));
	/*tempWindows.push_back(pair<unique_ptr<ChampionChat>, GLuint>
		(make_unique<ChampionChat>(championChat),time(NULL)));*/
	tempWindows.push_back({ make_unique<ChampionChat>(championChat), time(NULL) });
	

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
	vector<UIWindow> UIWindows;
	for (auto i : UIWindows)
	{
		//i.
		IsOver(x, y);
		// SetTarget
	}
	// Apply Hover Function of the element
	// The Onclick function will be activated from Input class

}

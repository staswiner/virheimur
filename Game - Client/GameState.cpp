//#include "GameState.h"
//
//
//PlayerRepository GameState::Players;
//PlayerRepository GameState::NewPlayers;
//PlayerRepository GameState::ReceivedPlayers;
//GlobalDataObject GameState::NewData;
//GlobalDataObject GameState::ReceivedData(ReceivedPlayers);
//GlobalDataObject GameState::Data(Players);
//GameState::GameState(Scene& scene, Network& network, Input& input, GameLogic& logic)
//	: scene(scene),
//	network(network),
//	input(input),
//	gameLogic(logic)
//{
//}
//
//
//GameState::~GameState()
//{
//}
//
//void GameState::Initialize(char * State)
//{
//	this->State = State;
//	//scene.Initialize();
//}
//
//void GameState::Inputfunc()
//{
//}
//
//void GameState::Draw(HDC hdc)
//{
//}
//
//void GameState::Draw3D()
//{
//}
//
//UIElement * GameState::GenerateForm()
//{
//	vec2 Position;
//	UI.root = new UIElement("Root", "");
//
//	/*UIElement* GreyCover = new UIElement("GreyCover", "Interface/GreyCover.png",0);
//	Position = vec2(0, 0);
//	GreyCover->TopLeft = Position;
//	GreyCover->SetByTrueSize(Position);
//	GreyCover->innerText = "PAUSE";
//	root->AppendChild(GreyCover);*/
//
//	UIElement* UsernameElement = new UIElement("Username", "Interface/Textbox.png");
//	Position = vec2(10, 80);
//	UsernameElement->TopLeft = Position;
//	UsernameElement->SetByTrueSize(Position);
//	UsernameElement->AddHoverEvent([]
//	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/TextboxHovered.png"); });
//	UsernameElement->AddHoverDoneEvent([]
//	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/Textbox.png"); });
//	UsernameElement->AddReturnDefaultEvent([]
//	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/Textbox.png"); });
//	UsernameElement->AddClickEvent([]
//	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/TextboxSelected.png"); });
//	UsernameElement->AddTextChangedEvent([]
//	(UIElement* Element)mutable-> void {
//		if (Element->innerText.back() == '\r')
//		{
//			TCP tcp; tcp.SendPacket(Element->innerText); Element->innerText.pop_back();
//		}
//	});
//	UI.root->AppendChild(UsernameElement);
//
//	UIElement* PasswordElement = new UIElement("Password", "Interface/Textbox.png");
//	Position = vec2(10, 160);
//	PasswordElement->TopLeft = Position;
//	PasswordElement->SetByTrueSize(Position);
//	PasswordElement->AddHoverEvent([]
//	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/TextboxHovered.png"); });
//	PasswordElement->AddHoverDoneEvent([]
//	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/Textbox.png"); });
//	PasswordElement->AddReturnDefaultEvent([]
//	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/Textbox.png"); });
//	PasswordElement->AddClickEvent([]
//	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/TextboxSelected.png"); });
//	UI.root->AppendChild(PasswordElement);
//
//	//UIElement* StatsWindow = new UIElement("StatsWindow", "Interface/StatsWindow.png");
//	//Position = vec2(710, 300);
//	//StatsWindow->TopLeft = Position;
//	//StatsWindow->SetByTrueSize(Position);
//	//root->AppendChild(StatsWindow);
//
//	//for (int i = 0; i < 4; i++)
//	//{
//	//	UIElement* StatsField = new UIElement("StatsField"+i, "Interface/StatsField.png");
//	//	Position = vec2(710, 300 + (i * 50));
//	//	StatsField->TopLeft = Position;
//	//	StatsField->SetByTrueSize(Position);
//	//	StatsField->AddHoverEvent([]
//	//	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/StatsFieldHovered.png"); });
//	//	StatsField->AddHoverDoneEvent([]
//	//	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/StatsField.png"); });
//	//	StatsField->AddReturnDefaultEvent([]
//	//	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/StatsField.png"); });
//	//	StatsField->AddClickEvent([]
//	//	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/StatsFieldSelected.png"); });
//	//	StatsWindow->AppendChild(StatsField);
//	//}
//	// load up for later use
//	UIElement* EmptyHPBar = new UIElement("EmptyHPBar", "Interface/EmptyHPBar.png");
//	UIElement* FullHPBar = new UIElement("FullHPBar", "Interface/FullHPBar.png");
//	return UI.root;
//}

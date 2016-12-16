//#include "Login_Screen.h"
//
//
//HDC Login_Screen::m_HDC;
//Login_Screen::Login_Screen()
//{
//	for (int i = 0; i < 255; i++)
//	{
//		KeyIsPressed[i] = false;
//		kbInput[i] = pressed_default;
//	}
//	kbInput[BACKSPACE] = &Login_Screen::pressed_backspace;
//	kbInput[SPACE] = &Login_Screen::pressed_space;
//	for (int i = '!'; i < 'z'; i++)
//	{
//		kbInput[i] = &Login_Screen::pressed_key;
//	}
//}
//
//
//Login_Screen::~Login_Screen()
//{
//}
//
//void Login_Screen::ConnectToServer()
//{
//	glewExperimental = TRUE;
//	GLenum err = glewInit();
//	glLoadIdentity();
//	
//	mLogin_Screen_Graphics.Initialize();
//	mLogin_Screen_Graphics.DrawDisconnectedLoginScreen();
//	//mClient._Initialize(); //TODO: make a server protocol
//	//mClient._SendMessage("Login Screen");
//	//// wait for server response
//	//while (mClient._RecieveMessage() != "Connected");
//	// ready to go
//	//mLogin_Screen_Graphics.DrawConnectedLoginScreen();
//}
//
//void Login_Screen::LoopScreen()
//{
//	Draw();
//	
//	if (mouse.LeftIsPressed()) // TODO: make it efficient code
//	{
//		// Username
//		bool isSelected = false;
//		/*for each (Textbox* textBox in mLogin_Screen_Graphics.textBoxes)
//		{
//			textBox->isSelected(false);
//			if (textBox->OnSelection())
//			{
//				this->mCurrentSelection = textBox->GetIndex();
//				mLogin_Screen_Graphics.SelectTextBox(mLogin_Screen_Graphics.textBoxes[mCurrentSelection]);
//				textBox->isSelected(true);
//				isSelected = true;
//			}
//		}*/
//		if (!isSelected)
//		{
//			this->mCurrentSelection = 0;
//			mLogin_Screen_Graphics.SelectTextBox(NULL);
//
//		}
//		// Login button
//
//		mLogin_Screen_Graphics.b_TryLogin->isSelected(false);
//		if (mLogin_Screen_Graphics.b_TryLogin->OnSelection())
//		{
//			mLogin_Screen_Graphics.b_TryLogin->isSelected(true);
//			isSelected = true;
//		}
//		
//		if (!isSelected)
//		{
//			this->mCurrentSelection = 0;
//			mLogin_Screen_Graphics.SelectTextBox(NULL);
//
//		}
//		
//		// Attempt Login
//		if (mouse.IsInRectangle(250, 50, 300, 100))
//		{
//			CheckUsernamePasswordMatch();
//		}
//	
//	}
//	if (keyboard.isKeyPressed((VirtualKeys)TAB) && KeyIsPressed[TAB] == false)
//	{
//		(++mCurrentSelection)%=mLogin_Screen_Graphics.textBoxes.size();
//		mLogin_Screen_Graphics.SelectTextBox(mLogin_Screen_Graphics.textBoxes[mCurrentSelection]);
//		KeyIsPressed[TAB] = true;
//	}
//	if (!keyboard.isKeyPressed(TAB))
//	{
//		KeyIsPressed[TAB] = false;
//	}
//}
//void Login_Screen::Draw()
//{
//	glEnable(GL_DEPTH_TEST);
//	glEnable(GL_STENCIL_TEST);
//	//glClearColor(255, 0, 0, 0);
//
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
//	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
//
//	glDepthMask(GL_TRUE);
//
//	mLogin_Screen_Graphics.DrawConnectedLoginScreen(mCurrentSelection, mField);
//	
//
//	glFlush();
//	SwapBuffers(m_HDC);
//}
//
//void Login_Screen::CheckUsernamePasswordMatch()
//{
//	mClient._SendMessage(this->Username + "|" + this->Password);
//	if (mClient._RecieveMessage() == "1")
//	{
//		// Log in
//	}
//	else
//	{
//		// Pop message: "Username or Password do not Match"
//	}
//}
//
//void Login_Screen::CreateAccount()
//{
//
//}
//
//void Login_Screen::SetPassword()
//{
//
//}
//
//void Login_Screen::SetUsername()
//{
//}
//
///*---Input Functions---*/
//void Login_Screen::pressed_backspace(Login_Screen* a_ls,char)
//{
//	a_ls->mLogin_Screen_Graphics.SelectedTextBox->EraseChar();
//}
//void Login_Screen::pressed_space(Login_Screen* a_ls, char)
//{
//	a_ls->mLogin_Screen_Graphics.SelectedTextBox->InputChar(' ');
//}
//void Login_Screen::pressed_enter(Login_Screen* a_ls, char)
//{
//
//}
//void Login_Screen::pressed_tab(Login_Screen* a_ls, char)
//{
//
//}
//void Login_Screen::pressed_key(Login_Screen* a_ls, char key)
//{
//	if (a_ls->mLogin_Screen_Graphics.SelectedTextBox != NULL)
//	{
//		if (key >= 'A' && key <= 'Z')
//			key += 'a' - 'A';
//		if (a_ls->keyboard.isKeyPressed(SHIFT) && key >= 'a' && key <= 'z')
//		{
//			key += 'A' - 'a';
//		}
//		else if (a_ls->keyboard.isKeyPressed(SHIFT) && key >= 'A' && key <= 'Z')
//		{
//			key += 'a' - 'A';
//		}
//		a_ls->mLogin_Screen_Graphics.SelectedTextBox->InputChar(key);
//	}
//}
//
//void Login_Screen::pressed_default(Login_Screen * a_ls, char key)
//{
//
//}

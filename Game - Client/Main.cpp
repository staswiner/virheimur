#define _WINSOCKAPI_
//#define _WINSOCKAPI2_
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Windowsx.h>
#include "MainLoop.h"
#include "Keyboard.h"
#include "Mouse.h"

#include <GL\glut.h>
#include <iostream>
#include <sstream>



static Keyboard keyboard;
static Mouse mouse;
static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
static MainLoop Loop;
bool    done;                   //flag for completion of app
bool fullScreen = false;
void SetupPixelFormat(HDC hDC);
int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nCmdShow)
{
	WNDCLASSEX windowClass; //window class
	HWND    hwnd;                   //window handle
	MSG     msg;                    //message
	DWORD   dwExStyle;              //window extended style
	DWORD   dwStyle;                //window style
	RECT    windowRect;

	/*      Screen/display attributes*/
	int width = 1024;
	int height = 600;
	mouse.SetWindowSize(width, height);
	int bits = 32;
	windowRect.left = (long)0;               //set left value to 0
	windowRect.right = (long)width;  //set right value to requested width
	windowRect.top = (long)0;                //set top value to 0
	windowRect.bottom = (long)height;//set bottom value to requested height

									 /*      Fill out the window class structure*/
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	windowClass.lpfnWndProc = WindowProc;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = hInstance;
	windowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	windowClass.hCursor = LoadCursor(nullptr,IDC_ARROW);//(HCURSOR)LoadImage(NULL, "/cursor1.cur", IMAGE_CURSOR, 0, 0, LR_SHARED);//LoadCursorFromFile("cursor1.cur");// (NULL, IDC_ICON);
	windowClass.hbrBackground = NULL;
	windowClass.lpszMenuName = NULL;
	windowClass.lpszClassName = "MyClass";
	windowClass.hIconSm = LoadIcon(NULL, IDI_WINLOGO);
	
	/*      Register window class*/
	if (!RegisterClassEx(&windowClass))
	{
		return 0;
	}
	/*      Check if fullscreen is on*/
	if (fullScreen)
	{
		DEVMODE dmScreenSettings;
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = width;   //screen width
		dmScreenSettings.dmPelsHeight = height; //screen height
		dmScreenSettings.dmBitsPerPel = bits;   //bits per pixel
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN !=
			DISP_CHANGE_SUCCESSFUL))
		{
			/*      Setting display mode failed, switch to windowed*/
			MessageBox(NULL, "Display mode failed", NULL, MB_OK);
			fullScreen = false;
		}
	}

	/*      Check if fullscreen is still on*/
	if (fullScreen)
	{
		dwExStyle = WS_EX_APPWINDOW;    //window extended style
		dwStyle = WS_POPUP;                             //windows style
		ShowCursor(FALSE);                              //hide mouse pointer
	}

	else
	{
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE; //window extended style
		dwStyle = WS_OVERLAPPEDWINDOW;                                  //windows style
	}

	AdjustWindowRectEx(&windowRect, dwStyle, FALSE, dwExStyle);

	/*      Class registerd, so now create our window*/
	hwnd = CreateWindowEx(NULL, "MyClass",  //class name
		"Creating A Game",       //app name
		dwStyle |
		WS_CLIPCHILDREN |
		WS_CLIPSIBLINGS |
		//WS_MAXIMIZE |
		WS_CAPTION,
		100,
		50,                         //x and y coords
		windowRect.right - windowRect.left,
		windowRect.bottom - windowRect.top,//width, height
		NULL,                 //handle to parent
		NULL,                 //handle to menu
		hInstance,    //application instance
		NULL);                //no xtra params

	/*      Check if window creation failed (hwnd = null ?)*/
	if (!hwnd)
	{
		return 0;
	}

	ShowWindow(hwnd, SW_SHOW);      //display window

	UpdateWindow(hwnd);                     //update window

	// Load non-GL Model Data
	//Loop.LoadModels = std::async(&MainLoop::LoadGame, &Loop);
	// Initialize Loop
	Loop.Initialize();
	done = false;   //initialize loop condition variable

	//future<void> LoadModels = std::async(&MainLoop::LoadGame, &Loop);
					/*      Main message loop*/
	//CreateAcceleratorTable()
	while (!done)
	{
		mouse.OnWheelMove(0);
		while (TRUE == PeekMessage(&msg, hwnd, NULL, NULL, PM_REMOVE))
		{
			//TrackMouseEvent()
			//TrackMouseEvent(this);
			if (msg.message == WM_QUIT)     //did we receive a quit message?
			{
				done = true;
			}

			else
			{
				TranslateMessage(&msg);
				//TranslateAccelerator(hwnd,)
				DispatchMessage(&msg);
			}
		}
		//if (!Loop.IsLoaded)
		//{
		//	if (Loop.LoadModels._Is_ready())
		//	{
		//		// Load GL-related Model Data
		//	//	Loop.BindGame();
		//		Loop.IsLoaded = true;

		//	}
		//}
		//Loop.Draw_Scene();
		Loop.GameLoop();
	//	loginScreen.LoopScreen();
	}

	if (fullScreen)
	{
		ChangeDisplaySettings(NULL, 0);
		ShowCursor(TRUE);
	}

	return msg.wParam;

}
#define CALL_MEMBER_FN(object,ptrToMember)  ((object).*(ptrToMember))

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	int width, height;
	static HDC	hDC;	//device context
	static HGLRC	hRC;	//rendering context
	std::ostringstream DeltaB;
	GLdouble glProjectMatrix[16] = {};
	//mouse.SetInWindow(true);
	switch (uMsg)
	{
	case WM_CREATE: //window being created

		hDC = GetDC(hwnd);  //get current windows device context
		//Login_Screen::m_HDC = hDC;
		Loop.game.SetHDC(hDC);
		SetupPixelFormat(hDC); //call our pixel format setup function
							   /*      Create rendering context and make it current
							   */
		hRC = wglCreateContext(hDC);
		wglMakeCurrent(hDC, hRC);
		mouse.OnWheelMove(GET_WHEEL_DELTA_WPARAM(wParam));

		/*	   glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		glDepthMask(GL_TRUE);*/

		return 0;
		break;

	case WM_CLOSE:  //window is closing

					/*      Deselect rendering context and delete it*/
		wglMakeCurrent(hDC, NULL);
//		wglDeleteContext(hRC);

		/*      Send quit message to queue*/
		//Loop.client._CloseConnection(MainLoop::ClientID);
		done = true;
		PostQuitMessage(0);
		return 0;
		break;

		// case WM_SYSKEYDOWN:
	case WM_CHAR:
		keyboard.PushBackLetter(wParam);
	case WM_KEYDOWN:
		keyboard.OnKeyPressed(wParam);
	//	(loginScreen.kbInput[wParam]) (&loginScreen,wParam);
		keyboard.PushBackCommand(wParam);
		break;
		//   case WM_SYSKEYUP:
	case WM_KEYUP:
		keyboard.OnKeyReleased(wParam);
		break;

	case WM_SIZE:

		/*      Retrieve width and height*/
		height = HIWORD(lParam);
		width = LOWORD(lParam);

		/*      Don't want a divide by 0*/
		if (height == 0)
		{
			height = 1;
		}
		mouse.SetWindowSize(width, height);
		/*      Reset the viewport to new dimensions*/
		glViewport(0, 0, width, height);
		/*      Set current Matrix to projection*/
		
		//Loop.mPostProcessing.ChangeBuffersSize();
		return 0;
		break;
	case WM_COMMAND:
		cout << "hello";
	case WM_NCMOUSELEAVE:
		mouse.OnMouseMove(400, 300); break;
	case WM_LBUTTONDOWN:
		mouse.OnLeftPressed(); break;
	case WM_LBUTTONUP:
		mouse.OnLeftReleased(); break;
	case WM_RBUTTONDOWN:
		mouse.OnRightPressed(); break;
	case WM_RBUTTONUP:
		mouse.OnRightReleased(); break;
	case WM_LBUTTONDBLCLK:
		mouse.PushCommand(wParam); break;
	case WM_MOUSEMOVE:
		mouse.OnMouseMove(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		{
			/*if (mouse.GetMouseX() > mouse.GetWindowSize().x || mouse.GetMouseX() < 0 || mouse.GetMouseY() > mouse.GetWindowSize().y || mouse.GetMouseY() < 0)
			{
				mouse.SetInWindow(false);
			}
			else
			{
				mouse.SetInWindow(true);
			}*/
		}

		break;
	case WM_MOUSEWHEEL:
		mouse.OnWheelMove(GET_WHEEL_DELTA_WPARAM(wParam));

		/*   DeltaB << GET_WHEEL_DELTA_WPARAM(wParam) << endl;
		OutputDebugString(DeltaB.str().c_str());*/
		break;
	//case MM_WIM_OPEN:
	//	cout << "hello";
	//	break;
	//case MM_WIM_DATA:
	//	cout << "hello"; 
	//	break;
	default:

		break;
	}
	return (DefWindowProc(hwnd, uMsg, wParam, lParam));
}
void SetupPixelFormat(HDC hDC)
{
	/*      Pixel format index
	*/
	int nPixelFormat;

	static PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),          //size of structure
		1,                                      //default version
		PFD_DRAW_TO_WINDOW |                    //window drawing support
		PFD_SUPPORT_OPENGL |                    //opengl support
		PFD_DOUBLEBUFFER,                       //double buffering support
		PFD_TYPE_RGBA,                          //RGBA color mode
		32,                                     //32 bit color mode
		0, 0, 0, 0, 0, 0,                       //ignore color bits
		0,                                      //no alpha buffer
		0,                                      //ignore shift bit
		0,                                      //no accumulation buffer
		0, 0, 0, 0,                             //ignore accumulation bits
		16,                                     //16 bit z-buffer size
		0,                                      //no stencil buffer
		0,                                      //no aux buffer
		PFD_MAIN_PLANE,                         //main drawing plane
		0,                                      //reserved
		0, 0, 0 };                              //layer masks ignored

												/*      Choose best matching format*/
	nPixelFormat = ChoosePixelFormat(hDC, &pfd);

	/*      Set the pixel format to the device context*/
	SetPixelFormat(hDC, nPixelFormat, &pfd);
}
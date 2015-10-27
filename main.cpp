#define WIN32_LEAN_AND_MEAN
#define INITGUID

// Library includes
#include <windows.h>		// include all the windows headers.
#include <windowsx.h>	// include usefull macros.
#include <string>
#include <ctime>
#include <cstdlib>

#ifdef _DEBUG
#include <vld.h>
#endif // _DEBUG

// Local Includes
#include "engine/CINIParser.h"
#include "engine/totalcubedomination.h"
#include "singletons.h"
#include "defines.h"

#define WINDOW_CLASS_NAME "WINCLASS1"

HWND CreateAndRegisterWindow(HINSTANCE _hInstance, int32 _iWidth, int32 _iHeight, 
							 const char* _pcTitle, bool _bFullScreen);

LRESULT CALLBACK WindowProc(HWND _hwnd, uint32 _msg, WPARAM _wparam, LPARAM _lparam)
{
	switch (_msg)
	{
		case WM_DESTROY:
		{
			PostQuitMessage(0);

			return(0);
		}
		break;

	default: break;
	}

	return(DefWindowProc(_hwnd, _msg, _wparam, _lparam) );
}

int32 WINAPI WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance, LPSTR _lpCmdLine, int32 _nCmdShow)
{
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG) );

    srand(static_cast<uint32>(time(0) ) );
	
	CINIParser iniparser;

	if (!iniparser.LoadIniFile("settings"))
	{
		MessageBox(0, "Could not open settings.ini", "Error", MB_ICONERROR | MB_OK);

		DestroySingletons();

		return (0);
	}

	int32 iWidth;
	int32 iHeight;
	bool bFullScreen;

	iniparser.GetIntValue("window", "width", iWidth);
	iniparser.GetIntValue("window", "height", iHeight);
	iniparser.GetBoolValue("window", "fullscreen", bFullScreen);

	HWND hwnd = CreateAndRegisterWindow(_hInstance, iWidth, iHeight, "Total Cube Domination", bFullScreen);

	CTotalCubeDomination& rGame = CTotalCubeDomination::GetInstance();

	if (!rGame.Initialise(_hInstance, hwnd, iWidth, iHeight, bFullScreen) )
	{
		DestroySingletons();

		return (0);
	}

	// Main event loop
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) )
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			rGame.ExecuteOneFrame();
		}
	}

	DestroySingletons();

	return (static_cast<int32>(msg.wParam));
}


HWND CreateAndRegisterWindow(HINSTANCE _hInstance, int32 _iWidth, int32 _iHeight, 
							const char* _pcTitle, bool _bFullScreen)
{
	WNDCLASSEX winclass;
	HWND hwnd;

	// First fill in the window class structure.
	winclass.cbSize = sizeof(WNDCLASSEX);
	winclass.style = CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	winclass.lpfnWndProc = WindowProc;
	winclass.cbClsExtra = 0;
	winclass.cbWndExtra = 0;
	winclass.hInstance = _hInstance;
	winclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	winclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	winclass.hbrBackground = static_cast<HBRUSH>(GetStockObject(NULL_BRUSH) );
	winclass.lpszMenuName = NULL;
	winclass.lpszClassName = WINDOW_CLASS_NAME;
	winclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	// register the window class
	if (!RegisterClassEx(&winclass) )
	{
		return(0);
	}

	DWORD dwFlags;
	int32 iWindowXBorder = 0;
	int32 iWindowYBorder = 0;

	if (!_bFullScreen)
	{
		iWindowXBorder = GetSystemMetrics(SM_CXFRAME) + 
		GetSystemMetrics(SM_CXBORDER);

		iWindowYBorder = GetSystemMetrics(SM_CYCAPTION) + 
		GetSystemMetrics(SM_CYBORDER) + GetSystemMetrics(SM_CYFRAME);

        dwFlags = WS_BORDER | WS_CAPTION | WS_SYSMENU | WS_VISIBLE;
	}
	else
	{
        dwFlags = WS_EX_TOPMOST | WS_POPUP | WS_VISIBLE;
	}

	// create the window
	hwnd = CreateWindowEx(NULL,
		WINDOW_CLASS_NAME,
		_pcTitle,
		dwFlags,
		CW_USEDEFAULT,CW_USEDEFAULT,		
		_iWidth + iWindowXBorder, _iHeight + iWindowYBorder,
		NULL,
		NULL,
		_hInstance,
		NULL);

	return(hwnd);
}
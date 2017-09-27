// FormTest.cpp : Defines the entry point for the application.
//
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include "FormTest.h"
#include <windows.h>
#include <shellapi.h>
#include <thread>
#include "resource.h"

#define ID_TRAY_APP_ICON    1001
#define ID_TRAY_EXIT        1002
#define ID_TRAY_TITLE       1003
#define WM_SYSICON          (WM_USER + 1)
#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
wchar_t* szWindowClass = L"PHONIX";
HWND hWnd;
NOTIFYICONDATA notifyIconData;
HMENU Hmenu;
UINT WM_TASKBAR = 0;
int selectedDevice = 0;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

void InitNotifyIconData();
void BuildTrayMenu();


static Device Devices[10] = {
};
static int devices_size = sizeof(Devices)/sizeof(*Devices);
static int last_index()
{
	for (int i = 0; i < devices_size; i++)
		if (Devices[i].Guid == 0)
			return i;
}

int increment = 0;
int AddDevice(Device d)
{
	if (increment >= devices_size) return 0;
	Devices[increment] = d;
	increment++;
	return increment - 1;
}

void SetSelectedDevice(int device)
{
	selectedDevice = device;
}

Device GetSelectedDevice()
{
	return Devices[selectedDevice];
}

int GetSelectedDeviceIndex()
{
	return selectedDevice;
}

void ResetDevices()
{
	increment = 0;
	delete[] &Devices;
}

void BuildTrayMenu()
{
	Hmenu = CreatePopupMenu();
	AppendMenu(Hmenu, MF_DEFAULT, ID_TRAY_TITLE, L"Phonix v0.1");
	for (int i = 0; i < last_index(); i++)
		AppendMenu(Hmenu, MF_UNCHECKED, i + ID_TRAY_EXIT + 2, Devices[i].Name);
	ModifyMenu(Hmenu, selectedDevice + 2 + ID_TRAY_EXIT, MF_BYCOMMAND | MF_CHECKED, selectedDevice + 2 + ID_TRAY_EXIT, Devices[selectedDevice].Name);
	AppendMenu(Hmenu, MF_SEPARATOR, 1100, L"");
	AppendMenu(Hmenu, MF_STRING, ID_TRAY_EXIT, L"Exit");
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    //LoadStringW(hInstance, IDC_FORMTEST, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    MSG msg;

    // Main message loop:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_ENABLE;//CS_HREDRAW | CS_VREDRAW //CS_NOCLOSE
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName   = L"Phonix v0.1 ~ Async";
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable
   int width = 400;
   int height = 300;
   RECT rect;
   GetWindowRect(GetDesktopWindow(), &rect);
   int xPos = (rect.right / 2) - (width / 2);
   int yPos = (rect.bottom / 2) - (height / 2);

   hWnd = CreateWindowW(szWindowClass, L"Phonix v0.1", WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION | WS_VISIBLE, // WS_MINIMIZEBOX
	   xPos, yPos, width, height, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }
   InitNotifyIconData();
   //ShowWindow(hWnd, nCmdShow);
   std::this_thread::sleep_for(std::chrono::milliseconds(2000));
   ShowWindow(hWnd, SW_HIDE);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_TASKBAR && !IsWindowVisible(hWnd))
	{
		ShowWindow(hWnd, SW_HIDE);
		return 0;
	}
    switch (message)
    {
	case WM_ACTIVATE:
		Shell_NotifyIcon(NIM_ADD, &notifyIconData);
		break;
	case WM_CREATE:
		ShowWindow(hWnd, SW_HIDE);
		BuildTrayMenu();
		break;
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		switch (wmId)
		{
		case ID_HELP_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case ID_FILE_EXIT:
			DestroyWindow(hWnd);
			break;
		}
	}
	break;
	case WM_SYSCOMMAND:
		switch (wParam & 0xFFF0)
		{
		case SC_MOVE:
			return 0;
		case SC_MINIMIZE:
		case SC_CLOSE:
			ShowWindow(hWnd, SW_HIDE);
			return 0;
			break;
		}
		break;
	case WM_SYSICON:
	{
		if(wParam == ID_TRAY_APP_ICON && lParam == WM_LBUTTONDOWN)
			SetForegroundWindow(hWnd);
		else if (lParam == WM_RBUTTONDOWN)
		{
			POINT curPoint;
			GetCursorPos(&curPoint);
			UINT clicked = TrackPopupMenu(Hmenu, TPM_RETURNCMD | TPM_NONOTIFY, curPoint.x, curPoint.y, 0, hWnd, NULL);
			SendMessage(hWnd, WM_NULL, 0, 0); // send benign message to window to make sure the menu goes away.
			if (clicked == ID_TRAY_EXIT)
			{
				//ResetDevices();
				Shell_NotifyIcon(NIM_DELETE, &notifyIconData);
				PostQuitMessage(0);
			}
			else if (clicked == ID_TRAY_TITLE)
			{
				ShowWindow(hWnd, SW_SHOW);
				SetForegroundWindow(hWnd);
			}
			else if (clicked > ID_TRAY_EXIT)
			{
				selectedDevice = clicked - ID_TRAY_EXIT - 2;
				for (int i = 0; i < 4; i++)
				{
					if (i == selectedDevice)
						ModifyMenu(Hmenu, clicked, MF_BYCOMMAND | MF_CHECKED, clicked, Devices[i].Name);
					else
						ModifyMenu(Hmenu, ID_TRAY_EXIT + i + 2, MF_BYCOMMAND | MF_UNCHECKED, ID_TRAY_EXIT + i + 2, Devices[i].Name);
				}
				UpdateDevice();
			}
		}
	}
	break;
	case WM_CLOSE:
		ShowWindow(hWnd, SW_HIDE);
		return 0;
		break;
	case WM_NCHITTEST:
	{
		UINT uHitTest = DefWindowProc(hWnd, WM_NCHITTEST, wParam, lParam);
		if (uHitTest == HTCLIENT)
			return HTCAPTION;
		else
			return uHitTest;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
    }
	return DefWindowProc(hWnd, message, wParam, lParam);
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

WCHAR szTIP[64] = _T("Phonix v0.1");
void InitNotifyIconData()
{
		memset(&notifyIconData, 0, sizeof(NOTIFYICONDATA));
		notifyIconData.cbSize = sizeof(NOTIFYICONDATA);
		notifyIconData.hWnd = hWnd;
		notifyIconData.uID = ID_TRAY_APP_ICON;
		notifyIconData.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
		notifyIconData.uCallbackMessage = WM_SYSICON; //Set up our invented Windows Message
		notifyIconData.hIcon = (HICON)LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
		wcsncpy_s(notifyIconData.szTip, szTIP, sizeof(szTIP));
}
// CossioJiggle.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "CossioJiggle.h"
#include <windowsx.h>

#define MAX_LOADSTRING 100

HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR    lpCmdLine,  _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.
  

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_COSSIOJIGGLE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_COSSIOJIGGLE));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_COSSIOJIGGLE));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = NULL;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_BORDER,
      CW_USEDEFAULT, 0, 100, 100, nullptr, nullptr, hInstance, nullptr);

   SetTimer(hWnd, IDT_TIMER1, 10000, (TIMERPROC)NULL);

   HWND hwndJig = CreateWindowW(
       L"BUTTON",  // Predefined class; Unicode assumed 
       L"Jig",      // Button text 
       WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_PUSHLIKE,  // Styles 
       10,         // x position 
       10,         // y position 
       40,        // Button width
       40,        // Button height
       hWnd,     // Parent window
       (HMENU)BUTTON_JIG,       // Id
       (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
       NULL);      // Pointer not needed.
   HWND hwndExit = CreateWindowW(
       L"BUTTON",  // Predefined class; Unicode assumed 
       L"Exit",      // Button text 
       WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,  // Styles 
       70,         // x position 
       10,         // y position 
       40,        // Button width
       40,        // Button height
       hWnd,     // Parent window
       (HMENU)BUTTON_EXIT,       // Id
       (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
       NULL);      // Pointer not needed.

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            switch (wmId)
            {
            case BUTTON_EXIT:
                DestroyWindow(hWnd);
                break;
            case BUTTON_JIG:
                if (Button_GetCheck((HWND)lParam) == BST_CHECKED)
                    MessageBox(NULL, (LPCWSTR)L"Pushed", (LPCWSTR)L"Pushed", MB_ICONINFORMATION);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_TIMER:    
        MessageBox(NULL, (LPCWSTR)L"Time!", (LPCWSTR)L"Time", MB_ICONINFORMATION);
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}


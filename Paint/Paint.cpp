// Paint.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Paint.h"
#include <Windowsx.h>
#include <Windows.h>
#include <CommCtrl.h>

#define MAX_LOADSTRING 100
#define CMD_BUTTON_1 1001
#define CMD_BUTTON_2 1002
#define CMD_BUTTON_3 1003
#define CMD_BUTTON_4 1004
#define CMD_BUTTON_5 1005
#define CMD_BUTTON_6 1006


// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];  // the main window class name
HWND hwndRoundRect;
bool isLeftHold, isRightHold;

HDC dc;
HPEN pen;
int pen_size = 20;
int red = RGB(255, 0, 0);
int blue = RGB(0, 0, 255);
int black = RGB(0, 0, 0);
int white = RGB(255, 255, 255);
int current_color;




// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PAINT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PAINT));

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



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PAINT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_PAINT);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {
      
        
        isLeftHold = isRightHold = false;

        dc = GetDC(hWnd);

        pen = CreatePen(PS_SOLID, 20, black);
       
        CreateWindowW(L"Button", L"Red",
            WS_CHILD | WS_VISIBLE | SS_CENTER,
            10, 70, 70, 23, hWnd, (HMENU)CMD_BUTTON_1, hInst, NULL);
        CreateWindowW(L"Button", L"Blue",
            WS_CHILD | WS_VISIBLE | SS_CENTER,
            10, 100, 70, 23, hWnd, (HMENU)CMD_BUTTON_2, hInst, NULL);
        CreateWindowW(L"Button", L"Black",
            WS_CHILD | WS_VISIBLE | SS_CENTER,
            10, 130, 70, 23, hWnd, (HMENU)CMD_BUTTON_3, hInst, NULL);
        CreateWindowW(L"Button", L"Ellipse",
            WS_CHILD | WS_VISIBLE | SS_CENTER,
            10, 160, 70, 23, hWnd, (HMENU)CMD_BUTTON_4, hInst, NULL);
        CreateWindowW(L"Button", L"Rectangle",
            WS_CHILD | WS_VISIBLE | SS_CENTER,
            10, 190, 80, 23, hWnd, (HMENU)CMD_BUTTON_5, hInst, NULL);
        hwndRoundRect = CreateWindowW(L"Button", L"RoundRect",
            WS_CHILD | WS_VISIBLE | SS_CENTER,
            10, 220, 80, 23, hWnd, (HMENU)CMD_BUTTON_6, hInst, NULL);

        



        break;
    }
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case CMD_BUTTON_1:
            
                pen = CreatePen(PS_SOLID, 20, red);
                current_color = red;
                break;
            case CMD_BUTTON_2:
                pen = CreatePen(PS_SOLID, 20, blue);
                current_color = blue;
                break;
            
            case CMD_BUTTON_3:

                pen = CreatePen(PS_SOLID, 20, black);
                current_color = black;
                break;
            case CMD_BUTTON_4:
            {
                HBRUSH brush = CreateSolidBrush(current_color);
                SelectObject(dc, brush);
                Ellipse(dc, 100, 100, 200, 300);

                break;
            }
            case CMD_BUTTON_5:
            {
                HBRUSH brush = CreateSolidBrush(current_color);
                SelectObject(dc, brush);
                Rectangle(dc, 400, 100, 200, 300);

                break;
            }
            case CMD_BUTTON_6:
            {
                HBRUSH brush = CreateSolidBrush(current_color);
                SelectObject(dc, brush);
                RoundRect(dc, 500, 200, 300, 100, 300, 400);

                break;
            }
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
            
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_MOUSEMOVE:
    {
        if (isLeftHold) {
            
            HPEN savedPen = (HPEN)SelectObject(dc, pen);

            
            LineTo(dc, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));

            SelectObject(dc, savedPen);
           
            
        }



        //if (wParam & WM_LBUTTONDOWN)


        break;
    }

    case WM_LBUTTONDOWN:
    {
      
        isLeftHold = true;
        MoveToEx(dc, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), NULL);
        SetCapture(hWnd);
        
        LineTo(dc, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
        break;
    }
    case WM_LBUTTONUP:
    {

        isLeftHold = false;
        ReleaseCapture();
        break;
    }

    case WM_RBUTTONDOWN:
    {
        isLeftHold = true;
       MoveToEx(dc, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), NULL);
       SetCapture(hWnd);

       LineTo(dc, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
       pen = CreatePen(PS_SOLID, pen_size, white);
        
    
        break;
    }
    case WM_RBUTTONUP:
    {
        isLeftHold = false;
        ReleaseCapture();
        pen = CreatePen(PS_SOLID, pen_size, current_color);
        break;
    }

    case WM_MOUSEWHEEL:
    {
        if ((int)wParam < 0) pen_size--; else pen_size++;
        pen = CreatePen(PS_SOLID, pen_size, current_color);
        break;
    }
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:

        DeleteObject(pen);
      
        ReleaseDC(hWnd, dc);
        
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
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

#include <windows.h>
#include <iostream>
#include "camcapture.h"

LRESULT CALLBACK WindowProc (HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK HookProc(int nCode, WPARAM wParam, LPARAM lParam);

CAMERA camhwnd;
HWND hwnd;

//WinMain -- Main Window
int WINAPI WinMain ( HINSTANCE hInstance, HINSTANCE hPrevInstance,
                     LPSTR lpCmdLine, int nCmdShow )
{
    MSG msg;

    WNDCLASS wc;
    wc.style = CS_HREDRAW|CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(GetModuleHandle(NULL), IDI_APPLICATION);
    wc.hCursor = LoadCursor (NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH) (COLOR_WINDOW+1);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = TEXT("WebCam");

    RegisterClass (&wc);

    // Create the window
    hwnd = CreateWindow(TEXT("WebCam"),TEXT("WebCam"),WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX,CW_USEDEFAULT,CW_USEDEFAULT,600,600,0,0,hInstance,0);
    ShowWindow (hwnd,SW_SHOW);
    UpdateWindow (hwnd);

    SetWindowsHookEx(WH_KEYBOARD_LL, HookProc, GetModuleHandle(NULL), 0);   // Setup keyboard Hook

    while (GetMessage(&msg,0,0,0))  // Messages loop
    {
        if (!IsDialogMessage(hwnd, &msg))
        {
            TranslateMessage (&msg);
            DispatchMessage (&msg);
        }
    }
    return msg.wParam;
}


//Main Window Procedure WindowProc
LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HINSTANCE hInstance = GetModuleHandle(NULL);

    //some buttons
    HWND hButtStartCam;
    HWND hButtStopCam;
    HWND hButtGrabFrame;
    HWND hButtStartRecord;
    HWND hButtHideRecord;

    switch (message)                  /* handle the messages */
    {

    case WM_CREATE:
    {
        // Create buttons
        hButtStartCam = CreateWindowExA(0,"BUTTON","Start Camera",WS_CHILD | WS_VISIBLE,
                                        0,0,100,20,hwnd,(HMENU)1,hInstance, 0);
        hButtStopCam = CreateWindowExA(0,"BUTTON","Stop Camera",WS_CHILD | WS_VISIBLE,
                                       0,25,100,20,hwnd,(HMENU)2,hInstance, 0);
        hButtGrabFrame = CreateWindowExA(0,"BUTTON","Grab Frame",WS_CHILD | WS_VISIBLE,
                                         0,50,100,20,hwnd,(HMENU)3,hInstance, 0);
        hButtStartRecord = CreateWindowExA(0,"BUTTON","Start Record",WS_CHILD | WS_VISIBLE,
                                           0,75,100,20,hwnd,(HMENU)4,hInstance, 0);
        hButtHideRecord = CreateWindowExA(0,"BUTTON","Hide Record",WS_CHILD | WS_VISIBLE,
                                          0,125,100,20,hwnd,(HMENU)5,hInstance, 0);

        camhwnd = GetCamera(hwnd);
        StartCam(camhwnd);
        break;
    }

    case WM_COMMAND:
    {
        switch (LOWORD(wParam))
        {
        case 1:
            StartCam(camhwnd);
            break;

        case 2:
            StopCam(camhwnd);
            break;

        case 3:
            GetPicture(camhwnd);
            break;

        case 4:
            StartCapture(camhwnd);
            break;

        case 5:
            ShowWindow(hwnd, SW_HIDE);
            break;
        }
        break;
    }

    case WM_DESTROY:
    {
        StopCam(camhwnd);
        PostQuitMessage(0);   /* send a WM_QUIT to the message queue */
        break;
    }

    default:              /* for messages that we don't deal with */
        return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}

LRESULT CALLBACK HookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if(nCode == HC_ACTION && wParam == WM_KEYDOWN)
    {
        DWORD vkCode = ((LPKBDLLHOOKSTRUCT)lParam)->vkCode;
        switch (vkCode)
        {
        case VK_F10:    // Save image
            GetPicture(camhwnd);
            break;

        case VK_F11:    // Start capturing video
            StartCapture(camhwnd);
            break;

        case VK_F12:     // Show hided window
            ShowWindow(hwnd, SW_SHOW);
            break;
        }
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

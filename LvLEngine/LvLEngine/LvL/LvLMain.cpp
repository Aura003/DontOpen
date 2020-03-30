#include<stdio.h>
#include<iostream>
#include<conio.h>
#include<Windows.h>
#include"iLvLEngine.h"
#include"LvLEngineAlpha.h"
int main() 
{

}

LRESULT CALLBACK WindowsProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hprevInstance, LPSTR lpCmdLine, int nCmdShow)
{

    LvLEngineAlpha engine;
    const wchar_t CLASS_NAME[] = L"FirstWindowClass";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowsProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0, //optional window syltes
        CLASS_NAME, //windows calss
        L"Learn to Program Windows", //windows text
        WS_OVERLAPPEDWINDOW, //window style
        CW_USEDEFAULT, //xpos
        CW_USEDEFAULT, //ypos
        CW_USEDEFAULT, //width
        CW_USEDEFAULT, //height
        NULL,       //parent window
        NULL,       //menu
        hInstance, //instance handle from win main
        NULL        //additional application data

    );

    engine.Initialize();
    engine.StartEngine();

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        engine.Update();
    }
    return (int)msg.wParam;
}
LRESULT CALLBACK WindowsProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        FillRect(hdc, &ps.rcPaint, CreateSolidBrush(RGB(100, 200, 255)));
        EndPaint(hwnd, &ps);
    }
    return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
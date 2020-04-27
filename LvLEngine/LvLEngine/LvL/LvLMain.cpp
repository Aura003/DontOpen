#include "stdafx.h"
#include"iLvLEngine.h"
#include"iLvLRenderer.h"
#include"iLvLTexture.h"
#include "LvLTransform.h"
#include "LvLEntitySystem.h"
#include"LvLEngineAlpha.h"
#include"LvLEngineModules.h"

using namespace std;

int main(int nb, char* args[]) 
{
    const char* game = "Game01";
    if (nb >= 2) 
    {
        game = args[1];
    }
    LvLEngineModules::RendererDLL = "LvL2D";
    LvLEngineModules::PhysicsDLL = "LvLPhysics2D";

    LvLWindowParams wp;
    wp.Width = 640;
    wp.Height = 480;
    wp.Red = 50;
    wp.Blue = 255;

    LvLEngineAlpha engine;
    engine.Initialize(wp);

    engine.StartEngine();
    engine.LoadResourceFolder("assets");
    engine.LoadGame(game);

    //b2Vec2 gravity(0, 9.8f);
    //b2World world(gravity);

    ////creation of RigidBody
    //b2BodyDef bodyDef; //config of rigid body
    //bodyDef.type = b2BodyType::b2_dynamicBody;

    //b2Body* body = world.CreateBody(&bodyDef); //rigidbody

    ////creation of collider
    //b2PolygonShape shape; //collider
    //shape.SetAsBox(32, 32);

    //b2Fixture* fixture = body->CreateFixture(&shape, 1.0f); //collider

    //LvLTransform* transform = engine.GetEntitySystem()->GetEntity("bouncy")->GetTransform();

    //SDL_Rect rect;
    //rect.x = rect.y = 0;
    //rect.w = rect.h = 128;

    //LvLDrawOp test; //temporary 
    //strcpy_s(test.ResourceName, "../assets/Ohyea.png");

    while (engine.Update())
     {
        /*world.Step(1.0 / 30, 2, 6);
        b2Vec2 pos = body->GetPosition();
        transform->Position.x = pos.x;
        transform->Position.y = pos.y;*/

        engine.BeginDraw();
        engine.Draw();
        engine.Present();
     }
    //texture->Release();
    engine.ShutDown();

    return _getch();
}

//LRESULT CALLBACK WindowsProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hprevInstance, LPSTR lpCmdLine, int nCmdShow)
//{
//
//    LvLEngineAlpha engine;
//    const wchar_t CLASS_NAME[] = L"FirstWindowClass";
//
//    WNDCLASS wc = {};
//    wc.lpfnWndProc = WindowsProc;
//    wc.hInstance = hInstance;
//    wc.lpszClassName = CLASS_NAME;
//
//    RegisterClass(&wc);
//
//    HWND hwnd = CreateWindowEx(
//        0, //optional window syltes
//        CLASS_NAME, //windows calss
//        L"Learn to Program Windows", //windows text
//        WS_OVERLAPPEDWINDOW, //window style
//        CW_USEDEFAULT, //xpos
//        CW_USEDEFAULT, //ypos
//        CW_USEDEFAULT, //width
//        CW_USEDEFAULT, //height
//        NULL,       //parent window
//        NULL,       //menu
//        hInstance, //instance handle from win main
//        NULL        //additional application data
//
//    );
//
//    engine.Initialize();
//    engine.StartEngine();
//
//    ShowWindow(hwnd, nCmdShow);
//    UpdateWindow(hwnd);
//
//    MSG msg;
//    while (GetMessage(&msg, NULL, 0, 0) > 0)
//    {
//        TranslateMessage(&msg);
//        DispatchMessage(&msg);
//        engine.Update();
//    }
//    return (int)msg.wParam;
//}
//LRESULT CALLBACK WindowsProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
//{
//    switch (uMsg)
//    {
//    case WM_DESTROY:
//        PostQuitMessage(0);
//
//    case WM_PAINT:
//    {
//        PAINTSTRUCT ps;
//        HDC hdc = BeginPaint(hwnd, &ps);
//
//        FillRect(hdc, &ps.rcPaint, CreateSolidBrush(RGB(100, 200, 255)));
//        EndPaint(hwnd, &ps);
//    }
//    return 0;
//    }
//    return DefWindowProc(hwnd, uMsg, wParam, lParam);
//}
#pragma once
#include<stdio.h>
#include<iostream>
#include<string>
#include "Listint.h"
#include"iLvLEngine.h"
#include"EngineAlpha.h"

//#define MYDEF_ONE
#ifdef MYDEF_32 //enables only when 32 bit soln enabled
int ww = 100;
#endif

#define PI 3.14159265f
#define RAD2DEG(r) r* 180/PI
//#undef RAD2DEG

#define CHECK_NBPARAM(count, required);\
if(count - 2 < required)\
{\
    printf("ERROR: Requires %d arguments",required);\
    return EXIT_FAILURE; \
}

#ifdef MYDEF_ONE
const char* name = "David";
#elif defined(MYDEF_TWO)
const char* name = "Mukil";
#else
const char* name = "the Boss";
#endif // MYDEF_ONE

class DInosaurToy
{
    //vector<int> mylist;
//mylist.push_back(100);
//mylist.push_back(2000);
//mylist.pop_back();

//int* p = &mylist[0];

//for (int i = 0; i < mylist.size(); i++) 
//{
//    int xx = *p;
//    p++;
//}
////std::map
//for (vector<int>::iterator it = mylist.begin(); it != mylist.end();it++)
//{
//    int xx = *it;
//}

public:
    void initialize(int hp)
    {
        _hp = hp;
    }
private:
    int _hp = 100;
};
void Function1()
{
    int x = 100;
    int y = x;
    y += 100;
    printf("x=%d, y=%d", x, y);
    if (y > 100)
    {
        int w = y;
        w += 20;
        int j = w;
        printf("j = %d", j);
    }

}
void Function2()
{
    int a[5];
    memset(&a, 0, sizeof(a));

    a[0] = 20;
    a[2] = 30;
    a[4] = 50;

}
void Calculator() 
{
    //float deg = RAD2DEG(1.5f);
    //printf("%f %s", deg, name);
    /*for (size_t i = 0; i < nb; i++)
    {
        printf("%s\n", args[i]);
    }*/
    /*std::string cmd = std::string(args[1]);
    if (cmd == "add")
    {
        CHECK_NBPARAM(nb, 2);
        int a = std::stoi(args[2]);
        int b = std::stoi(args[3]);
        int result = a + b;
        printf("%d + %d = %d", a, b, result);
    }
    else if (cmd == "minus")
    {
        CHECK_NBPARAM(nb, 2);
        int a = std::stoi(args[2]);
        int b = std::stoi(args[3]);
        int result = a - b;
        printf("%d - %d = %d", a, b, result);
    }
    else if (cmd == "time")
    {
        CHECK_NBPARAM(nb, 2);
        int a = std::stoi(args[2]);
        int b = std::stoi(args[3]);
        int result = a * b;
        printf("%d * %d = %d", a, b, result);
    }
    if (cmd == "rad2deg")
    {
        CHECK_NBPARAM(nb, 1);
        float c = std::stof(args[2]);
        float deg = RAD2DEG(c);
        printf("rad2deg(%f) = %f", c, deg);
    }

    _getch();*/
}

void Testarr() 
{
    // int arr[] = { 1,20,30,55 };  //create array with values
   // int arrnb = sizeof(arr) / sizeof(int); //get the nb of elements
    //int* arr = new int[4];
    //arr[0] = 1;
    //arr[1] = 2;
    //arr[2] = 3;
    //arr[3] = 4;
    //int* parr = arr; //get pointer on the first element
    //int arrnb = 4; //heap size of array
    //for (int i = 0; i < arrnb; i++) 
    //{
    //    printf("[%d] = %d \n", i, *parr);
    //    parr++; //jump to next element
    //}
    //delete arr;

   /* int arr[] = { 20,2020,100,1001 };
    int* pparr = (int*)malloc(sizeof(int) * 4);
    memcpy(pparr, &arr, sizeof(int) * 4);
    int* parr = pparr;
    int count = 4;*/
}
void ListintStuff() {
    Listint myList(4);
    myList.Add(5);
    myList.Add(20);
    myList.Add(39);
    myList.Add(99);
    //myList.Insert(4,66);
    //myList.Pop(true);
    int* parr = myList.GetBuffer();
    int count = myList.Count();
    int capacity = myList.GetCapacity();

    for (int i = 0; i < count; i++)
    {
        printf("[%d] = %d \n", i, *parr);
        parr++;
    }
    std::cout << "Capacity is : " << myList.GetCapacity() << std::endl;
    std::cout << "Count is : " << myList.Count() << std::endl;
}

void Function3()
{
    /*DInosaurToy* rarr = new DInosaurToy();
    rarr->initialize(9001);
    delete rarr;*/
    DInosaurToy rarr;
    rarr.initialize(9111);

    DInosaurToy* raar2 = &rarr;
    raar2->initialize(88);
}
void ModMe(int xx, int yy, int* pp)
{
    xx += 1000;
    yy += 3000;


}
void Function4() //copy by value and ref
{
    int x = 100;
    int y = x;
    y += 20;
    printf("%d %d", x, y);

    int& w = x;
    w = 141;
    printf("%d %d", x, w);

    ModMe(x, y, NULL);
    printf("%d %d", x, y);

    int* p = &x; //referencing
    int g = *p; //dereferencing 
    int& r = *p;
    r += 500;
}
void Function5()
{
    int* p = NULL;
    if (p == NULL)
    {
        int w = 100; //will be removed from  stack when out of scope
        p = &w;
    }
    if (true)
    {
        int q = 500;
        printf("%d", q);
    }
    int pp = *p;
    printf("%d", pp);
}
void Function6()
{
    int a[5];
    memset(a, 0, sizeof(a));

    /*a[0] = 5;
    a[1] = 10;
    a[2] = 15;
    a[3] = 20;
    a[4] = 25;*/
    int* p = &a[0];
    int nb = sizeof(a) / sizeof(int);
    for (int i = 0; i < nb; i++)
    {
        (*p) = (i + 1) * 5;
        p++;
        //a[i] = (i+1) * 5;
    }

    for (int i = 0; i < nb; i++)
    {
        (*p) = (i + 1) * 5;
        p++;
        printf("[%d] = %d", i, *p);

    }
}
#include<Windows.h>
LRESULT CALLBACK WindowsProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hprevInstance, LPSTR lpCmdLine, int nCmdShow)
{

    EngineAlpha engine;
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
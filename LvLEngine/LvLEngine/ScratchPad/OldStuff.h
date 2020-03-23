#pragma once
#include<stdio.h>
#include<iostream>

class DInosaurToy
{
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
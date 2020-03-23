#include<stdio.h>
#include<iostream>
#include<string>
#include<conio.h>

#define PI 3.14159265f
#define RAD2DEG(r) r* 180/PI
//#undef RAD2DEG

#define CHECK_NBPARAM(count, required);\
if(count - 2 < required)\
{\
    printf("ERROR: Requires %d arguments",required);\
    return EXIT_FAILURE; \
}

int main(int nb, char* args[]) 
{    
   /* printf("%f", PI);
    float deg = RAD2DEG(18.5f);
    std::cout << deg << std::endl;*/

    std::string operation;

    for (int i = 0; i < nb; i++) 
    {
        printf("%s\n", args[i]);
    }
   /* int a = std::stoi(args[1]);
    int b = std::stoi(args[2]);
    int result = a + b;*/


    operation = std::string(args[1]);
    int result;
    if (operation == "add") 
    {
        CHECK_NBPARAM(nb, 2)
        int k = std::stoi(args[2]);
        int j = std::stoi(args[3]);
        printf("%d, + %d = %d", k, j, result = k + j);
    }
    else if (operation == "subtract") 
    {
        CHECK_NBPARAM(nb, 2)
        int k = std::stoi(args[2]);
        int j = std::stoi(args[3]);
        printf("%d - %d = %d", k, j, result = k - j);
    }
    else if (operation == "multiply") 
    {
        CHECK_NBPARAM(nb,2)
        int k = std::stoi(args[2]);
        int j = std::stoi(args[3]);
        printf("%d * %d = %d", k, j, result = k * j);
    }
    else if (operation == "Rad2Deg")
    {
        CHECK_NBPARAM(nb, 1)
        float m = std::stof(args[2]);
        float gg = RAD2DEG(m);
        printf("Radian to Degree of %f = %f: ",m,gg);
    }
   /* printf("%d + %d =%d\n", a, b, result);*/
    return EXIT_SUCCESS;
 }
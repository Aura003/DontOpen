#include<stdio.h>
#include<iostream>
#include<string>
#include<conio.h>
//#include"iLvLEngine.h"
//#include"EngineAlpha.h"
#include<SDL.h>
#include<SDL_image.h>
#include<assert.h>

//#include "Listint.h"


int main(int nb, char* args[]) 
{    
    if (SDL_Init(SDL_INIT_VIDEO) < 0) 
    {
        printf("SDL could not initialize! SDL-ERROR: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    //create window
    SDL_Window* window = SDL_CreateWindow ("SDL My Window",
                                                                                SDL_WINDOWPOS_CENTERED, //pos x
                                                                                SDL_WINDOWPOS_CENTERED, //pos y
                                                                                1024, //width
                                                                                768, //height
                                                                                SDL_WINDOW_HIDDEN); //fullscreen , etc

    SDL_Renderer* renderer = NULL;
    SDL_Texture* texture = NULL;
    if (window == NULL) 
    {
        printf("Window could not be created! SDL_Error : %s \n", SDL_GetError());
    }
    else 
    {
        SDL_ShowWindow(window);
        //The surface contained by window
        SDL_Surface* screenSurface = NULL;
        //Get window surface
        screenSurface = SDL_GetWindowSurface(window);
        //Fill the surface white
        SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0, 200, 0));
        //Update the surface
        SDL_UpdateWindowSurface(window);
        //Wait for 2 seconds
        SDL_Delay(2000);
       
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
       
        assert(IMG_Init(IMG_INIT_PNG) != 0);

        SDL_Surface* texSurface = IMG_Load("../assets/Ohyea.png");
        texture = SDL_CreateTextureFromSurface(renderer, texSurface);
        SDL_FreeSurface(texSurface);
        texSurface = NULL;
        
        SDL_Rect rect;
        rect.x = rect.y = 0;
        rect.w = rect.h = 64;

        bool running = true;
        SDL_Event event;
        while (running) 
         {
            while (SDL_PollEvent(&event) != 0) 
             {
                switch (event.type) 
                {
                case SDL_QUIT:
                    running = false;
                    break;
                }
             }
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, texture, NULL, &rect);
            SDL_RenderPresent(renderer);
            //update Engine
            //draw Engine
         }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

   return EXIT_SUCCESS;
 }


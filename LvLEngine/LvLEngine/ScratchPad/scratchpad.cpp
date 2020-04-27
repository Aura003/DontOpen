#include "stdafx.h"
#include"iLvLEngine.h"
#include "iLvLRenderer.h"
#include "iLvLTexture.h" //temporary
#include "LvLTransform.h"
#include "LvLEntitySystem.h"
#include"EngineAlpha.h"
#include "Modules.h"


using namespace std;

//typedef void (*MYHELLO)(int);
//void hello(int x) 
//{
//
//}

//bool sortme(int i, int j) 
//{
//    return i > j;
//}
int main(int nb, char* args[]) 
{
    //std::vector<int>blah = { 1,20,99,0,100 };
    //std::sort(blah.begin(), blah.end(),sortme);

    //temporary
    //void (*func)(int) = &hello;// func is a variable name! not a function
    //func(10); // essentially, this is calling hello()

    //MYHELLO hi = &hello;
    //end of temporary

    const char* game = "Game01";

    if (nb >= 2) 
    {
        game = args[1];
    }
    EngineAlphaModule::RendererDLL = "LvL2D";
    EngineAlphaModule::PhysicsDLL = "LvLPhysics2D";

    //LvL_SAFERELEASE(texture);

    LvLWindowParams wp;
    wp.Width = 640;
    wp.Height = 480;
    wp.Red = 50;
    wp.Blue = 255;

    EngineAlpha engine;
    engine.Initialize(wp);

    engine.StartEngine();
    engine.LoadResourceFolder("assets");
    engine.LoadGame(game);

    //iLvLTexture* texture = LvL_LoadTexture("../assets/Ohyea.png");
    //iLvLTexture* texture = engine.LoadTexture("../assets/Ohyea.png");

    //b2Vec2 gravity(0, 9.8f);
    //b2World world(gravity);

    ////creation of RigidBody
    //b2BodyDef bodyDef; //config of rigid body
    //bodyDef.type = b2BodyType::b2_dynamicBody;

    //b2Body* body = world.CreateBody(&bodyDef); //rigidbody

    ////creation of collider
    //b2PolygonShape shape; //collider
    //shape.SetAsBox(32,32);

    //b2Fixture* fixture = body->CreateFixture(&shape, 1.0f); //collider

    //LvLTransform* transform = engine.GetEntitySystem()->GetEntity("bouncy")->GetTransform();

    // SDL_Rect rect;
    // rect.x = rect.y = 0;
    // rect.w = rect.h = 128;
    
   // printf("number of ref %d", texture->GetRefCount());

        //LvLDrawOp test; //temporary 
        //strcpy_s(test.ResourceName, "../assets/Ohyea.png");

    while (engine.Update())
    {
     /*   world.Step(1.0 / 30, 2, 6);
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
    
    
    //if (SDL_Init(SDL_INIT_VIDEO) < 0) 
    //{
    //    printf("SDL could not initialize! SDL-ERROR: %s\n", SDL_GetError());
    //    return EXIT_FAILURE;
    //}
    ////create window
    //SDL_Window* window = SDL_CreateWindow ("SDL My Window",
    //                                                                            SDL_WINDOWPOS_CENTERED, //pos x
    //                                                                            SDL_WINDOWPOS_CENTERED, //pos y
    //                                                                            1024, //width
    //                                                                            768, //height
    //                                                                            SDL_WINDOW_HIDDEN); //fullscreen , etc

    //SDL_Renderer* renderer = NULL;
    //SDL_Texture* texture = NULL;
    //if (window == NULL) 
    //{
    //    printf("Window could not be created! SDL_Error : %s \n", SDL_GetError());
    //}
    //else 
    //{
    //    SDL_ShowWindow(window);
    //    //The surface contained by window
    //    SDL_Surface* screenSurface = NULL;
    //    //Get window surface
    //    screenSurface = SDL_GetWindowSurface(window);
    //    //Fill the surface white
    //    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0, 200, 0));
    //    //Update the surface
    //    SDL_UpdateWindowSurface(window);
    //    //Wait for 2 seconds
    //    SDL_Delay(2000);
    //   
    //    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    //   
    //    assert(IMG_Init(IMG_INIT_PNG) != 0);

    //    SDL_Surface* texSurface = IMG_Load("../assets/Ohyea.png");
    //    texture = SDL_CreateTextureFromSurface(renderer, texSurface);
    //    SDL_FreeSurface(texSurface);
    //    texSurface = NULL;
    //    
    //}
    //    SDL_Rect rect;
    //    rect.x = rect.y = 0;
    //    rect.w = rect.h = 64;

    //    bool running = true;
    //    SDL_Event event;
    //    while (running) 
    //     {
    //        while (SDL_PollEvent(&event) != 0) 
    //         {
    //            switch (event.type) 
    //            {
    //            case SDL_QUIT:
    //                running = false;
    //                break;
    //            }
    //         }
    //        SDL_RenderClear(renderer);
    //        SDL_RenderCopy(renderer, texture, NULL, &rect);
    //        SDL_RenderPresent(renderer);
    //        //update Engine
    //        //draw Engine
    //     }

    //SDL_DestroyWindow(window);
    //SDL_Quit();
 

   return EXIT_SUCCESS;
 }


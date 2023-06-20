#include "game.hpp"
#include <iostream>

int CGame::InitSDL()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        SDL_ShowSimpleMessageBox(
            SDL_MESSAGEBOX_ERROR,
            "Title",
            SDL_GetError(),
            NULL);
        return 1;
    }

    window = SDL_CreateWindow(
        "Inf3",
        0, 0,
        100, 100,
        SDL_WINDOW_MAXIMIZED);
    if (window == NULL)
    {
        SDL_ShowSimpleMessageBox(
            SDL_MESSAGEBOX_ERROR,
            "Title",
            SDL_GetError(),
            NULL);
        return 1;
    }

    renderer = SDL_CreateRenderer(
        window, -1, 0);
    if (renderer == NULL)
    {
        SDL_ShowSimpleMessageBox(
            SDL_MESSAGEBOX_ERROR,
            "Title",
            SDL_GetError(),
            NULL);
        return 1;
    }

    // if portrait x,y else y,x
    if (GetOrientation() == 0)
    {
        SDL_GetRendererOutputSize(
            renderer,
            &screenWidth,
            &screenHeight);
    }
    else
    {
        SDL_GetRendererOutputSize(
            renderer,
            &screenHeight,
            &screenWidth);
    }

    // it worked
    return 0;
}

int CGame::Run()
{
    while(loopgame)
    {
    InputGame();
    UpdateScreen();
    }
    QuitGame();
}

void CGame::QuitGame()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
}

void CGame::LoadRects()
{
    testRect.w = 100;
    testRect.h = 100;

    bigRect.w = 200;
    bigRect.h = 100;
    bigRect.x = 0;
    bigRect.y = 0;

    cellRect.w = 100;
    cellRect.h = 100;
    cellRect.x = 100;
    cellRect.y = 0;
}

int CGame::GetOrientation()
{
    switch (SDL_GetDisplayOrientation(0))
    {
    case SDL_ORIENTATION_PORTRAIT:
    {
        return 0;
    }
    case SDL_ORIENTATION_PORTRAIT_FLIPPED:
        return 1;
    case SDL_ORIENTATION_LANDSCAPE:
        return 2;
    case SDL_ORIENTATION_LANDSCAPE_FLIPPED:
        return 3;
    case SDL_ORIENTATION_UNKNOWN:
        return 4;
    }
}

void CGame::TouchGrid()
{
    if(SDL_HasIntersection(
        &touch, &cellRect))
            loopgame = false;
}

void CGame::InputGame()
{
    while (SDL_PollEvent(&event) != 0)
    {
        switch (event.type)
        {
        case SDL_FINGERDOWN:
        {
            f = event.tfinger;
            
            GetOrientation()==0 ?
                touch.x = f.x *screenWidth, 
                touch.y = f.y * screenHeight :
                
                touch.x = f.x * screenHeight,
                touch.y = f.y * screenWidth;
                
            // touch grid
            if (SDL_HasIntersection(
                    &touch, &bigRect))
            {
                TouchGrid();
            }
        }
        }
    }
}

void CGame::UpdateScreen()
{
    SDL_SetRenderDrawColor(
        renderer,
        0, 0, 0, 255);

    SDL_RenderClear(renderer);

    switch (GetOrientation())
    {
    case 0:
    {
        SDL_SetRenderDrawColor(
            renderer,
            255, 0, 0, 255);

        testRect.x = (screenWidth / 2) - 50;
        testRect.y = (screenHeight / 2) - 50;
        break;
    }
    case 1:
    {
        SDL_SetRenderDrawColor(
            renderer,
            0, 255, 0, 255);
        break;
    }
    case 2:
    {
        SDL_SetRenderDrawColor(
            renderer,
            0, 0, 255, 255);

        testRect.x = (screenHeight / 2) - 50;
        testRect.y = (screenWidth / 2) - 50;
        break;
    case 3:
    {
        SDL_SetRenderDrawColor(
            renderer,
            255, 255, 0, 255);
        testRect.x = (screenHeight / 2) - 50;
        testRect.y = (screenWidth / 2) - 50;
        break;
    }
    }
    default:
    {
        SDL_SetRenderDrawColor(
            renderer,
            0, 0, 0, 255);
        break;
    }
    }

    SDL_RenderFillRect(renderer, &testRect);

    SDL_SetRenderDrawColor(
        renderer,
        255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &bigRect);
    SDL_RenderFillRect(renderer, &cellRect);

    SDL_RenderPresent(renderer);
}
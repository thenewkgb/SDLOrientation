#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

class CGame
{
  public:
    CGame(){};
    ~CGame()
    {
        QuitGame();
    }
    int InitSDL();
    int Run();
    void LoadRects();

  private:
    void QuitGame();
    void InputGame();
    void TouchGrid();
    int GetOrientation();
    void UpdateScreen();
    
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    
    bool loopgame = true;

    int screenWidth{0};
    int screenHeight{0};

    SDL_Event event{};
    SDL_TouchFingerEvent f{};

    SDL_Rect bigRect{};
    SDL_Rect cellRect{};
    SDL_Rect testRect{};
    SDL_Rect touch{1, 1, 1, 1};
};
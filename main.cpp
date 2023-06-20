/*
name: Infinite Line
author: Kevin Barnard

My next attempt at IL will be to separate
the two halfs of the screen. Grid input and the keypad with differing TOUCHUP and
TOUCHDOWN events. Both grid and keypad
work together with the text input in the middle.

also I wanted portrait and landscape modes.

the old version could not handle a keypress
while holding down and moving
*/

#include "game.hpp"

int main(int argc, char *argv[])
{
    CGame game{};

    if (game.InitSDL() == 0)
    {
        game.LoadRects();
        game.Run();
        
    }
    else
    {
        return 1;
    }
    
    return 0;
}
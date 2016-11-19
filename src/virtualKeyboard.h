#ifndef VIRTUALKEYBOARD_H
#define VIRTUALKEYBOARD_H

#include <SDL2/SDL.h>

class virtualKeyboard
{
    public:
        bool keyPressed(char k);
        bool keyPressed(SDL_SCANCODE 
        void newKeyUpEvent(SDL_KEYUP* e);
        void newKeyDownEvent(SDL_KEYDOWN* e);
};

#endif

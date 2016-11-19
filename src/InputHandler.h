#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <SDL2/SDL.h>
#include "VirtualKeyboard.h"

class InputHandler
{
    public:
        static int ParseEvent(SDL_Event* e);
};

#endif

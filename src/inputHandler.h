#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <SDL2/SDL.h>

class inputHandler
{
    public:
        static int ParseEvent(SDL_Event* e);
};

#endif
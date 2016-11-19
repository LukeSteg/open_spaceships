#include "inputHandler.h"
#include <stdio.h>

int inputHandler::ParseEvent(SDL_Event* e)
{
    int returnValue = 1;
    switch(e->type){
    case SDL_KEYDOWN:{
            printf("UNREGISTERED key pressed: %s\n", SDL_GetKeyName(e->key.keysym.sym));
        break;}
    default:{
        returnValue = 0;
        break;}
    }
    return returnValue;
}

#include "inputHandler.h"
#include <stdio.h>

int inputHandler::ParseEvent(SDL_Event* e)
{
    int returnValue = 1;
    switch(e->type){
    case SDL_KEYDOWN:{
        switch(e->key.keysym.sym){
            case SDLK_UP:{
                printf("UP KEY pressed\n");
                break;}
            case SDLK_a:{
                printf("A KEY pressed\n");
                break;}
            default:{
                printf("UNREGISTERED key pressed\n");
            }
        }
        break;}
    default:{
        returnValue = 0;
        break;}
    }
    return returnValue;
}

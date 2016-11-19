#include "InputHandler.h"
#include <stdio.h>


int InputHandler::ParseEvent(SDL_Event* e)
{
    int returnValue = 1;
    switch(e->type){
        case SDL_KEYUP:{
            VirtualKeyboard::newKeyUp(e);
            break;}
        case SDL_KEYDOWN:{
            VirtualKeyboard::newKeyDown(e);
            break;}
        default:{
            returnValue = 0;
            break;}
    }
    return returnValue;
}

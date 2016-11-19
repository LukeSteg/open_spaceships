#include "inputHandler.h"
#include <stdio.h>

int inputHandler::ParseEvent(SDL_Event* e)
{
    int returnValue = 1;
    switch(e->type){
        case SDL_KEYUP:{
            virtualKeyboard::newKeyUpEvent(e);
            break;}
        case SDL_KEYDOWN:{
            virtualKeyboard::newKeyDownEvent(e);
            break;}
        default:{
            returnValue = 0;
            break;}
    }
    return returnValue;
}

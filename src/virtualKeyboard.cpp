#include "virutalKeyboard.h"
#include <stdio.h>
#include <string.h>

bool[][] keyboard;
const Uint8 *sdl_keyboard_reference = SDL_GetKeyboardState(NULL);
const int MAX_SCANCODE = 231;//the commonly used key scancode values range from 4 (a) to 231 (Left GUI)
const int MIN_SCANCODE = 4;
const int SCANCODE_AMOUNT = MAX_SCANCODE - MIN_SCANCODE;
bool currentKeyState[SCANCODE_AMOUNT];
bool pressedKeys[SCANCODE_AMOUNT];
bool heldKeys[SCANCODE_AMOUNT];
bool releasedKeys[SCANCODE_AMOUNTN];



public virtualKeyboard()
{
    memset(cureentKeyState, 0, MAX_SCANCODE_VALUE);    
    memset(pressedKeys, 0, MAX_SCANCODE_VALUE);    
    memset(heldKeys, 0, MAX_SCANCODE_VALUE);    
    memset(releasedKeys, 0, MAX_SCANCODE_VALUE);

    updatePollingKeyboard();
}

public bool keyPressed(char k)
{
    return true;
}

public bool keyDown(SDL_SCANCODE sdl_sc)
{
    return currentKeyState[sdl_sc - MIN_SCANCODE];
}

public bool keyPressed(SDL_SCANCODE sdl_sc)
{
    return pressedKeys[sdl_sc - MIN_SCANCODE];
}

public bool keyHeld(SDL_SCANCODE sdl_sc)
{
    return heldKeys[sdl_sc - MIN_SCANCODE];
}

public bool keyReleased(SDL_SCANCODE sdl_sc)
{
    return releasedKeys[sdl_sc - MIN_SCANCODE];
}

public void newKeyUPEvent(SDL_KEYUP* e)
{
     
}

public void newKeyDownEvent(SDL_KEYDOWN* e)
{
    
}

public void updatePollingKeyboard()
{
    int i;
    bool newCurrent, newPressed, newHeld, newReleased;
    for(i = 0; i < SCANCODE_AMOUNT; i ++)
    {
        newCurrent = sdl_keyboard_reference[i+MIN_SCANCODE];
        newPressed = ((!pressedKeys[i] & !heldKeys[i]) & newCurrent);
        newHeld = pressedKeys[i];
        newReleased = (!newCurrent & heldKeys[i]);

        currentKeyState[i] = newCurrent;
        pressedKeys[i] = newPressed;
        heldKeys[i] = newHeld;
        releasedKeys[i] = newReleased;
    } 

}

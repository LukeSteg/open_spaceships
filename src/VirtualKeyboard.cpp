#include <stdio.h>
#include <string.h>
#include <algorithm>


#include "VirtualKeyboard.h"



std::map<SDL_Keycode, std::list<std::function<void()>> resetKeyboardBuffers()
{

    //memset(currentKeyState, 0, SCANCODE_AMOUNT);    
    //memset(pressedKeys, 0, SCANCODE_AMOUNT);    
    //memset(heldKeys, 0, SCANCODE_AMOUNT);    
    //memset(releasedKeys, 0, SCANCODE_AMOUNT);

    //updatePollingKeyboard();

	std::map<SDL_Keycode, std::list<std::function<void()>> temp_callback_list;
	return temp_callback_list;
}

std::map<SDL_Keycode, std::list<std::function<void()>>> VirtualKeyboard::callback_map = resetKeyboardBuffers();

bool VirtualKeyboard::keyPressed(char k)
{
    return true;
}

bool VirtualKeyboard::keyDown(SDL_Keycode sdl_sc)
{
    //return currentKeyState[sdl_sc - MIN_SCANCODE];
}

bool VirtualKeyboard::keyPressed(SDL_Keycode sdl_sc)
{
   // return pressedKeys[sdl_sc - MIN_SCANCODE];
}

bool VirtualKeyboard::keyHeld(SDL_Keycode sdl_sc)
{
    //return heldKeys[sdl_sc - MIN_SCANCODE];
}

bool VirtualKeyboard::keyReleased(SDL_Keycode sdl_sc)
{
    //return releasedKeys[sdl_sc - MIN_SCANCODE];
}

void VirtualKeyboard::registerKeyUpEvent(SDL_Keycode keycode, std::function<void()> callback)
{	

	callback_map[keycode].push_front(callback);

}

void VirtualKeyboard::registerKeyDownEvent(SDL_Keycode keycode, std::function<void()> callback)
{
    	callback_map[keycode].push_front(callback);
}

void VirtualKeyboard::newKeyDown(SDL_Event* e)
{
	SDL_Keycode keycode = e->key.keysym.sym;
	VirtualKeyboard::callRegisteredEvents(keycode);
}

void VirtualKeyboard::newKeyUp(SDL_Event* e)
{
	SDL_Keycode keycode = e->key.keysym.sym;
	//callRegisteredEvents(keycode);
}

/*void VirtualKeyboard::updateKeyboardAndCallLambadas(){

	VirtualKeyboard::updatePollingKeyboard()

	for(i = 0; i < SCANCODE_AMOUNT; i ++){
		heldKeys[i]
}*/

/*void VirtualKeyboard::updatePollingKeyboard()
{
    int i;
    bool newCurrent, newPressed, newHeld, newReleased;
    *sdl_keyboard_reference = SDL_GetKeyboardState(NULL);
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

}*/



void VirtualKeyboard::callRegisteredEvents(SDL_Keycode keycode)
{
	
	std::list<std::function<void()>> callback_list = callback_map[keycode];
	std::for_each(callback_list.begin(),callback_list.end(),[&] (std::function<void()> item) {item();});
}




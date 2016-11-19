#ifndef VIRTUALKEYBOARD_H
#define VIRTUALKEYBOARD_H

#include <SDL2/SDL.h>
#include <map>
#include <list>
#include <functional>


class VirtualKeyboard
{
    public:

void static resetKeyboardBuffers();
bool static keyPressed(char k);
bool static keyDown(SDL_Keycode sdl_sc);
bool static keyPressed(SDL_Keycode sdl_sc);
bool static keyHeld(SDL_Keycode sdl_sc);
bool static keyReleased(SDL_Keycode sdl_sc);
void static newKeyUp(SDL_Event* e);
void static newKeyDown(SDL_Event* e);
void static updatePollingKeyboard();
void static registerKeyUpEvent(SDL_Keycode keycode, std::function<void()> callback);
void static registerKeyDownEvent(SDL_Keycode keycode, std::function<void()> callback);

	private:

void static callRegisteredEvents(SDL_Keycode keycode);

static bool* keyboard[3];
//static const Uint8 *sdl_keyboard_reference = SDL_GetKeyboardState(NULL);
static const int MAX_SCANCODE = 231;//the commonly used key scancode values range from 4 (a) to 231 (Left GUI)
static const int MIN_SCANCODE = 4;
static const int SCANCODE_AMOUNT = MAX_SCANCODE - MIN_SCANCODE;
static bool currentKeyState[SCANCODE_AMOUNT];
static bool pressedKeys[SCANCODE_AMOUNT];
static bool heldKeys[SCANCODE_AMOUNT];
static bool releasedKeys[SCANCODE_AMOUNT];
static std::map<SDL_Keycode, std::list<std::function<void()>>> callback_map;

};
#endif

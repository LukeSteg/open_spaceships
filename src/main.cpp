#include <SDL2/SDL.h>



int main(int argc, char* args[]){

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;

if(SDL_Init(SDL_INIT_VIDEO)<0){return 0;}

gWindow = SDL_CreateWindow("SpaceShips",SDL_WINDOWPOS_UNDEFINED,
SDL_WINDOWPOS_UNDEFINED,1920,1080,SDL_WINDOW_SHOWN);

if(!gWindow){return 0;}

gScreenSurface = SDL_GetWindowSurface(gWindow);

/*
while(true){

SDL_UpdateWindowSurface(gWindow);
}


*/
SDL_Delay(8000);

SDL_DestroyWindow(gWindow);
SDL_Quit();
return 0;
}

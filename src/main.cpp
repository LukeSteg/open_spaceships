#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <stdio.h>
#include "graphics.h"

using namespace std;

#define FRAME_INTERVAL 16//in ms

int main(int argc, char* args[]){
if(SDL_Init(SDL_INIT_VIDEO)<0){printf("Failed to initialize SDL\n");return 0;}

bool quit = false;
SDL_Window* window = NULL;

SDL_Renderer* ren;
SDL_CreateWindowAndRenderer(1920,1080,SDL_WINDOW_OPENGL, &window, &ren);

SDL_SetWindowTitle(window,"Open Spaceships : random window suffixes not yet a feature");


SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
SDL_GLContext context = SDL_GL_CreateContext(window);

if(!ren||!window) {
	SDL_DestroyWindow(window);
	printf("Failed to initialize SDL window!\n");
	SDL_Quit();
	return -1;
	}
graphics gfx = graphics();
gfx.Setup(ren);

long long time;// in a galaxy far far away
long long last_frame;
int	delta;
//While the user hasn't quit



SDL_Event event;


while(!quit) {
	while(SDL_PollEvent(&event)){
		switch(event.type){
		case SDL_QUIT:{
			quit = true;
			break;}
		default:{break;}
		}
	}



	time = SDL_GetTicks();
	delta = time - last_frame;
	if(delta >= FRAME_INTERVAL){
	//Game Update(delta);
   	 gfx.Render(delta);
	//SDL_GL_SwapBuffers(); SDL 1.0
    	//SDL_GL_SwapWindow(window);
	SDL_RenderPresent(ren);
	SDL_UpdateWindowSurface(window);//render
	
	last_frame = SDL_GetTicks();
	delta = 0;
	}
	SDL_Delay(1);
}

SDL_DestroyRenderer(ren);
SDL_DestroyWindow(window);
SDL_Quit();
return 0;
}

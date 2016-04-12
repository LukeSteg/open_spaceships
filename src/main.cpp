#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <stdio.h>
#include "graphics.h"
#include "inputHandler.h"

using namespace std;

#define FRAME_INTERVAL 16//in ms

int main(int argc, char* args[]){
if(SDL_Init(SDL_INIT_EVERYTHING)<0){printf("Failed to initialize SDL\n");return 0;}
bool quit = false;
SDL_Window* window = NULL;
//SDL_Renderer* ren = NULL;


SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);


window = SDL_CreateWindow("Open Spaceships : random window suffixes not yet a feature", 
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,1920,1080,SDL_WINDOW_OPENGL);
if(!window){printf("Failed to initialize window: %s\n",SDL_GetError());SDL_Quit();return -1;}

//ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
//if(ren == NULL){printf("Failed to initialize renderer: %s\n",SDL_GetError());}



SDL_GLContext context = SDL_GL_CreateContext(window);
if( context == NULL ) { printf( "OpenGL context could not be created! SDL Error: %s\n", SDL_GetError() ); SDL_DestroyWindow(window);SDL_Quit();return -1; }
if(SDL_GL_MakeCurrent(window, context)!= 0){printf( "OpenGL context could not be set! SDL Error: %s\n", SDL_GetError() ); return -1;}


graphics gfx = graphics();
gfx.Setup();

long long time;// in a galaxy far far away
long long last_frame= SDL_GetTicks();
int	delta;
//While the user hasn't quit



SDL_Event event;


while(!quit) {
	while(SDL_PollEvent(&event)){
		switch(event.type){
			case SDL_QUIT:{quit = true;break;}
		default:{
            inputHandler::ParseEvent(&event);
            break;}
		}
	}

	time = SDL_GetTicks();
	delta = time - last_frame;
	if(delta >= FRAME_INTERVAL){
	//Game Update(delta);
   	 gfx.Render(delta);
    	
	SDL_GL_SwapWindow(window);
	
	last_frame = SDL_GetTicks();
	delta = 0;
	}
	SDL_Delay(1);
}

//SDL_DestroyRenderer(ren);
SDL_DestroyWindow(window);
SDL_Quit();
return 0;
}

#include <SDL2/SDL.h>
#include <stdio.h>

#define FRAME_INTERVAL 16//in ms

int main(int argc, char* args[]){
if(SDL_Init(SDL_INIT_VIDEO)<0){printf("Failed to initialize SDL\n");return 0;}

bool quit = false;
SDL_Window* window = NULL;


window = SDL_CreateWindow("Open Spaceships",SDL_WINDOWPOS_UNDEFINED,
	SDL_WINDOWPOS_UNDEFINED,1920,1080,SDL_WINDOW_SHOWN);

if(!window){return -1;}

SDL_Renderer* ren = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
if(!ren){
	SDL_DestroyWindow(window);
	printf("Failed to initialize SDL renderer!\n");
	SDL_Quit();
	return -1;
	}

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

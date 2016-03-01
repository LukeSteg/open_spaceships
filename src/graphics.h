#ifndef GRAPHICS_H
#define GRAPHICS_H
#define SCREENWIDTH 1920
#define SCREENHEIGHT 1080
#define FIELD_OF_VIEW 90.0f

#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL.h>

class graphics
{
    SDL_Texture* spaceShipTexture;
    SDL_Renderer* renderer;
    public:
          void Render(int delta);
          bool Setup(SDL_Renderer* rend);
          void Destroy();

};

#endif

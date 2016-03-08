#ifndef GRAPHICS_H
#define GRAPHICS_H
#define SCREENWIDTH 1920
#define SCREENHEIGHT 1080
#define FIELD_OF_VIEW 90.0f

#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL.h>

class graphics
{
    GLuint texture;
    public:
          void Render(int delta);
          bool Setup();
          void Destroy();

};

#endif

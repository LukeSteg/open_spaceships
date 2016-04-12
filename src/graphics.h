#ifndef GRAPHICS_H
#define GRAPHICS_H
#define SCREENWIDTH 1920
#define SCREENHEIGHT 1080
#define FIELD_OF_VIEW 90.0f

#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL.h>
#include <string>
using namespace std;



class VisualObject{
	public:
	GLuint texIndex;
	float *vertices;
	float *normals;
	float *texCoords;
	int vert_count;
	void Unload();
	~VisualObject();
};

int CreateVisualObject(VisualObject* vo,string filename);


class graphics
{
    VisualObject vo;
    public:
          void Render(int delta);
          bool Setup();
          void Destroy();
};

#endif

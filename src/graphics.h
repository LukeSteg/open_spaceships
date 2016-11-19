#ifndef GRAPHICS_H
#define GRAPHICS_H
#define SCREENWIDTH 1920
#define SCREENHEIGHT 1080
#define FIELD_OF_VIEW 90.0f


#define MAX_MATRIX_STACK 10




#include <SDL2/SDL.h>
#include <string>
#include "types.h"
#include "shader.h"

using namespace std;



class VisualObject{
	public:
	GLuint texID,vertID,coordID;
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
	Mat4 Modelview[MAX_MATRIX_STACK];
	Mat4 Projection[MAX_MATRIX_STACK];
	Shader shader;
	int	 Modelview_Stack;
	int  Projection_Stack;
    public:
          void Render(int delta);
          bool Setup();
          void Destroy();
};

#endif

#ifndef  SHADER_H
#define SHADER_H

#define GL_GLEXT_PROTOTYPES
#include <SDL2/SDL_opengl.h>
#include <GL/glext.h>

typedef struct{
int hashID;
GLuint program;

//UNIFORMS
GLint MODELVIEW_MATRIX;
GLint PROJECTION_MATRIX;
GLint TEXTURE_0;
GLint COLOR;
char Load(char* vertex_filename,char* fragment_filename);
void Use();
}Shader;




#endif

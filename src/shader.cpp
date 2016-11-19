#include "shader.h"
#include <stdlib.h>
#include <stdio.h>

char Shader::Load(char* vertex_filename, char* fragment_filename){
hashID =0;
program =0;
GLuint vertex_handle,fragment_handle;

FILE* vertex = fopen(vertex_filename,"r");
int vertex_size =0;

if(!vertex){
	printf("Cannot open Vertex shader file!\n");
	return 0;
}

fseek(vertex, 0L, SEEK_END);
vertex_size = ftell(vertex);
fseek(vertex, 0L, SEEK_SET);

GLchar* vrtmp =(char*) malloc(vertex_size+1);
fread(vrtmp,1,vertex_size,vertex);

vrtmp[vertex_size] = 0;
fclose(vertex);


FILE* fragment = fopen(fragment_filename,"r");
int fragment_size = 0;
if(!fragment){
	printf("Cannot open Fragment shader file!\n");
	return 0;
}

fseek(fragment, 0L, SEEK_END);
fragment_size = ftell(vertex);
fseek(fragment, 0L, SEEK_SET);

GLchar* frtmp =(char*) malloc(fragment_size+1);
fread(frtmp,1,fragment_size,fragment);
frtmp[fragment_size] = 0;
fclose(fragment);

program = glCreateProgram();
vertex_handle   = glCreateShader(GL_VERTEX_SHADER);
fragment_handle = glCreateShader(GL_FRAGMENT_SHADER);

glShaderSource(vertex_handle,1,(const GLchar**)&vrtmp,NULL);
glShaderSource(fragment_handle,1,(const GLchar**)&frtmp,NULL);

glCompileShader(vertex_handle);
glCompileShader(fragment_handle);

GLint fr_compilestatus, vr_compilestatus, link_status;

glGetShaderiv(vertex_handle,GL_COMPILE_STATUS,&vr_compilestatus);
glGetShaderiv(fragment_handle,GL_COMPILE_STATUS,&fr_compilestatus);

free(vrtmp);
free(frtmp);

if(vr_compilestatus && fr_compilestatus){
	glAttachShader(program,vertex_handle);
	glAttachShader(program,fragment_handle);
	glLinkProgram(program);
	glGetProgramiv(program,GL_LINK_STATUS,&link_status);
	if(link_status){
		MODELVIEW_MATRIX = glGetUniformLocation(program,"modelview_matrix");
		PROJECTION_MATRIX = glGetUniformLocation(program,"projection_matrix");
		TEXTURE_0 = glGetUniformLocation(program,"texture0");
		COLOR = glGetUniformLocation(program,"Color");
		glBindAttribLocation(program,0,"a_Vertex");
		glBindAttribLocation(program,1,"a_TexCoord");
		return 1;}
	else{printf("shader linker error\n");return 0; }//Linker error
}
else{
	char errlog[256];
	glGetShaderInfoLog(vertex_handle,255,NULL,&errlog[0]);
	errlog[255] = 0;
	printf("(VERTEX)%s\n",errlog);	
	glGetShaderInfoLog(fragment_handle,255,NULL,&errlog[0]);
	printf("(FRAGMENT)%s\n",errlog);	
	//write(Errlog);
	return 0;}//Compile Error
}

void Shader::Use(){glUseProgram(program);}

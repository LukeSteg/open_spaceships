#include "graphics.h"
#include <SDL2/SDL_image.h>

bool graphics::Setup()
{
 

    bool properlySetUp = true;
    
    glClearColor(0.0f,1.0f,0.0f,1.0f);

    glClearDepth(1.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glDepthFunc(GL_LEQUAL);

    glViewport(0,0,SCREENWIDTH, SCREENHEIGHT);

    SDL_Surface *tempSurface = IMG_Load("assets/StarDestroyer.jpeg");
    if(tempSurface == NULL){printf("image did not load\n%s\n",IMG_GetError());}

    glGenTextures( 1, &texture );
    glBindTexture( GL_TEXTURE_2D, texture );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexImage2D( GL_TEXTURE_2D, 0, tempSurface->format->BytesPerPixel, 
		tempSurface->w, tempSurface->h, 0,GL_RGB,
		 GL_UNSIGNED_BYTE, tempSurface->pixels );

    int err = glGetError();
    if(err != GL_NO_ERROR){
	printf("gl setup error %x\n",err);
	} 


    return properlySetUp;
}


static float rotate = 0.0f;
void graphics::Render(int delta)
{

    rotate += delta;

   glClearColor(0.7f,0.3f,0.1f,1.0f);
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

 

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

    //gluPerspective(FIELD_OF_VIEW, SCREENWIDTH/SCREENHEIGHT, 0.1f, 100.0f);
    //glFrustum(-SCREENWIDTH/2,SCREENWIDTH/2,-SCREENHEIGHT/2,SCREENHEIGHT/2,0.1f, 100.0f);

   // glFrustum(-100.f,100.f,-50.f,50.f,0.1f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
    
    //glRotatef((rotate/360.0f),0.0f,1.0f,0.0f);
    //glTranslatef(0.0f,0.0f,-1.0f);

	
	    
    int err = glGetError();
    if(err != GL_NO_ERROR){
	printf("gl draw-init error %x\n",err);
	} 


    glBegin(GL_TRIANGLES);
    glColor3f(1.0f,1.0f,1.0f);


    glTexCoord2f(0.0f,1.0f);
    glVertex3f(0.0f,0.0f,-0.5f);


    glTexCoord2f(0.0f,0.0f);
    glVertex3f(0.0f,0.5f,-0.5f);


    glTexCoord2f(1.0f,0.0f);
    glVertex3f(0.5f,0.5f,-0.5f);


    glTexCoord2f(0.0f,1.0f);
    glVertex3f(0.0f,0.0f,-0.5f);


    glTexCoord2f(1.0f,1.0f);
    glVertex3f(0.5f,0.0f,-0.5f);


    glTexCoord2f(1.0f,0.0f);
    glVertex3f(0.5f,0.5f,-0.5f);

    glEnd();

    err = glGetError();
    if(err != GL_NO_ERROR){
	printf("gl draw error %x\n",err);
	} 

}

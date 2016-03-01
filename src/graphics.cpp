#include "graphics.h"
#include <SDL2/SDL_image.h>

bool graphics::Setup(SDL_Renderer* rend)
{
    bool properlySetUp = true;
    
    //glClearColor(0.0f,0.0f,0.0f,0.0f);

    glClearDepth(1.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D); 
    glDepthFunc(GL_LEQUAL);

    glViewport(0,0,SCREENWIDTH, SCREENHEIGHT);

    renderer = rend;

    //SD test code
    SDL_Surface *tempSurface = IMG_Load("assets/StarDestroyer.jpeg");
    if(tempSurface == NULL)
        printf("image did not load\n%s\n",IMG_GetError());
    spaceShipTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    if(spaceShipTexture == NULL)
        printf("texture was not created\n%s\n",SDL_GetError());

    return properlySetUp;
}


static float rotate = 0.0f;
void graphics::Render(int delta)
{

    rotate += delta;

    glClearColor(0.0f,0.0f,0.0f,0.0f);

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    //gluPerspective(FIELD_OF_VIEW, SCREENWIDTH/SCREENHEIGHT, 0.1f, 100.0f);
    glFrustum(-SCREENWIDTH/2,SCREENWIDTH/2,-SCREENHEIGHT/2,SCREENHEIGHT/2,0.1f, 100.0f);

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();
    
    glRotatef(rotate,0.0f,1.0f,0.0f);
   // SDL_GL_BindTexture(spaceShipTexture,NULL, NULL);
	
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f,1.0f,1.0f);

    glVertex3f(0.0f,0.0f,0.0f);
    glTexCoord2f(0.0f,0.0f);

    glVertex3f(0.0f,500.0f,500.0f);
    glTexCoord2f(0.0f,1.0f);

    glVertex3f(500.0f,500.0f,500.0f);
    glTexCoord2f(1.0f,1.0f);

    glVertex3f(0.0f,0.0f,0.0f);
    glTexCoord2f(0.0f,0.0f);

    glVertex3f(500.0f,0.0f,500.0f);
    glTexCoord2f(1.0f,0.0f);

    glVertex3f(500.0f,500.0f,500.0f);
    glTexCoord2f(1.0f,1.0f);

    glEnd();

    //render code goes here
    //test code for SD picure
    //SDL_RenderPresent(renderer);
    /*if(SDL_RenderCopy(renderer, spaceShipTexture, NULL, NULL))
        printf("you fkd up\n%s\n", SDL_GetError());*/

}

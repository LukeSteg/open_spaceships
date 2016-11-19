#include "graphics.h"


#include <string.h>

#include <SDL2/SDL_image.h>

#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>







bool graphics::Setup()
{
    bool properlySetUp = true;
    printf("setting up...\n");;
    glClearColor(0.0f,1.0f,0.0f,1.0f);

    glClearDepth(1.0f);

	Modelview_Stack = 0;
	Projection_Stack =0;
	for(int i=0;i<MAX_MATRIX_STACK;i++){
		Modelview[i].Identity();
		Projection[i].Identity();
	}

	std::string vert = "./assets/gfx/basic.vrt";
	std::string frag = "./assets/gfx/basic.frg";
	shader.Load((char*)vert.c_str(),(char*)frag.c_str());
	
	GLuint vao;//Hey thanks Nicol Bolas
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
    //glEnable(GL_DEPTH_TEST);
    //glEnable(GL_TEXTURE_2D);
    //glDepthFunc(GL_LEQUAL);
	int res = CreateVisualObject(&vo,"./assets/duck.dae");
	printf("Result: %d\n",res);

    glViewport(0,0,SCREENWIDTH, SCREENHEIGHT);
    return properlySetUp;
}


int CreateVisualObject(VisualObject* vo,string filename){
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile( filename,aiProcessPreset_TargetRealtime_Fast);

	if(scene){
		aiMesh* mesh = scene->mMeshes[0];
		aiMaterial* mat = scene->mMaterials[mesh->mMaterialIndex];
		vo->vert_count = mesh->mNumFaces*3;
		vo->vertices = new float[mesh->mNumFaces*3*3];
		vo->normals = new float[mesh->mNumFaces*3*3];
		vo->texCoords = new float[mesh->mNumFaces*3*2];
		int vertex = 0;
		for(unsigned int i=0;i<mesh->mNumFaces;i++)
		{
		aiFace& face = mesh->mFaces[i];
			for(int j=0;j<3;j++)
			{
			aiVector3D uv = mesh->mTextureCoords[0][face.mIndices[j]];
			aiVector3D normal = mesh->mNormals[face.mIndices[j]];
			aiVector3D pos = mesh->mVertices[face.mIndices[j]];

			memcpy(&vo->texCoords[vertex*2],&uv,sizeof(float)*2);		 
			memcpy(&vo->normals[vertex*3],&normal,sizeof(float)*3);
			memcpy(&vo->vertices[vertex*3],&pos,sizeof(float)*3);
			vertex++;
			}
		}


		glGenBuffers(1,&vo->vertID);
		glGenBuffers(1,&vo->coordID);

		glBindBuffer(GL_ARRAY_BUFFER,vo->vertID);
		glBufferData(GL_ARRAY_BUFFER,sizeof(float)*3*vo->vert_count,vo->vertices,GL_STATIC_DRAW);
	
		glBindBuffer(GL_ARRAY_BUFFER,vo->coordID);
		glBufferData(GL_ARRAY_BUFFER,sizeof(float)*2*vo->vert_count,vo->texCoords,GL_STATIC_DRAW);

		aiString base_filename;
		std::string tex_filename;
		mat->GetTexture(aiTextureType_DIFFUSE,0,&base_filename);
		
		tex_filename.append("./assets/");
		char *fn = new char[base_filename.length+1];
		std:strcpy(fn,base_filename.C_Str());
		tex_filename.append(&fn[2]);

		printf("Opening:%s\n",tex_filename.c_str());
		SDL_Surface *tempSurface = IMG_Load(tex_filename.c_str());
		if(tempSurface == NULL){printf("image did not load\n%s\n",IMG_GetError());}

		glGenTextures( 1, &vo->texID );
		glBindTexture( GL_TEXTURE_2D, vo->texID );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		if(tempSurface->format->BytesPerPixel == 3){
			printf("No alpha\n");

			unsigned char* bad_pixels =(unsigned char*)tempSurface->pixels;
			unsigned char* pxl =(unsigned char*) malloc(tempSurface->w*tempSurface->h*3);

			int i2,j2;
			for(int i=0;i<tempSurface->h;i++){
				for(int j=0;j<tempSurface->w;j++){
					i2 = (tempSurface->h-1)-i;
					j2 = (tempSurface->w-1)-j;
					pxl[(i*tempSurface->w + j)*3 + 0] = bad_pixels[(i2*tempSurface->w + j)*3 + 2];
					pxl[(i*tempSurface->w + j)*3 + 1] = bad_pixels[(i2*tempSurface->w + j)*3 + 1];
					pxl[(i*tempSurface->w + j)*3 + 2] = bad_pixels[(i2*tempSurface->w + j)*3 + 0];
				}
			}
	

			glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, 
				tempSurface->w, tempSurface->h, 0, GL_RGB,
				GL_UNSIGNED_BYTE, pxl);
			free(pxl);
			printf("First color: %d,%d,%d\n",pxl[0],pxl[1],pxl[2]);
		}
		else if(tempSurface->format->BytesPerPixel == 4){//with alpha
			printf("Says it's got alpha\n");
			glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, 
				tempSurface->w, tempSurface->h, 0, GL_RGBA,
				GL_UNSIGNED_BYTE, tempSurface->pixels );
		}
		else {
			printf("What the hell %d bytes per pixel?!\n",tempSurface->format->BytesPerPixel);
		}

		SDL_FreeSurface(tempSurface);//we dont need the image any more, its in the GPU


	return 1;
	}

	else if(!scene){
    //importer.GetErrorString();
    return 0;
	}
	
	return 0;
}


void VisualObject::Unload(){
vert_count =0;
if(vertID >= 0){glDeleteBuffers(1,&vertID);vertID = -1;}
if(coordID >= 0){glDeleteBuffers(1,&coordID);coordID = -1;}
if(texID >= 0){glDeleteTextures(1,&texID);texID = -1;}
if(vertices){delete(vertices);vertices = NULL;}
if(normals){delete(normals);normals = NULL;}
if(texCoords){delete(texCoords);texCoords = NULL;}
}

VisualObject::~VisualObject(){}//Unload();}



void graphics::Render(int delta)
{
	
	glClearColor(0.7f,0.3f,0.1f,1.0f);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	//glEnable(GL_TEXTURE_2D);
	//

	//glEnable(GL_BLEND);
	//glEnable(GL_DEPTH_TEST);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	shader.Use();

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glActiveTexture(GL_TEXTURE0);
	Modelview_Stack++;
	Modelview[Modelview_Stack].Identity();
	Modelview[Modelview_Stack].Scale(0.005f,0.005f,0.005f);

	Projection_Stack++;
	Projection[Projection_Stack].Identity();
	//Projection[Projection_Stack].Frustum();
	//Projection[Projection_Stack].(-cam.x_fov/2,cam.x_fov/2,-cam.y_fov/2.0f,cam.y_fov/2.0f,1.0f,256.0f);
	//Ortho(&Projection[Projection_Stack],-(256.0/2.0),(256.0/2.0),-(144.0/2.0),(144.0/2.0),-1.0f,512.0f);	//pixel perfect 2D

	//for loop for all VO's
	if(vo.vert_count > 0){
	glActiveTexture(GL_TEXTURE0);	 
	glBindTexture(GL_TEXTURE_2D, vo.texID );
	glUniform1i(shader.TEXTURE_0,0);
	float color[4] = {1.0f,1.0f,1.0f,1.0f};
	glUniform4fv(shader.COLOR,1,color);
	
	glUniformMatrix4fv(shader.MODELVIEW_MATRIX,1,GL_FALSE,Modelview[Modelview_Stack].m);
	glUniformMatrix4fv(shader.PROJECTION_MATRIX,1,GL_FALSE,Projection[Projection_Stack].m);
	
	//printf("B:%x\n",glGetError());
	glBindBuffer(GL_ARRAY_BUFFER,vo.vertID);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,0);
	//
	glBindBuffer(GL_ARRAY_BUFFER,vo.coordID);
	glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,0,0);

	glDrawArrays(GL_TRIANGLES,0,vo.vert_count);
	//printf("C:%x\n",glGetError());
	}
	Modelview_Stack--;
	Projection_Stack--;

}

#include "graphics.h"
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

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glDepthFunc(GL_LEQUAL);

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

		glGenTextures( 1, &vo->texIndex );
		glBindTexture( GL_TEXTURE_2D, vo->texIndex );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		glTexImage2D( GL_TEXTURE_2D, 0, tempSurface->format->BytesPerPixel, 
			tempSurface->w, tempSurface->h, 0,tempSurface->format->BytesPerPixel,
			GL_UNSIGNED_BYTE, tempSurface->pixels );
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
if(texIndex > 0){glDeleteTextures(1,&texIndex);texIndex = -1;}
if(vertices){delete(vertices);vertices = NULL;}
if(normals){delete(normals);normals = NULL;}
if(texCoords){delete(texCoords);texCoords = NULL;}
}

VisualObject::~VisualObject(){Unload();}



void graphics::Render(int delta)
{
	glClearColor(0.7f,0.3f,0.1f,1.0f);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

    //gluPerspective(FIELD_OF_VIEW, SCREENWIDTH/SCREENHEIGHT, 0.1f, 100.0f);
    glFrustum(-SCREENWIDTH/2,SCREENWIDTH/2,-SCREENHEIGHT/2,SCREENHEIGHT/2,0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    
	//glTranslatef(0.0f,0.0f,-1.0f);

	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	//glEnableClientState(GL_NORMAL_ARRAY);		Lighting later
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	 
	glClientActiveTexture(GL_TEXTURE0);
	glBindTexture( GL_TEXTURE_2D, vo->texIndex );
	//for loop for all VO's
	if(vo.vert_count > 0){	 
	glVertexPointer(3,GL_FLOAT,0,vo.vertices);
	//glNormalPointer(GL_FLOAT,0,vo.normals);
	glTexCoordPointer(2,GL_FLOAT,0,vo.texCoords);
	 
	glDrawArrays(GL_TRIANGLES,0,vo.vert_count);
	}
	//
	glDisableClientState(GL_VERTEX_ARRAY);
	//glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

}

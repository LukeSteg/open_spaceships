#include "types.h"


//////////////////////////////////////////////////////////////////////////////////////MATRIX

//Sets a Mat4 to the identity matrix
void Mat4::Identity(){
	memset(m,0,sizeof(float)*16);
	m[0] = m[5] = m[10] = m[15] = 1.0f;
}

//Multiplies 2 Mat4's storing the result in this
void Mat4::Multiply(Mat4 *b){
	float result[16];
	for(int i=0;i<4;i++){ //Column major on the left = Row Major on the right. In other words, 		this is a row major muliplication of B*A, so its A*B column major.
		for(int j=0;j<4;j++){
			result[i*4 + j]= (b->m[i*4]  *m[j]  ) +
							 (b->m[i*4+1]*m[j+4]) +
							 (b->m[i*4+2]*m[j+8]) +
							 (b->m[i*4+3]*m[j+12]);
		}
	}
	for(int i=0;i<16;i++){m[i] = result[i];}
}

//Translates a Mat4 by (x,y,z)
void Mat4::Translate(float x,float y,float z){
	Mat4 b ={{	1,0,0,0,
				0,1,0,0,
				0,0,1,0,
				x,y,z,1}};
	Multiply(&b);
}

//Scales a Mat4 by (x,y,z)
void Mat4::Scale(float x,float y,float z){
	Mat4 Scale =	{{x,0 ,0 ,0,
			  0 ,y,0 ,0,
			  0 ,0 ,z,0,
			  0 ,0 ,0 ,1}};
	Multiply(&Scale);
}

//Roates a Mat4 by theta in the (x,y,z) axis [It's reccomended to rotate one axis at a time)
void Mat4::Rotate(float x,float y,float z,float theta){
	float rx,ry,rz,normal;
	float c = cosf(theta*PI_OVER_180);
	float s = sinf(theta*PI_OVER_180);

	normal = sqrtf(x*x+y*y+z*z);
	rx = x/normal;
	ry = y/normal;
	rz = z/normal;

	Mat4 rot =	{{
		rx*rx*(1-c)+c,		rx*ry*(1-c)+rz*s,	rx*rz*(1-c)-ry*s,	0,
		rx*ry*(1-c)-rz*s,	ry*ry*(1-c)+c,		ry*rz*(1-c)+rx*s,	0,
		rx*rz*(1-c)+ry*s,	ry*rz*(1-c)-rx*s,	rz*rz*(1-c)+c,	0,
		0,0,0,1}};// Mental exercise!
	Multiply(&rot);
}

//Multiplies a matrix by an orthagonal projection matrix from left-right, bottom-top, and near-far
void Mat4::Ortho(float l,float r,float b,float t,float n,float f){
	float tx = -(r+l)/(r-l);
	float ty = -(t+b)/(t-b);
	float tz = -(f+n)/(f-n);

	Mat4 Ortho ={
	{2/(r-l),0,0,0,
	 0,2/(t-b),0,0,
	 0,0,-2/(f-n),0,
	 tx,ty,tz,1}};
	/* Here's the matrix (Row major) with spacing:
	2/(r-l),0      ,0       ,-(r+l)/(r-l)
	0      ,2/(t-b),0       ,-(t+b)/(t-b)
	0      ,0      ,-2/(f-n),-(f+n)/(f-n)
	0      ,0      ,0       ,1
	*/

	Multiply(&Ortho);
}

//Creates a view frustum for a 3D view
void Mat4::Frustum(float l,float r,float b,float t,float n,float f){
	Mat4 fr;	
	memset(&fr.m,0,sizeof(float)*16);
	
	// Row Major Frustum Matrix
	//	X	0 	A 	0 	
	//  0 	Y 	B 	0 
	//  0 	0 	C 	D 	
	//  0 	0 	-1 	0
	
	fr.m[0] = (2*n)/(r-l); //X
	fr.m[5] = (2*n)/(t-b); //Y

	fr.m[8] =   (r+l)/(r-l);     //A
	fr.m[9] =   (t+b)/(t-b);    //B
	fr.m[10] = -((f+n)/(f-n)); //C
	fr.m[11] =  -1;

	fr.m[14] = -(2*f*n)/(f-n);

	Multiply(&fr);
}

//Multiplies count number of 3-float points by the matrix, storing the resulting points in out
void Mat4::MultVec3(float* pts,float* out,int count){
	for(int i=0;i<count;i++){
		out[i*3 + 0] = m[0]*pts[i*3 + 0] + m[4]*pts[i*3 + 1] + m[8]*pts[i*3 + 2]  + m[12];
		out[i*3 + 1] = m[1]*pts[i*3 + 0] + m[5]*pts[i*3 + 1] + m[9]*pts[i*3 + 2]  + m[13];
		out[i*3 + 2] = m[2]*pts[i*3 + 0] + m[6]*pts[i*3 + 1] + m[10]*pts[i*3 + 2] + m[14];
	}
}

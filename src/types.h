#ifndef TYPES_H
#define TYPES_H
#include <math.h>
#include <cstring>
#define PI 3.1415926f 
#define PI_OVER_180 0.0174532925F



typedef struct Mat4{
float m[16];

void 				Identity();
void 				Multiply(Mat4 *b);
void 				Translate(float x,float y,float z);
void 				Scale(float x,float y,float z);
void 				Rotate(float x,float y,float z,float theta);
void 				Ortho(float l,float r,float b,float t,float n,float f);
void 				Frustum(float l,float r,float b,float t,float n,float f);
void				MultVec3(float* pts,float* out,int count);
} Mat4;




#endif

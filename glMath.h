/////////////////////////////////////////////////////////////////////////////
// glMath.h : Header file; Defines the class definitions
//
// ModelMagic3D and 'glOOP' (OpenGL Object Oriented Programming library)
// Copyright ?ImageWare Development 1997, 2002
//
// OpenGL is a registered trademark of Silicon Graphics
//
//
// This program is provided for educational and personal use only and
// is provided without guarantee or warrantee expressed or implied.
//
// Commercial use is strictly prohibited without written permission
// from ImageWare Development.
//
// This program is -not- in the public domain.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef __GLMATH__
#define __GLMATH__


//#include <gl\gl.h>
//#include <gl\glu.h>
////#include <gl\glaux.h>
#include <math.h>
//#include "Vector4.h"
//#include "Matrix4x4.h"


/////////////////////////////////////////////////////////////////////////////
// glMath Definitions:
//
#define Pi				3.14159265f
#define PiOver180		1.74532925199433E-002f
#define PiUnder180		5.72957795130823E+001f
#define SMALL_NUMBER	0.00001
#define LARGE_NUMBER	1E20

#define X				0	// Used for Coordinate array index
#define Y				1
#define Z				2
#define W				3

#define R				0	// Used for Color array index
#define G				1
#define B				2
#define A				3

#define TS				0	// Used for Texture coordinate array index
#define TT				1
#define TR				2
#define TQ				3

#define CIRCLE_N		24



/////////////////////////////////////////////////////////////////////////////
// Type Definitions:
//
typedef float		VECTORF[4];
typedef float		COLORF[4];
typedef double	Matx4x4[4][4];		


/////////////////////////////////////////////////////////////////////////////
// External function prototypes:
//

// Misc Math Functions
extern int Scale_down_to_power_of_2(long x);
extern int WordAlign(int n);

extern bool IsEven(int n);
extern bool IsEven(float f);

extern float Radiansf(float Angle);
extern float Degreesf(float Angle);
extern float Cosf(float Angle);
extern float Sinf(float Angle);
extern float Tanf(float Angle);
extern float Powerf(float Base, int Exponent);
extern float Sqrf(float x);
extern int Roundf(float x);
extern float Roundf(float x, int numDecimalPlaces);
extern int Roundfd(double x);
extern double Roundfd(double x, int numDecimalPlaces);
extern float Diff(float a, float b);

extern double Radiansd(double Angle);
extern double Degreesd(double Angle);
extern double Cosd(double Angle);
extern double Sind(double Angle);


// Vector Functions
extern bool VecEqualf(VECTORF a, VECTORF b);

extern void VecClearf(VECTORF a);

extern void Vec3f(float r, float s, float t, VECTORF a);
extern void UnVec3f(VECTORF a, float *r, float *s, float *t);
extern void Vec4f(float r, float s, float t, float u, VECTORF a);
extern void UnVec4f(VECTORF a, float *r, float *s, float *t, float *u);

extern void VecCopyf(VECTORF a, VECTORF b);
extern void VecCopy3f(VECTORF a, VECTORF b);
extern void VecCopy4f(VECTORF a, VECTORF b);

extern void VecSubf(VECTORF a, VECTORF b, VECTORF c);
extern void VecAddf(VECTORF a, VECTORF b, VECTORF c);
extern void VecAdd3f(VECTORF a, VECTORF b, VECTORF c, VECTORF d);
extern void VecMultf(VECTORF a, VECTORF b, VECTORF c);
extern void VecScalef(VECTORF a, float scale, VECTORF b);
extern float VecDiFFf(VECTORF a, VECTORF b);

extern float VecDotf(VECTORF a, VECTORF b);
extern void VecCrossf(VECTORF a, VECTORF b, VECTORF c);
extern float VecLenf(VECTORF a);
extern void VecNormalizef(VECTORF a);
extern void CalNormalf(VECTORF a, VECTORF b, VECTORF c, VECTORF n, bool bCCW=true);
extern bool GetVecAnglef(VECTORF a, VECTORF b, float *fAngle);
extern void GetEulerXYFromVector(VECTORF vec, float *rx, float *ry, float *rz);

extern float GetAreaTriangle(VECTORF a, VECTORF b, VECTORF c);
extern void GetCenterVec(VECTORF a, VECTORF b, VECTORF c, VECTORF center);

extern void MakePlane(VECTORF PlnX, VECTORF PlnY, VECTORF PlnPoint, float Scale , VECTORF RectPoint1, VECTORF RectPoint2, VECTORF RectPoint3, VECTORF RectPoint4);
extern int GetIntersectPoint(VECTORF AP1, VECTORF AP2, VECTORF BP1, VECTORF BP2, VECTORF IP);

extern int GetIntersectPoint3Plane(VECTORF APlane1, VECTORF APlane2, VECTORF APlane3, VECTORF BPoint);

// Affine Matrix Transformation Funcitons
extern void ZeroMatrix(Matx4x4 a);
extern void IdentityMatrix(Matx4x4 a);
extern void Translate3D(float tx, float ty, float tz, Matx4x4 a);
extern void Scale3D(float sx, float sy, float sz, Matx4x4 a);
extern void Rotate3D(int m, float Theta, Matx4x4 a);
extern void MultiplyMatricies(Matx4x4 a, Matx4x4 b, Matx4x4 c);
extern void MatrixCopy(Matx4x4 a, Matx4x4 b);
extern void TransposeMatrix(Matx4x4 a);
extern void PrepareMatrix(float Ox,  float Oy,  float Oz,
						  float Sx,  float Sy,  float Sz,
						  float Rx,  float Ry,  float Rz,
						  float Tx,  float Ty,  float Tz,
						  Matx4x4 XForm);
extern void PrepareInvMatrix(float Px,  float Py,  float Pz,
							 float Sx,  float Sy,  float Sz,
							 float Rx,  float Ry,  float Rz,
							 float Tx,  float Ty,  float Tz,
							 Matx4x4 XForm);
extern void SetRotationMatrix(float Rx,  float Ry,  float Rz,
							  Matx4x4 XForm);
extern void SetInvRotationMatrix(float Rx,  float Ry,  float Rz,
								 Matx4x4 XForm);
extern void VecTransformf(VECTORF sx, VECTORF dx, Matx4x4 M);
extern void SetAxisRotationMatrix(VECTORF vtx, VECTORF axis,float angle, Matx4x4 M);

extern void MatrixToEuler(Matx4x4 M, float *rx, float *ry, float *rz, bool bPositive= false);
extern void MatrixToEuler(Matx4x4 M, VECTORF r, bool bPositive=false);

// Misc OpenGL Related Functions
extern void GLMatrixTo4x4(double M[16], Matx4x4 a);
extern void Matx4x4ToGLMatrix(Matx4x4 a, double M[16]);
extern void GLIdentityMatrix(double M[16]);
extern bool InvertGLMatrix(double mat[16], double out[16]);
extern void Transformf(VECTORF sx, VECTORF dx, double M[16]);
extern void TransposeGLMatrix(double dst[16], double src[16]);
extern void AddGLMatrices(double dst[16], double a[16], double b[16]);
extern void MultGLMatrices(double dst[16], const double a[16], const double b[16]);
extern void CopyGLMatrix(double dst[16], double src[16]);
extern void BuildGLFrustumMatrix(double m[16], double l, double r, double b, double t,
								double n, double f);
extern void BuildGLPerspectiveMatrix(double m[16], double fovy, double aspect,
									  double zNear, double zFar);
extern void BuildGLLookAtMatrix(double m[16], double eyex, double eyey, double eyez,
								 double centerx, double centery, double centerz,
								 double upx, double upy, double upz);
extern void PrintGLMatrix(char *msg, double m[16]);


#endif // Include/Define


/////////////////////////////////////////////////////////////////////////////
// glMath.c : global glMath function implementation file
//
/////////////////////////////////////////////////////////////////////////////
#include <math.h>
#include <stdio.h>
#include "glMath.h"
#include "string.h"


/*****************************************************************************
 *
 *  Misc. Math Routines
 *
 *****************************************************************************
 */

int Scale_down_to_power_of_2(long x)
{
//	PURPOSE    : Utility to scale the number x to the next lower power of 2.
//				 For example:  300 would get scaled to 256..
//
//	RETURNS    : The scaled value of x
//
	int i;
	long shifted_x;

	shifted_x = x;
	for (i = 0; ((i < 16) && (shifted_x != 0)); i++)
		shifted_x = shifted_x >> 1;

	if (i == 0)
		return 0;
	else
		return ((int)(pow((double)2, (double)(i-1))));
}

int WordAlign(int n)
{
	//if(fmod(n, sizeof(RGBQUAD)))
	//{
	//	// Word align the row..
	//	n += sizeof(RGBQUAD) - (int)fmod(n, sizeof(RGBQUAD));
	//}

	return n;
}

bool IsEven(int n)
{
	double temp = fmod((double)n, 2.0);
	if(!temp)
		return true;
	else
		return false;
}

bool IsEven(float f)
{
	double temp = fmod((double)f, 2.0);
	if(!temp)
		return true;
	else
		return false;
}

float Radiansf(float Angle)
{
	double r = (double)Angle*PiOver180; 
	return(float)r;
}

float Degreesf(float Angle)
{
	double d = (double)Angle*PiUnder180;
	return(float)d;
}

float Sinf(float Angle)
{
	return((float)sin(Radiansf(Angle)));
}

float Cosf(float Angle)
{
	return((float)cos(Radiansf(Angle)));
}

float Tanf(float Angle)
{
	return((float)tan(Radiansf(Angle)));
}

float Powerf(float Base, int Exponent)
{
	float BPower;
	int   t;

	if(Exponent==0)
		return(1.0f);
	else
	{
		BPower=1.0f;
		for(t=1; t<=Exponent; t++)
			BPower*=Base;

		return(BPower);
	}
}

float Sqrf(float x)
{
	return(x*x);
}

int Roundf(float x)
{
	if(x<0)
		return((int)(x-0.5));
	else
		return((int)(x+0.5));
}

int Roundfd(double x)
{
	if(x<0)
		return((int)(x-0.5));
	else
		return((int)(x+0.5));
}

float Roundf(float x, int numDecimalPlaces)
{
	double exponent, fraction;
	int whole, fractional;

	whole = (int)x;
	fraction = (double)(x-whole);

	exponent = pow(10.0, numDecimalPlaces);

	fractional = Roundf((float)(fraction * exponent));
	return (float)(whole+(float)fractional/exponent);
}
double Roundfd(double x, int numDecimalPlaces)
{
	double exponent, fraction;
	int whole, fractional;

	whole = (int)x;
	fraction = (double)(x-whole);

	exponent = pow(10.0, numDecimalPlaces);

	fractional = Roundfd((double)(fraction * exponent));
	return (double)(whole+(double)fractional/exponent);
}

float Diff(float a, float b)
{
	if(a >= 0 && b >= 0)
	{
		if(a > b)
			return a-b;
		else
			return b-a;
	}
	if(a < 0 && b < 0)
	{
		if( a > b)
			return b-a;
		else
			return a-b;
	}
	if(a >= 0 && b < 0)
		return a-b;
	else
		return b-a;
}

double Radiansd(double Angle)
{
	double r = Angle*PiOver180; 
	return r;
}

double Degreesd(double Angle)
{
	double d = Angle*PiUnder180;
	return d;
}

double Cosd(double Angle)
{
	return((double)cos(Radiansd(Angle)));
}

double Sind(double Angle)
{
	return((double)sin(Radiansd(Angle)));
}


/*****************************************************************************
 *
 *  Vector Functions:
 *
 *****************************************************************************
 */

void Vec3f(float r, float s, float t, VECTORF a)
{
	a[X]=r;
	a[Y]=s;
	a[Z]=t;
}

void UnVec3f(VECTORF a, float *r, float *s, float *t)
{
	*r=a[X];
	*s=a[Y];
	*t=a[Z];
}

void Vec4f(float r, float s, float t, float u, VECTORF a)
{
	a[X]=r;
	a[Y]=s;
	a[Z]=t;
	a[3]=u;
}

void UnVec4f(VECTORF a, float *r, float *s, float *t, float *u)
{
	*r=a[X];
	*s=a[Y];
	*t=a[Z];
	*u=a[3];
}

void VecClearf(VECTORF a)
{
	a[X] = 0.0f;
	a[Y] = 0.0f;
	a[Z] = 0.0f;
	a[W] = 0.0f;
}

bool VecEqualf(VECTORF a, VECTORF b)
{
	if(fabs(a[X]-b[X]) > SMALL_NUMBER)
		return false;

	if(fabs(a[Y]-b[Y]) > SMALL_NUMBER)
		return false;

	if(fabs(a[Z]-b[Z]) > SMALL_NUMBER)
		return false;

	return true;
}

void VecCopy3f(VECTORF a, VECTORF b)
{
	b[X]=a[X];
	b[Y]=a[Y];
	b[Z]=a[Z];
}

void VecCopy4f(VECTORF a, VECTORF b)
{
	b[X]=a[X];
	b[Y]=a[Y];
	b[Z]=a[Z];
	b[W]=a[W];
}

void VecCopyf(VECTORF a, VECTORF b)
{
	b[X]=a[X];
	b[Y]=a[Y];
	b[Z]=a[Z];
	b[W]=a[W];
}

void VecSubf(VECTORF a, VECTORF b, VECTORF c)
{
	c[X]=a[X]-b[X];
	c[Y]=a[Y]-b[Y];
	c[Z]=a[Z]-b[Z];
}

void VecAddf(VECTORF a, VECTORF b, VECTORF c)
{
	c[X]=a[X]+b[X];
	c[Y]=a[Y]+b[Y];
	c[Z]=a[Z]+b[Z];
}

void VecAdd3f(VECTORF a, VECTORF b, VECTORF c, VECTORF d)
{
	d[X]=a[X]+b[X]+c[X];
	d[Y]=a[Y]+b[Y]+c[Y];
	d[Z]=a[Z]+b[Z]+c[Z];
}

void VecMultf(VECTORF a, VECTORF b, VECTORF c)
{
	c[X]=a[X]*b[X];
	c[Y]=a[Y]*b[Y];
	c[Z]=a[Z]*b[Z];
}

void VecScalef(VECTORF a, float scale, VECTORF b)
{
	b[X]=a[X]*scale;
	b[Y]=a[Y]*scale;
	b[Z]=a[Z]*scale;
}

float VecDiFFf(VECTORF a, VECTORF b)
{
	float fDiff;

	fDiff  = a[X]-b[X];
	fDiff += a[Y]-b[Y];
	fDiff += a[Z]-b[Z];

	return fDiff;
}

float VecDotf(VECTORF a, VECTORF b)
{
	float f;
	f = (a[X]*b[X] + a[Y]*b[Y] + a[Z]*b[Z]);
	return(Roundf(f, 5));
}

void VecCrossf(VECTORF a, VECTORF b, VECTORF c)
{
	c[X]=a[Y]*b[Z] - a[Z]*b[Y];
	c[Y]=a[Z]*b[X] - a[X]*b[Z];
	c[Z]=a[X]*b[Y] - a[Y]*b[X];
}

float VecLenf(VECTORF a)
{
	return(float)(sqrt(a[X]*a[X] + a[Y]*a[Y] + a[Z]*a[Z]));
}

void VecNormalizef(VECTORF a)
{
	float dist,invdist;

	dist=VecLenf(a);
	if(dist)
	{
		invdist=1.0f/dist;
		a[X]*=invdist;
		a[Y]*=invdist;
		a[Z]*=invdist;
		a[3]*=invdist;
	}
}

void CalNormalf(VECTORF a, VECTORF b, VECTORF c, VECTORF n, bool bCCW)
{
	// Calculate the surface normals of a plane, given points a, b and c
	// which reside on the surface of the plane.
	/*
                     ^ Vn (Normal)
                     |
                     | 
                     |
                     | 
                 Va  *------------------* Vb  (Vu)
                    /                 /
                  /                 / 
                /                 /
              /                 /
         Vc *------------------
       (Vv)	

	*/
	VECTORF	u, v;

	VecSubf(b, a, u);
	VecSubf(c, a, v);
	if(bCCW)
		VecCrossf(u, v, n);
	else
		VecCrossf(v, u, n);
	VecNormalizef(n);
}

bool GetVecAnglef(VECTORF a, VECTORF b, float *fAngle)
{
	// Calculate angle between two Normal vectors
	// where:
	//		u.v = u1v1 + u2v2 + u3v3
	//		u.v = |u||v|cos theta
	//		theta = inv cos(u.v/|u||v|)
	//

	double dLength;
	double dTheta = 0.;

	dLength = VecLenf(a)*VecLenf(b);
	if(dLength)	// Don't divide by Zero!
	{
		// Calculate the angle between the vectors
		dTheta = (VecDotf(a, b)) / dLength;
		if(fabs(dTheta-1) < SMALL_NUMBER)
		{
			*fAngle = 0;
			return true;
		}
		(*fAngle) = Degreesf((float)acos(dTheta));
		if(*fAngle)
			return true;
		else
		{
			// The acos function returns the arccosine of x in the
			// range 0 to PI radians. If x is less than -1 or greater than 1,
			// acos returns an indefinite result.
			if(dTheta < -1)
				*fAngle = 180.0f;
			else
				*fAngle = 0.0f;

			return true;
		}
	}
	else
		return false;
}

void GetEulerXYFromVector(VECTORF vec, float *rx, float *ry, float *rz)
{
	// Extract the Euler XY rotation values that points the Z-Axis in the 
	// direction of the given vector.
	//
	Matx4x4	matx;
	VECTORF	vecY;

	// Calculate the rotation about the x-axis
	if(vec[Y]==0)
		*rx = 0;
	else
		*rx = -Degreesf((float)atan2(vec[Y], vec[Z]));

	// Compensate for rounding errors
	Roundf(*rx, 5);

	// Rotate the vector by the inverse of the x-axis rotation
	Rotate3D(X, -*rx, matx);
	VecTransformf(vec, vecY, matx);

	// Calculate the rotation about the y-axis
	if(vecY[X]==0 && vecY[Z]>0)
		*ry = 0.0f;
	else
		*ry = Degreesf((float)atan2(vecY[X], vecY[Z]));

	// Compensate for rounding errors
	Roundf(*ry, 5);

	// Rotation about the z-axis is ambiguous, so we set it to zero
	*rz=0;
}


void GetCenterVec(VECTORF a, VECTORF b, VECTORF c, VECTORF center)
{
	VecAdd3f( a,  b,  c, center);
	VecScalef(center, 1.f/3.0f, center);
}

float GetAreaTriangle(VECTORF a, VECTORF b, VECTORF c)
{
	VECTORF p1;	VecCopyf(a,p1); 
	VECTORF p2;	VecCopyf(b,p2);
	VECTORF p3;	VecCopyf(c,p3);
	VECTORF xy;	VecSubf(p2,p1,xy);
	VECTORF xz;	VecSubf(p3,p1,xz);

	float fa = sqrtf(xy[X] * xy[X] + xy[Y] * xy[Y] + xy[Z] * xy[Z]);
	float fc = sqrtf(xz[X] * xz[X] + xz[Y] * xz[Y] + xz[Z] * xz[Z]);
	float fB = 0.0f;
	// Actually, its ok - this bit calculates the area.
	{
		VECTORF xyNorm;VecCopyf(xy,xyNorm);
		VecNormalizef(xyNorm);
		VECTORF xzNorm;VecCopyf(xz,xzNorm);
		VecNormalizef(xzNorm);
		float fDot = VecDotf(xyNorm, xzNorm);
		float fAngle = (float)acos(fDot);
		fB = fAngle;
	}
	
	return (float)((fa * fc * sin(fB))/2.0f);
}


void MakePlane(VECTORF PlnX, VECTORF PlnY, VECTORF PlnPoint, float Scale , VECTORF RectPoint1, VECTORF RectPoint2, VECTORF RectPoint3, VECTORF RectPoint4)
{

	VECTORF tempvec01;
	VECTORF tempvec02;
	VECTORF tempvec03;
	VECTORF tempvec04;
	VecScalef(PlnX, Scale, tempvec01);
	VecScalef(PlnY, Scale, tempvec02);
	VecScalef(PlnX, Scale* -1.0f, tempvec03);
	VecScalef(PlnY, Scale* -1.0f, tempvec04);
	VecAdd3f(PlnPoint, tempvec01, tempvec02, RectPoint1);
	VecAdd3f(PlnPoint, tempvec01, tempvec04, RectPoint2);
	VecAdd3f(PlnPoint, tempvec03, tempvec04, RectPoint3);
	VecAdd3f(PlnPoint, tempvec03, tempvec02, RectPoint4);
}

int GetIntersectPoint(VECTORF AP1, VECTORF AP2, 
                       VECTORF BP1, VECTORF BP2, VECTORF IP) 
{
    double t;
    double s; 
    double under = (BP2[Y]-BP1[Y])*(AP2[X]-AP1[X])-(BP2[X]-BP1[X])*(AP2[Y]-AP1[Y]);
    if(under==0) return 0;

    double _t = (BP2[X]-BP1[X])*(AP1[Y]-BP1[Y]) - (BP2[Y]-BP1[Y])*(AP1[X]-BP1[X]);
    double _s = (AP2[X]-AP1[X])*(AP1[Y]-BP1[Y]) - (AP2[Y]-AP1[Y])*(AP1[X]-BP1[X]); 

    t = _t/under;
    s = _s/under; 

    if(t<0.0 || t>1.0 || s<0.0 || s>1.0) return -1;
    if(_t==0 && _s==0) return -1; 

    IP[X] = float(AP1[X] + t * (AP2[X]-AP1[X]));
    IP[Y] = float(AP1[Y] + t * (AP2[Y]-AP1[Y]));

    return 1;
}

double max3n(double a, double b, double c){
	double af, bf, cf;
	if(a<0) af=-a;
	else af=a;
	if(b<0) bf=-b;
	else bf=b;
	if(c<0) cf=-c;
	else cf=c;

	if(af>=bf){
		if(af>=cf){
			return a;
		} else {
			return c;
		}
	} else {
		if(bf>=cf){
			return b;
		} else {
			return c;
		}
	}
}

 int GetIntersectPoint3Plane(VECTORF APlane1, VECTORF APlane2, VECTORF APlane3, VECTORF BPoint)
 {
	int i,j,k;
	
	double a[4]={2,4,6,2};
	double b[4]={3,-2,1,-5};
	double c[4]={1,2,-1,9};
	double temp,x1,x2,x3;
	double t[4]={0,0,0,0};
	double ta[4]={0,0,0,0};
	double tb[4]={0,0,0,0};
	double tc[4]={0,0,0,0};
	a[0]=APlane1[0];	a[1]=APlane1[1];	a[2]=APlane1[2];	a[3]=APlane1[3];
	b[0]=APlane2[0];	b[1]=APlane2[1];	b[2]=APlane2[2];	b[3]=APlane2[3];
	c[0]=APlane3[0];	c[1]=APlane3[1];	c[2]=APlane3[2];	c[3]=APlane3[3];

//	double mmm[7];
//	mmm[1]=a[0]*b[2]-a[2]*b[0];
//	mmm[4]=a[1]*b[2]-a[2]*b[1];
//	mmm[3]=b[0]*c[2]-b[2]*c[0];
//	mmm[2]=b[1]*c[2]-b[2]*c[1];
//	mmm[5]=b[2]*c[3]-b[3]*c[2];
//	mmm[6]=a[2]*b[3]-a[3]*b[2];
//	BPoint[0] =  (mmm[4]*mmm[5]-mmm[2]*mmm[6])/(mmm[1]*mmm[2]-mmm[3]*mmm[4]);
//	BPoint[1] =  (mmm[3]*mmm[6]-mmm[1]*mmm[5])/(mmm[1]*mmm[2]-mmm[3]*mmm[4]);
//	BPoint[2] = (a[3]-BPoint[0]*a[0]-BPoint[1]*a[1])/a[2];
//	TRACE("x1 = %lf\n", BPoint[0]);
//	TRACE("x2 = %lf\n", BPoint[1]);
//	TRACE("x3 = %lf\n", BPoint[2]);
//return 0;
//	printf("첫행의 행렬 입력 띄워쓰기로 구분 : ");
//	scanf("%lf %lf %lf %lf", &a[0], &a[1], &a[2], &a[3]);
//	printf("둘째행의 행렬 입력 띄워쓰기로 구분 : ");
//	scanf("%lf %lf %lf %lf", &b[0], &b[1], &b[2], &b[3]);
//	printf("셋째행의 행렬 입력 띄워쓰기로 구분 : ");
//	scanf("%lf %lf %lf %lf", &c[0], &c[1], &c[2], &c[3]);
//	printf("원래 행렬 (확대계수행렬) : \n");
//	for(i=0;i<4;i++){
//		printf("%lf ",a[i]);
//	}
////	printf("\n");
//	for(i=0;i<4;i++){
//		printf("%lf ",b[i]);
//	}
//	printf("\n");
//	for(i=0;i<4;i++){
//		printf("%lf ",c[i]);
//	}
//	printf("\n\n");
//	
	// 피봇팅을 위해 첫행 비교
	if(a[0] == max3n(a[0],b[0],c[0])){
		for(i=0;i<4;i++){
			ta[i] = a[i];
			j = 1;
		}
	} else if(b[0] == max3n(a[0],b[0],c[0])){
		for(i=0;i<4;i++){
			ta[i] = b[i];
			j = 2;
		}
	} else {
		for(i=0;i<4;i++){
			ta[i] = c[i];
			j = 3;
		}
	}

 	// 피봇팅을 위해 둘째행 비교
	if(j == 1){
		if(b[1] == max3n(b[1],c[1],0)){
			for(i=0;i<4;i++){
				tb[i] = b[i];
			}
			k = 3;
		} else {
			for(i=0;i<4;i++){
				tb[i] = c[i];
			}
			k = 2;
		}
	} else if(j == 2){
		if(a[1] == max3n(a[1],c[1],0)){
			for(i=0;i<4;i++){
				tb[i] = a[i];
			}
			k = 3;
			
		} else {
			for(i=0;i<4;i++){
				tb[i] = c[i];
			}
			k = 1;

		}
	} else {
		if(a[1] == max3n(a[1],b[1],0)){
			for(i=0;i<4;i++){
				tb[i] = a[i];
			}
			k = 2;
		} else {
			for(i=0;i<4;i++){
				tb[i] = b[i];
			}
			k = 1;
		}
	}

	// 셋째행 채우기
	if(k == 1){
		for(i=0;i<4;i++){
			tc[i] = a[i];
		}
	} else if(k == 2){
		for(i=0;i<4;i++){
			tc[i] = b[i];
		}
	} else {
		for(i=0;i<4;i++){
			tc[i] = c[i];
		}
	}


	//printf("피봇팅 결과 (확대계수행렬) : \n");
	//for(i=0;i<4;i++){
	//	printf("%lf ",ta[i]);
	//}
	//printf("\n");
	//for(i=0;i<4;i++){
	//	printf("%lf ",tb[i]);
	//}
	//printf("\n");
	//for(i=0;i<4;i++){
	//	printf("%lf ",tc[i]);
	//}
	//printf("\n\n");
	a[i] = ta[i];
	b[i] = tb[i];
	c[i] = tc[i];



	// 첫행 소거
	temp = a[0];
	for(i=0;i<4;i++){
		a[i] = a[i] / temp;
	}
	for(i=0;i<4;i++){
		t[i] = a[i] * b[0];
	}
	for(i=0;i<4;i++){
		b[i] = b[i]-t[i];
	}
	for(i=0;i<4;i++){
		t[i] = a[i] * c[0];
	}
	for(i=0;i<4;i++){
		c[i] = c[i]-t[i];
	}
	temp = b[1];
	for(i=1;i<4;i++){
		b[i] /= temp;
	}
	for(i=0;i<4;i++){
		t[i] = b[i]*c[1];
	}
	for(i=0;i<4;i++){
		c[i] = c[i]-t[i];
	}
	temp = c[2];
	for(i=0;i<4;i++){
		c[i] = c[i] / temp;
	}
	for(i=0;i<4;i++){
		if(a[i] == -0) a[i] = 0;
		if(b[i] == -0) b[i] = 0;
		if(c[i] == -0) c[i] = 0;
	}
		
	//printf("결과 행렬 (확대계수행렬) : \n");
	//for(i=0;i<4;i++){
	//	printf("%lf ",a[i]);
	//}
	//printf("\n");
	//for(i=0;i<4;i++){
	//	printf("%lf ",b[i]);
	//}
	//printf("\n");
	//for(i=0;i<4;i++){
	//	printf("%lf ",c[i]);
	//}
	//printf("\n\n");

	//printf("결과 : \n");
	x3 = c[3];
	x2 = b[3] - b[2]*x3;
	x1 = a[3] - a[1]*x2 - a[2]*x3;
	/*TRACE("x1 = %lf\n", x1);
	TRACE("x2 = %lf\n", x2);
	TRACE("x3 = %lf\n", x3);*/
	Vec3f((float)x1, (float)x2, (float)x3, BPoint);
    return 1;
 }


/*****************************************************************************
 *
 *  Affine Matrix Transformation Routines
 *
 *****************************************************************************

  We define a 4x4 matrix array, referenced as Row,Column as:

		| 0,0  0,1  0,2  0,3 |
		|                    |	
		| 1,0  1,1  1,2  1,3 |
		|                    |	
		| 2,0  2,1  2,2  2,3 |
		|                    |	
		| 3,0  3,1  3,2  3,3 |
*/

void ZeroMatrix(Matx4x4 a)
{
	// Initialize the matrix to the following values:
	//		0.0		0.0		0.0		0.0
	//		0.0		0.0		0.0		0.0
	//		0.0		0.0		0.0		0.0
	//		0.0		0.0		0.0		0.0
	//
	int i, j;

	for (i=0; i<4; i++)
	{
		for (j=0; j<4; j++)
			a[i][j]=0.0;
	}
}

void IdentityMatrix(Matx4x4 a)
{
	// Initialize the matrix to the following values:
	//		1.0		0.0		0.0		0.0
	//		0.0		1.0		0.0		0.0
	//		0.0		0.0		1.0		0.0
	//		0.0		0.0		0.0		1.0
	//
	int i, j;

	for (i=0; i<4; i++)
	{
		for (j=0; j<4; j++)
		{
			if(i==j)
				a[i][j]=1.0;
			else
				a[i][j]=0.0;
		}
	}
}

void Translate3D(float tx, float ty, float tz, Matx4x4 a)
{
	//	Translation matrix identified as:
	//		 ----------------
	//		| 1   0   0   Tx |
	//		| 0   1   0   Ty |
	//		| 0   0   1   Tz |
	//		| 0   0   0   1  |
	//		 ----------------
	int i;

	ZeroMatrix(a);
	for (i=0; i<4; i++)
		a[i][i]=1.0;

	a[X][3]=tx;
	a[Y][3]=ty;
	a[Z][3]=tz;
}

void Scale3D(float sx, float sy, float sz, Matx4x4 a)
{
	// Scaling matrix identified as:
	//		 ----------------
	//		| Sx  0   0   0 |
	//		| 0   Sy  0   0 |
	//		| 0   0   Sz  0 |
	//		| 0   0   0   1 |
	//		 ----------------

	ZeroMatrix(a);
	a[X][X]=sx;
	a[Y][Y]=sy;
	a[Z][Z]=sz;
	a[3][3]=1.0;
}

void Rotate3D(int m, float Theta, Matx4x4 a)
{
	float c, s;
	c = s = 0.f;

	ZeroMatrix(a);
	c=Cosf(Theta);
	s=Sinf(Theta);

	// Compensate for rounding errors
	if(fabs(c)<SMALL_NUMBER)
		c=0.0f;
	if(fabs(s)<SMALL_NUMBER)
		s=0.0f;

	switch(m)
	{
		case X:
			//	Rotation about the X-Axis matrix identified as:
			//		 -----------------------
			//		| 1     0      0      0 |
			//		| 0     cosX   -sinX  0 |
			//		| 0     sinX   cosX   0 |
			//		| 0     0      0      1 |
			//		 -----------------------

			a[X][X]= 1.0;
			a[Y][Y]= c;
			a[Y][Z]=-s;
			a[Z][Y]= s;
			a[Z][Z]= c;
			a[3][3]= 1.0;
			break;

		case Y:
			//	Rotation about the Y-Axis matrix identified as:
			//		 -----------------------
			//		| cosY  0      sinY   0 |
			//		| 0     1      0      0 |
			//		| -sinY 0      cosY   0 |
			//		| 0     0      0      1 |
			//		 -----------------------

			a[X][X]= c;
			a[X][Z]= s;
			a[Y][Y]= 1.0;
			a[Z][X]=-s;
			a[Z][Z]= c;
			a[3][3]= 1.0;
			break;

		case Z:
			//	Rotation about the Z-Axis matrix identified as:
			//		 -----------------------
			//		| cosZ  -sinZ  0      0 |
			//		| sinZ  cosZ   0      0 |
			//		| 0     0      1      0 |
			//		| 0     0      0      1 |
			//		 -----------------------

			a[X][X]= c;
			a[X][Y]=-s;
			a[Y][X]= s;
			a[Y][Y]= c;
			a[Z][Z]= 1.0;
			a[3][3]= 1.0;
			break;
	}
}
	
void MultiplyMatricies(Matx4x4 a, Matx4x4 b, Matx4x4 c)
{
	int   i, j, k;

	for(i=0; i<4; i++)
	{
		for(j=0; j<4; j++)
		{
			for(k=0, c[i][j]=0; k<4; k++)
				c[i][j] += a[i][k] * b[k][j];
		}
	}
}

void MatrixCopy(Matx4x4 a, Matx4x4 b)
{
	int  i, j;

	for(i=0; i<4; i++)
	{
		for(j=0; j<4; j++)
			b[i][j]=a[i][j];
	}
}

void TransposeMatrix(Matx4x4 a)
{
	Matx4x4 M;
	int  i, j;

	for(i=0; i<4; i++)
	{
		for(j=0; j<4; j++)
			M[j][i]=a[i][j];
	}
	MatrixCopy(M, a);
}

void PrepareMatrix(float Ox,  float Oy,  float Oz,
				   float Sx,  float Sy,  float Sz,
				   float Rx,  float Ry,  float Rz,
				   float Tx,  float Ty,  float Tz,
				   Matx4x4 XForm)
{
	Matx4x4 M1, M2, M3, M4, M5, M6, M7, M8, M9, M10;


	Translate3D(Tx, Ty, Tz, M1);
	Scale3D(Sx, Sy, Sz, M2);
	Rotate3D(Z, Rz, M3);
	Rotate3D(Y, Ry, M4);
	Rotate3D(X, Rx, M5);
	Translate3D(Ox, Oy, Oz, M6);

	MultiplyMatricies(M2, M1, M7);
	MultiplyMatricies(M3, M7, M8);
	MultiplyMatricies(M4, M8, M9);
	MultiplyMatricies(M5, M9, M10);
	MultiplyMatricies(M6, M10, XForm);
}

void PrepareInvMatrix(float Ox,  float Oy,  float Oz,
					  float Sx,  float Sy,  float Sz,
					  float Rx,  float Ry,  float Rz,
					  float Tx,  float Ty,  float Tz,
					  Matx4x4 XForm)
{
	Matx4x4 M1, M2, M3, M4, M5, M6, M7, M8, M9, M10;

	Translate3D(-Ox, -Oy, -Oz, M1);
	Rotate3D(X, -Rx, M2);
	Rotate3D(Y, -Ry, M3);
	Rotate3D(Z, -Rz, M4);
	Scale3D(1/Sx, 1/Sy, 1/Sz, M5);
	Translate3D(-Tx, -Ty, -Tz, M6);

	MultiplyMatricies(M2, M1, M7);
	MultiplyMatricies(M3, M7, M8);
	MultiplyMatricies(M4, M8, M9);
	MultiplyMatricies(M5, M9, M10);
	MultiplyMatricies(M6, M10, XForm);
}

void SetRotationMatrix(float Rx,  float Ry,  float Rz,
					   Matx4x4 XForm)
{
	Matx4x4 M1, M2, M3, M4;

	Rotate3D(Z, Rz, M1);
	Rotate3D(Y, Ry, M2);
	Rotate3D(X, Rx, M3);

	MultiplyMatricies(M2, M1, M4);
	MultiplyMatricies(M3, M4, XForm);
}

void SetInvRotationMatrix(float Rx,  float Ry,  float Rz,
						  Matx4x4 XForm)
{
	Matx4x4 M1, M2, M3, M4;

	Rotate3D(X, -Rx, M1);
	Rotate3D(Y, -Ry, M2);
	Rotate3D(Z, -Rz, M3);

	MultiplyMatricies(M2, M1, M4);
	MultiplyMatricies(M3, M4, XForm);
}

void SetAxisRotationMatrix(VECTORF vtx, VECTORF axis,float angle, Matx4x4 XForm)
{
	VecNormalizef(axis);

	float ddd= (float)(sqrt(axis[Y]*axis[Y] + axis[Z]*axis[Z]));

	Matx4x4 M1, M2, M3, M4, M5, M6, M7, M8, M9, M10, M11, M12;
	
	IdentityMatrix(M2);
	M2[1][1]=axis[Z]/ddd;				M2[1][2]=(axis[Y]*-1.0f)/ddd*-1.0f;
	M2[2][1]=(axis[Y]*-1.0f)/ddd;		M2[2][2]=axis[Z]/ddd;
	IdentityMatrix(M3);
	M3[0][0]=ddd;						M3[0][2]=axis[X];
	M3[2][0]=axis[X]*-1.0f;				M3[2][2]=ddd;

	IdentityMatrix(M5);
	M5[0][0]=ddd;						M5[0][2]=axis[X]*-1.0f;
	M5[2][0]=axis[X];					M5[2][2]=ddd;
	IdentityMatrix(M6);
	M6[1][1]=axis[Z]/ddd;				M6[1][2]=axis[Y]/ddd*-1.0f;
	M6[2][1]=axis[Y]/ddd;				M6[2][2]=axis[Z]/ddd;

	Translate3D(vtx[X], vtx[Y], vtx[Z], M1);
	Rotate3D(Z, Degreesf(angle), M4);
	Translate3D(vtx[X]* -1.0f, vtx[Y]* -1.0f, vtx[Z]* -1.0f, M7);


	MultiplyMatricies(M1, M2, M8);
	MultiplyMatricies(M8, M3, M9);
	MultiplyMatricies(M9, M4, M10);
	MultiplyMatricies(M10, M5, M11);
	MultiplyMatricies(M11, M6, M12);
	MultiplyMatricies(M12, M7, XForm);

}


void VecTransformf(VECTORF S, VECTORF d, Matx4x4 M)
{
	double x, y, z;
	x = y = z = 0.;

	// Transform the Source vector 'S' by the matrix 'M'
	x = M[X][X]*S[X] + M[X][Y]*S[Y] + M[X][Z]*S[Z] + M[X][3];//*S[3];
	y = M[Y][X]*S[X] + M[Y][Y]*S[Y] + M[Y][Z]*S[Z] + M[Y][3];//*S[3];
	z = M[Z][X]*S[X] + M[Z][Y]*S[Y] + M[Z][Z]*S[Z] + M[Z][3];//*S[3];

	// Compensate for rounding errors
	if(fabs(x) < SMALL_NUMBER)
		x = 0.0f;
	if(fabs(y) < SMALL_NUMBER)
		y = 0.0f;
	if(fabs(z) < SMALL_NUMBER)
		z = 0.0f;

	// Store the transformed values in the Destination
	// vector 'd'
	d[X] = (float)x;
	d[Y] = (float)y;
	d[Z] = (float)z;
}

void MatrixToEuler(Matx4x4 M, float *rx, float *ry, float *rz, bool bPositive)
{
	double C;
	double tx, ty;

	// Calculate the Y-Axis angle
	*ry  = (float)asin(M[X][Z]);
	C	 = cos(*ry);
	*ry *= (float)PiUnder180;

	if(fabs(C) > SMALL_NUMBER)	// Gimball lock?
	{
		// No gimball lock, so calculate the XZ-Axis angles
		tx	=  M[Z][Z]/C;
		ty	= -M[Y][Z]/C;
		*rx	= (float)(atan2(ty, tx) * PiUnder180);

		tx	=  M[X][X]/C;
		ty	= -M[X][Y]/C;
		*rz	= (float)(atan2(ty, tx) * PiUnder180);
	}
	else
	{
		// Gimball lock has occurred, so set the X-Axis angle to Zero and 
		// calculate the Z-Axis angle.
		*rx	= 0.0f;
		tx	= M[Y][Y];
		ty	= M[Y][X];
		*rz = (float)(atan2(ty, tx) * PiUnder180);
	}

	if(!bPositive) return;

	// Return only positive angles from [0-360]
	if(*rx < 0)	*rx += 360;
	if(*ry < 0)	*ry += 360;
	if(*rz < 0)	*rz += 360;
}

void MatrixToEuler(Matx4x4 M, VECTORF r, bool bPositive)
{
	double C;
	double tx, ty;

	// Calculate the Y-Axis angle
	r[Y]  = (float)asin(M[X][Z]);
	C	  = cos(r[Y]);
	r[Y] *= (float)PiUnder180;

	if(fabs(C) > SMALL_NUMBER)	// Gimball lock?
	{
		// No gimball lock, so calculate the XZ-Axis angles
		tx	 =  M[Z][Z]/C;
		ty	 = -M[Y][Z]/C;
		r[X] = (float)(atan2(ty, tx) * PiUnder180);
		tx	 =  M[X][X]/C;
		ty	 = -M[X][Y]/C;
		r[Z] = (float)(atan2(ty, tx) * PiUnder180);
	}
	else
	{
		// Gimball lock has occurred, so set the X-Axis angle to Zero and 
		// calculate the Z-Axis angle.
		r[X] = 0.0f;
		tx	 = M[Y][Y];
		ty	 = M[Y][X];
		r[Z] = (float)(atan2(ty, tx) * PiUnder180);
	}

	if(!bPositive) return;

	// Return only positive angles from [0-360]
	if(r[X] < 0)	r[X] += 360;
	if(r[Y] < 0)	r[Y] += 360;
	if(r[Z] < 0)	r[Z] += 360;
}


/*****************************************************************************
 *
 *  Misc OpenGL Related Functions:
 *
 *****************************************************************************
  We define a 4x4 matrix array,			OpenGL linear matrix format:
  referenced as Row,Column as:

	| 0,0  0,1  0,2  0,3 |					|a0  a4  a8   a12|
	|                    |					|                |
	| 1,0  1,1  1,2  1,3 |					|a1  a5  a9   a13|
	|                    |					|                |
	| 2,0  2,1  2,2  2,3 |					|a2  a6  a10  a14|
	|                    |					|                |
	| 3,0  3,1  3,2  3,3 |					|a3  a7  a11  a15|

 */

void GLMatrixTo4x4(double M[16], Matx4x4 a)
{
	int i, j;

	for(i=0; i<4; i++)
	{
		for(j=0; j<4; j++)
			a[i][j]=(float)M[(i*4)+j];
	}
}

void Matx4x4ToGLMatrix(Matx4x4 a, double M[16])
{
	int i, j;

	for(i=0; i<4; i++)
	{
		for(j=0; j<4; j++)
			M[(i*4)+j]=(double)a[j][i];
	}
}

void GLIdentityMatrix(double M[16])
{
	// Initialize the matrix to the following values:
	//		1.0		0.0		0.0		0.0
	//		0.0		1.0		0.0		0.0
	//		0.0		0.0		1.0		0.0
	//		0.0		0.0		0.0		1.0
	//
	memset(M, 0, sizeof(double)*16);
	M[X] = M[5] = M[10] = M[15] = 1.0;
}

// Compute inverse of 4x4 transformation matrix.
// Code contributed by Jacques Leroy jle@star.be
// Return true for success, false for failure (singular matrix)
//
#define SWAP_ROWS(a, b) { double *_tmp = a; (a)=(b); (b)=_tmp; }
#define MAT(m,r,c) (m)[(c)*4+(r)]

bool InvertGLMatrix(double mat[16], double out[16])
{
   const double *m   = mat;
   double wtmp[4][8];
   double m0, m1, m2, m3, s;
   double *r0, *r1, *r2, *r3;
  
   r0 = wtmp[X], r1 = wtmp[Y], r2 = wtmp[Z], r3 = wtmp[3];
  
   r0[X] = MAT(m,0,0), r0[Y] = MAT(m,0,1),
   r0[Z] = MAT(m,0,2), r0[3] = MAT(m,0,3),
   r0[4] = 1.0, r0[5] = r0[6] = r0[7] = 0.0,
  
   r1[X] = MAT(m,1,0), r1[Y] = MAT(m,1,1),
   r1[Z] = MAT(m,1,2), r1[3] = MAT(m,1,3),
   r1[5] = 1.0, r1[4] = r1[6] = r1[7] = 0.0,
  
   r2[X] = MAT(m,2,0), r2[Y] = MAT(m,2,1),
   r2[Z] = MAT(m,2,2), r2[3] = MAT(m,2,3),
   r2[6] = 1.0, r2[4] = r2[5] = r2[7] = 0.0,
  
   r3[X] = MAT(m,3,0), r3[Y] = MAT(m,3,1),
   r3[Z] = MAT(m,3,2), r3[3] = MAT(m,3,3),
   r3[7] = 1.0, r3[4] = r3[5] = r3[6] = 0.0;
  
   /* choose pivot - or die */
   if (fabs(r3[X])>fabs(r2[X])) SWAP_ROWS(r3, r2);
   if (fabs(r2[X])>fabs(r1[X])) SWAP_ROWS(r2, r1);
   if (fabs(r1[X])>fabs(r0[X])) SWAP_ROWS(r1, r0);
   if (0.0 == r0[X])  return false;
  
   /* eliminate first variable     */
   m1 = r1[X]/r0[X]; m2 = r2[X]/r0[X]; m3 = r3[X]/r0[X];
   s = r0[Y]; r1[Y] -= m1 * s; r2[Y] -= m2 * s; r3[Y] -= m3 * s;
   s = r0[Z]; r1[Z] -= m1 * s; r2[Z] -= m2 * s; r3[Z] -= m3 * s;
   s = r0[3]; r1[3] -= m1 * s; r2[3] -= m2 * s; r3[3] -= m3 * s;
   s = r0[4];
   if (s != 0.0) { r1[4] -= m1 * s; r2[4] -= m2 * s; r3[4] -= m3 * s; }
   s = r0[5];
   if (s != 0.0) { r1[5] -= m1 * s; r2[5] -= m2 * s; r3[5] -= m3 * s; }
   s = r0[6];
   if (s != 0.0) { r1[6] -= m1 * s; r2[6] -= m2 * s; r3[6] -= m3 * s; }
   s = r0[7];
   if (s != 0.0) { r1[7] -= m1 * s; r2[7] -= m2 * s; r3[7] -= m3 * s; }
  
   /* choose pivot - or die */
   if (fabs(r3[Y])>fabs(r2[Y])) SWAP_ROWS(r3, r2);
   if (fabs(r2[Y])>fabs(r1[Y])) SWAP_ROWS(r2, r1);
   if (0.0 == r1[Y])  return false;
  
   /* eliminate second variable */
   m2 = r2[Y]/r1[Y]; m3 = r3[Y]/r1[Y];
   r2[Z] -= m2 * r1[Z]; r3[Z] -= m3 * r1[Z];
   r2[3] -= m2 * r1[3]; r3[3] -= m3 * r1[3];
   s = r1[4]; if (0.0 != s) { r2[4] -= m2 * s; r3[4] -= m3 * s; }
   s = r1[5]; if (0.0 != s) { r2[5] -= m2 * s; r3[5] -= m3 * s; }
   s = r1[6]; if (0.0 != s) { r2[6] -= m2 * s; r3[6] -= m3 * s; }
   s = r1[7]; if (0.0 != s) { r2[7] -= m2 * s; r3[7] -= m3 * s; }
  
   /* choose pivot - or die */
   if (fabs(r3[Z])>fabs(r2[Z])) SWAP_ROWS(r3, r2);
   if (0.0 == r2[Z])  return false;
  
   /* eliminate third variable */
   m3 = r3[Z]/r2[Z];
   r3[3] -= m3 * r2[3], r3[4] -= m3 * r2[4],
   r3[5] -= m3 * r2[5], r3[6] -= m3 * r2[6],
   r3[7] -= m3 * r2[7];
  
   /* last check */
   if (0.0 == r3[3]) return false;
  
   s = 1.0/r3[3];              /* now back substitute row 3 */
   r3[4] *= s; r3[5] *= s; r3[6] *= s; r3[7] *= s;
  
   m2 = r2[3];                 /* now back substitute row 2 */
   s  = 1.0/r2[Z];
   r2[4] = s * (r2[4] - r3[4] * m2), r2[5] = s * (r2[5] - r3[5] * m2),
   r2[6] = s * (r2[6] - r3[6] * m2), r2[7] = s * (r2[7] - r3[7] * m2);
   m1 = r1[3];
   r1[4] -= r3[4] * m1, r1[5] -= r3[5] * m1,
   r1[6] -= r3[6] * m1, r1[7] -= r3[7] * m1;
   m0 = r0[3];
   r0[4] -= r3[4] * m0, r0[5] -= r3[5] * m0,
   r0[6] -= r3[6] * m0, r0[7] -= r3[7] * m0;
  
   m1 = r1[Z];                 /* now back substitute row 1 */
   s  = 1.0/r1[Y];
   r1[4] = s * (r1[4] - r2[4] * m1), r1[5] = s * (r1[5] - r2[5] * m1),
   r1[6] = s * (r1[6] - r2[6] * m1), r1[7] = s * (r1[7] - r2[7] * m1);
   m0 = r0[Z];
   r0[4] -= r2[4] * m0, r0[5] -= r2[5] * m0,
   r0[6] -= r2[6] * m0, r0[7] -= r2[7] * m0;
  
   m0 = r0[Y];                 /* now back substitute row 0 */
   s  = 1.0/r0[X];
   r0[4] = s * (r0[4] - r1[4] * m0), r0[5] = s * (r0[5] - r1[5] * m0),
   r0[6] = s * (r0[6] - r1[6] * m0), r0[7] = s * (r0[7] - r1[7] * m0);
  
   MAT(out,0,0) = r0[4]; MAT(out,0,1) = r0[5],
   MAT(out,0,2) = r0[6]; MAT(out,0,3) = r0[7],
   MAT(out,1,0) = r1[4]; MAT(out,1,1) = r1[5],
   MAT(out,1,2) = r1[6]; MAT(out,1,3) = r1[7],
   MAT(out,2,0) = r2[4]; MAT(out,2,1) = r2[5],
   MAT(out,2,2) = r2[6]; MAT(out,2,3) = r2[7],
   MAT(out,3,0) = r3[4]; MAT(out,3,1) = r3[5],
   MAT(out,3,2) = r3[6]; MAT(out,3,3) = r3[7]; 
  
   return true;
}
#undef SWAP_ROWS

void Transformf(VECTORF S, VECTORF d, double M[16])
{
	double x, y, z;

	// Transform the Source vector 'S' by the matrix 'M'
	x = M[X]*S[X] + M[4]*S[Y] + M[8] *S[Z] + M[12];
	y = M[Y]*S[X] + M[5]*S[Y] + M[9] *S[Z] + M[13];
	z = M[Z]*S[X] + M[6]*S[Y] + M[10]*S[Z] + M[14];

	// Compensate for rounding errors
	if(fabs(x) < SMALL_NUMBER)
		x = 0.0f;
	if(fabs(y) < SMALL_NUMBER)
		y = 0.0f;
	if(fabs(z) < SMALL_NUMBER)
		z = 0.0f;

	// Store the transformed values in the Destination
	// vector 'd'
	d[X] = (float)x;
	d[Y] = (float)y;
	d[Z] = (float)z;
}

/* dst = transpose(src) */
void TransposeGLMatrix(double dst[16], double src[16])
{
	dst[X] = src[X];
	dst[Y] = src[4];
	dst[Z] = src[8];
	dst[3] = src[12];

	dst[4] = src[Y];
	dst[5] = src[5];
	dst[6] = src[9];
	dst[7] = src[13];

	dst[8] = src[Z];
	dst[9] = src[6];
	dst[10] = src[10];
	dst[11] = src[14];

	dst[12] = src[3];
	dst[13] = src[7];
	dst[14] = src[11];
	dst[15] = src[15];
}

/* dst = a + b */
void AddGLMatrices(double dst[16], double a[16], double b[16])
{
	dst[X] = a[X] + b[X];
	dst[Y] = a[Y] + b[Y];
	dst[Z] = a[Z] + b[Z];
	dst[3] = a[3] + b[3];

	dst[4] = a[4] + b[4];
	dst[5] = a[5] + b[5];
	dst[6] = a[6] + b[6];
	dst[7] = a[7] + b[7];

	dst[8] = a[8] + b[8];
	dst[9] = a[9] + b[9];
	dst[10] = a[10] + b[10];
	dst[11] = a[11] + b[11];

	dst[12] = a[12] + b[12];
	dst[13] = a[13] + b[13];
	dst[14] = a[14] + b[14];
	dst[15] = a[15] + b[15];
}

/* dst = a * b */
void MultGLMatrices(double dst[16], const double a[16], const double b[16])
{
	int i, j;

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			dst[i * 4 + j] = b[i * 4 + 0] * a[0 * 4 + j] +
							 b[i * 4 + 1] * a[1 * 4 + j] +
							 b[i * 4 + 2] * a[2 * 4 + j] +
							 b[i * 4 + 3] * a[3 * 4 + j];
		}
	}
}

void CopyGLMatrix(double dst[16], double src[16])
{
	int i;

	for (i=0; i<16; i++)
		dst[i] = src[i];
}

void BuildGLFrustumMatrix(double m[16], double l, double r, double b, double t,
						double n, double f)
{
	m[X] = (2.0*n) / (r-l);
	m[Y] = 0.0;
	m[Z] = 0.0;
	m[3] = 0.0;

	m[4] = 0.0;
	m[5] = (2.0*n) / (t-b);
	m[6] = 0.0;
	m[7] = 0.0;

	m[8] = (r+l) / (r-l);
	m[9] = (t+b) / (t-b);
	m[10] = -(f+n) / (f-n);
	m[11] = -1.0;

	m[12] = 0.0;
	m[13] = 0.0;
	m[14] = -(2.0*f*n) / (f-n);
	m[15] = 0.0;
}

void BuildGLPerspectiveMatrix(double m[16], double fovy, double aspect,
							  double zNear, double zFar)
{
	double xmin, xmax, ymin, ymax;

	ymax = zNear * tan(fovy * Pi / 360.0);
	ymin = -ymax;

	xmin = ymin * aspect;
	xmax = ymax * aspect;

	BuildGLFrustumMatrix(m, xmin, xmax, ymin, ymax, zNear, zFar);
}

/* Build a 4x4 matrix transform based on the parameters for gluLookAt.
 * Code lifted from Brian Paul's MesaGLU.
 */
void BuildGLLookAtMatrix(double m[16], double eyex, double eyey, double eyez,
						 double centerx, double centery, double centerz,
						 double upx, double upy, double upz)
{
	double x[3], y[3], z[3];
	double mag;

	/* Make rotation matrix */

	/* Z vector */
	z[X] = eyex - centerx;
	z[Y] = eyey - centery;
	z[Z] = eyez - centerz;
	if(z[X]==0) z[X] = 0.01;
	if(z[Y]==0) z[Y] = 0.01;
	if(z[Z]==0) z[Z] = 0.01;
	mag = sqrt( z[X]*z[X] + z[Y]*z[Y] + z[Z]*z[Z] );
	if (mag)	// mpichler, 19950515
	{
		z[X] /= mag;
		z[Y] /= mag;
		z[Z] /= mag;
	}

	/* Y vector */
	y[X] = upx;
	y[Y] = upy;
	y[Z] = upz;

	/* X vector = Y cross Z */
	x[X] =  y[Y]*z[Z] - y[Z]*z[Y];
	x[Y] = -y[X]*z[Z] + y[Z]*z[X];
	x[Z] =  y[X]*z[Y] - y[Y]*z[X];

	/* Recompute Y = Z cross X */
	y[X] =  z[Y]*x[Z] - z[Z]*x[Y];
	y[Y] = -z[X]*x[Z] + z[Z]*x[X];
	y[Z] =  z[X]*x[Y] - z[Y]*x[X];

	/* mpichler, 19950515 */
	/* cross product gives area of parallelogram, which is < 1.0 for
	 * non-perpendicular unit-length vectors; so normalize x, y here
	 */

	mag = sqrt( x[X]*x[X] + x[Y]*x[Y] + x[Z]*x[Z] );
	if (mag)
	{
		x[X] /= mag;
		x[Y] /= mag;
		x[Z] /= mag;
	}

	mag = sqrt( y[X]*y[X] + y[Y]*y[Y] + y[Z]*y[Z] );
	if (mag)
	{
		y[X] /= mag;
		y[Y] /= mag;
		y[Z] /= mag;
	}

#define M(row,col)  m[col*4+row]
	M(0,0) = x[X];  M(0,1) = x[Y];  M(0,2) = x[Z];  M(0,3) = -x[X]*eyex + -x[Y]*eyey + -x[Z]*eyez;
	M(1,0) = y[X];  M(1,1) = y[Y];  M(1,2) = y[Z];  M(1,3) = -y[X]*eyex + -y[Y]*eyey + -y[Z]*eyez;
	M(2,0) = z[X];  M(2,1) = z[Y];  M(2,2) = z[Z];  M(2,3) = -z[X]*eyex + -z[Y]*eyey + -z[Z]*eyez;
	M(3,0) = 0.0;   M(3,1) = 0.0;   M(3,2) = 0.0;   M(3,3) = 1.0;
#undef M
}

/* For debugging purposes. */
void PrintGLMatrix(char *msg, double m[16])
{
	/*TRACE("%s\n", msg);
	TRACE(" [ %f %f %f %f ]\n",   m[X], m[4], m[8],  m[12]);
	TRACE(" [ %f %f %f %f ]\n",   m[Y], m[5], m[9],  m[13]);
	TRACE(" [ %f %f %f %f ]\n",   m[Z], m[6], m[10], m[14]);
	TRACE(" [ %f %f %f %f ]\n\n", m[3], m[7], m[11], m[15]);*/
}


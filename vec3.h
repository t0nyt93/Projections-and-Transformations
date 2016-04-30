#include <stdio.h>
#include <string.h>
#define _USE_MATH_DEFINES
#include <cmath>

#ifndef VEC3_H
#define VEC3_H

class Vec3
{
public:
	float x, y, z;
	Vec3(float = 0, float = 0, float = 0);
	Vec3&   operator=(const Vec3&);
	Vec3    operator+(const Vec3&);
	Vec3    operator-(const Vec3&);       // binary -
	Vec3    operator-();                   // unary -
	Vec3    Cross(Vec3&);
	float   Dot(Vec3&);
	float   Length();
	void    Print(char * = "", FILE * = stderr);
	Vec3    Unit();
	float	X();
	float	Y();
	float	Z();


	friend class Mat4;
};


inline float
SQR(float f)
{
	return f * f;
}

#endif
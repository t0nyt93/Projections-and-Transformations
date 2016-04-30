#include "vec3.h"
#include <math.h>
Vec3::Vec3(float _x, float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;
}

Vec3&
Vec3::operator=(const Vec3& rhs)
{
	this->x = rhs.x;
	this->y = rhs.y;
	this->z = rhs.z;
	return *this;
}

Vec3
Vec3::operator+(const Vec3& that)
{
	// "this" is a pointer to this class's vec3  (this->name)
	// "that" is a reference to the other vector (that.name)
	Vec3 result;
	result.x = this->x + that.x;
	result.y = this->y + that.y;
	result.z = this->z + that.z;
	return result;
}

Vec3
Vec3::operator-(const Vec3& that)
{
	// "this" is a pointer to this class's vec3  (this->name)
	// "that" is a reference to the other vector (that.name)
	Vec3 result;
	result.x = this->x - that.x;
	result.y = this->y - that.y;
	result.z = this->z - that.z;
	return result;
}

Vec3
Vec3::operator-()
{
	// "this" is a pointer to this class's vec3  (this->name)
	// there is no "that" here
	Vec3 result;
	result.x = -(this->x) ;
	result.y = -(this->y);
	result.z = -(this->z) ;
	return result;
}

Vec3
Vec3::Cross(Vec3& that)
{
	// "this" is a pointer to this class's vec3  (this->name)
	// "that" is a reference to the other vector (that.name)
	Vec3 result;
	result.x = (this->y * that.z) - (this->z * that.y);
	result.y = (this->z * that.x) - (this->x * that.z);
	result.z = (this->x * that.y) - (this->y * that.x);
	return result;
}

float
Vec3::Dot(Vec3& that)
{
	// "this" is a pointer to this class's vec3  (this->name)
	// "that" is a reference to the other vector (that.name)
	float d = (this->x * that.x) + (this->y * that.y) + (this->z * that.z) ;
	return d;
}

float
Vec3::Length()
{
	// "this" is a pointer to this class's vec3  (this->name)
	float len = sqrt(pow(this->x,2.) + (pow(this->y,2.)) + pow(this->z,2.)) ;
	return len;
}

void
Vec3::Print(char *str, FILE *fp)
{
	fprintf(fp, "%s [ %8.3f %8.3f %8.3f ]\n", str, this->x, this->y, this->z);
}

Vec3
Vec3::Unit()
{
	// "this" is a pointer to this class's vec3  (this->name)
	Vec3 result;
	result.x = this->x / this->Length() ;
	result.y = this->y / this->Length();
	result.z = this->z / this->Length();
	return result;
}
float	Vec3::X()
{
	int x = this->x;
	return x;
}
float	Vec3::Y()
{
	int y = this->y;
	return y;
}
float	Vec3::Z()
{
	int z = this->z;
	return z;
}
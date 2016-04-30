#include "vec3.h"
#include "mat4.h"

	// ** 2A: **

Mat4::Mat4( )
{
	SetIdentity( );
}


Mat4::Mat4(	float a, float b, float c, float d, float e, float f, float g, float h,
		float i, float j, float k, float l, float n, float o, float p, float q )
{
	m[0][0]	= a;	m[0][1]	= b;	m[0][2]	= c;	m[0][3]	= d;
	m[1][0]	= e;	m[1][1]	= f;	m[1][2]	= g;	m[1][3]	= h;
	m[2][0]	= i;	m[2][1]	= j;	m[2][2]	= k;	m[2][3]	= l;
	m[3][0]	= n;	m[3][1]	= o;	m[3][2]	= p;	m[3][3]	= q;
}

Mat4&
Mat4::operator=( const Mat4& that )
{
	// "this" is a pointer to this class's mat4  (this->name)
	// "that" is a reference to the other matrix (that.name)
	int i,j,k;
	for(i=0; i < 4; i++ ){
		for(j=0;j<4;j++)
			{
			this->m[i][j] = that.m[i][j];
			}
	}
	
	return *this;
}

Mat4
Mat4::operator*( Mat4& that )
{
	// "this" is a pointer to this class's mat4  (this->name)
	// "that" is a reference to the other matrix (that.name)
    int i,j,k;
	Mat4 result;
	for(i=0;i<4;i++)
	{	
		for (int j = 0; j < 4; ++j)
		{
			result.m[i][j] = 0;
			for (int k = 0; k < 4; ++k)
			{	
				result.m[i][j] += this->m[i][k] * that.m[k][j];
			}
			/* code */
		}
	}
	//result.m ???
	return result;
}

Vec3
Mat4::operator*( Vec3& that )
{
	// "this" is a pointer to this class's mat4  (this->name)
	// "that" is a reference to the vector (that.name)

	Vec3 result;
	result.x = this->m[0][0] * that.x + this->m[0][1] * that.y + this->m[0][2] * that.z + this->m[0][3];
	result.y = this->m[1][0] * that.x + this->m[1][1] * that.y + this->m[1][2] * that.z + this->m[1][3];
	result.z = this->m[2][0] * that.x + this->m[2][1] * that.y + this->m[2][2] * that.z + this->m[2][3];
	
	return result;;
}

void
Mat4::Print( char *str, FILE *fp )
{
	// "this" is a pointer to this class's mat4  (this->name)

	fprintf( fp, "%s \n", str );
	fprintf( fp, "\t%8.2f  %8.2f  %8.2f  %8.2f\n", this->m[0][0], this->m[0][1], this->m[0][2], this->m[0][3] );
	fprintf( fp, "\t%8.2f  %8.2f  %8.2f  %8.2f\n", this->m[1][0], this->m[1][1], this->m[1][2], this->m[1][3] );
	fprintf( fp, "\t%8.2f  %8.2f  %8.2f  %8.2f\n", this->m[2][0], this->m[2][1], this->m[2][2], this->m[2][3] );
	fprintf( fp, "\t%8.2f  %8.2f  %8.2f  %8.2f\n", this->m[3][0], this->m[3][1], this->m[3][2], this->m[3][3] );
}

void
Mat4::SetIdentity( )
{
	// "this" is a pointer to this class's mat4  (this->name)
	int x,y;
	for(x=0;x<4;x++)
	{
		for(y=0;y<4;y++)
		{
			if(x == y)
			{
				this->m[x][y] = 1;
			}
			else
				this->m[x][y] = 0;

		}

	}

}

	// ** 2B: **

void
Mat4::SetRotateZ( float deg )
{
	// "this" is a pointer to this class's mat4  (this->name)
	float rad = D2R * deg;
	m[0][0] = m[1][1] = cos(rad);
	m[0][1] = -sin(rad);
	m[1][0] = sin(rad);
}

void
Mat4::SetRotateY( float deg )
{
	float rad = D2R * deg;
	m[0][0] = m[2][2] = cos(rad);
	m[0][2] = sin(rad);
	m[2][0] = -sin(rad);

}

void
Mat4::SetRotateX( float deg )
{

	float rad = D2R * deg;
	m[1][1] = m[2][2] = cos(rad);
	m[1][2] = -sin(rad);
	m[2][1] = sin(rad);

}



void
Mat4::SetScale( float sx, float sy, float sz )
{
	// "this" is a pointer to this class's mat4  (this->name)
	m[0][0] *= sx;
	m[1][1] *= sy;
	m[2][2] *= sz;
	//this->m ???
}
void
Mat4::SetOrthoGraphic(float l,float r, float t, float b, float n, float f)
{
	//Supposedly simplified and working?
	m[0][0] = 2./(r-l);		m[0][1] = 0.;			m[0][2] = 0.;			m[0][3] = -((r+l)/(r-l));
	m[1][0] = 0.;			m[1][1] = 2./(t-b);		m[1][2] = 0.;			m[1][3] = -((t+b)/(t-b));
	m[2][0] = 0.;			m[2][1] = 0.;			m[2][2] = -(2./(f-n));	m[2][3] = -((f+n)/(f-n));
	m[3][0] = 0.;			m[3][1] = 0.;			m[3][2] = 0.;			m[3][3] = 1.;

}
void
Mat4::SetPerspective(double a, double nZ, double fZ)
{
	a *= D2R;
	m[0][0] = 1. /tan(a/2.) ;	m[0][1] = 0.;	m[0][2] = 0.;	m[0][3] = 0.;
	m[1][0] = 0.;	m[1][1] = 1/tan(a/2.);	m[1][2] = 0.;	m[1][3] = 0.;
	m[2][0] = 0.;	m[2][1] = 0.;	m[2][2] = (-nZ-fZ)/nZ-fZ;	m[2][3] = (2. * nZ * fZ)/(nZ - fZ);
	m[3][0] = 0.;	m[3][1] = 0.;	m[3][2] = 1.;	m[3][3] = 0.;

}

void
Mat4::SetTranslate( float tx, float ty, float tz )
{
	// "this" is a pointer to this class's mat4  (this->name)

	m[0][3] = tx;
	m[1][3] = ty;
	m[2][3] = tz;

}
void
Mat4::SetCamera(Vec3 xAxis, Vec3 yAxis, Vec3 zAxis,Vec3 eye)
{
	//Colum Major...

	m[0][0] = xAxis.x;	m[0][1] = xAxis.y;	m[0][2] = xAxis.z;	m[0][3] = -(eye.Dot(xAxis));
	m[1][0] = yAxis.x;	m[1][1] = yAxis.y;	m[1][2] = yAxis.z;	m[1][3] = -(eye.Dot(yAxis));
	m[2][0] = zAxis.x;	m[2][1] = zAxis.y;	m[2][2] = zAxis.z;	m[2][3] = -(eye.Dot(zAxis));
	m[3][0] = 0.;	m[3][1] = 0.;	m[3][2] = 0.;	m[3][3] = 1.;
	

	//Row Major
	/*m[0][0] = xAxis.x;	m[0][1] = yAxis.x;	m[0][2] = zAxis.x;	m[0][3] = 0.;
	m[1][0] = xAxis.y;	m[1][1] = yAxis.y;	m[1][2] = zAxis.y;	m[1][3] = 0.;
	m[2][0] = xAxis.z;	m[2][1] = yAxis.z;	m[2][2] = zAxis.z;	m[2][3] = 0.;
	m[3][0] = -(eye.Dot(xAxis));	m[3][1] = -(eye.Dot(yAxis));	m[3][2] = -(eye.Dot(zAxis));	m[3][3] = 1.;
	*/
}

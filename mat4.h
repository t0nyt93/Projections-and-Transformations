#include <stdio.h>
#include <string.h>
#define _USE_MATH_INCLUDES
#include <cmath>
#include "vec3.h"

#ifndef MAT4_H
#define MAT4_H

class Mat4
{
     protected:
        float	m[4][4];

    public:
	Mat4( );
        Mat4( 	float, float, float, float, float, float, float, float,
		float, float, float, float, float, float, float, float );
	Mat4&	operator=( const Mat4& );
	Mat4 	operator*( Mat4& );
	Vec3 	operator*( Vec3& );
	void	Print( char * = "", FILE * = stderr );
	void	SetIdentity( );
	void	SetRotateX( float );
	void	SetRotateY( float );
	void	SetRotateZ( float );
	void	SetScale( float, float, float );
	void	SetTranslate( float, float, float );
	void    SetOrthoGraphic(float,float,float,float,float,float);
	void    SetPerspective(double,double,double);
	void	SetCamera(Vec3);
};

#ifndef D2R
#define D2R	( (float)M_PI / 180.f )
#endif

// don't need to declare SQR in here -- it is defined in vec3.h

#endif          // MAT4_H
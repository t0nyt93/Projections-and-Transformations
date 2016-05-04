/*

Dummy routines for matrix transformations.

These are for you to write!

*/


#include <stdio.h>
#include <math.h>
#include <fstream>
#include <Windows.h>
#include <ostream>
#include <sstream>
#include <string>
#include <queue>
#include "osuGraphics.h"
#include "lines.h"
#include "vec3.h"
#include "mat4.h"
 
double NP, FP;
//-------------------------------------------------

//------Data Structures ------------
struct myVertex {
	double myX = 0, myY = 0;
	int red, green, blue;
	int initialized = 0;
};
struct my3DVertex {
	Vec3 pos = Vec3();
	Vec3 color = Vec3();
	int intialized;
};

struct myTriangle {
	myVertex one = {}, two = {}, three = {};
	int currRed, currGreen, currBlue;
	double minX, maxX, minY, maxY;
}tDraw;

struct myLine {
	my3DVertex one, two;
}lDraw;

BOOL ORTHO = FALSE;
BOOL PROJECTION = FALSE;

//-------------------
std::queue<Mat4> matStack;
Vec3 u;
Mat4 Current_Transform = Mat4();
Mat4 persProj = Mat4();
Mat4 orthoProj = Mat4();
Mat4 myView = Mat4();
//-------------------
void osuOrtho(double left, double right, double bottom, double top, double nearp,double farp)
{ 
	NP = nearp;
	FP = farp;
	orthoProj.SetOrthoGraphic(left, right, top, bottom, nearp, farp);
	printf("Set Ortho graphic\n");
	orthoProj.Print();
	ORTHO = TRUE;
	PROJECTION = FALSE;
}
void osuPerspective(double fovy, double nearp, double farp) 
{
	NP = nearp;
	FP = farp;
	int w, h, ar;
	osuGetFramebufferSize(&w, &h);
	ar = w / h;
	double pi = 3.1415926535;
	double angle = (pi / 180.) * fovy;
	/*double l, r, t, b, pi = 3.1415926535;
	
	t = nearp *  tan((pi / 180.) * (fovy / 2.));
	b = -t;
	r = t * ar;
	l = -r;*/
	printf("t %8.2f b%8.2f a %8.2f\n",angle,nearp,farp);
	persProj.SetPerspective(angle,nearp,farp);
	printf("Perspective Mat set\n");
	persProj.Print();
	PROJECTION = TRUE;
	ORTHO = FALSE;
}

//Specify the RGB of all subsequent vertices that will be drawn
void osuColor3f(double red, double green, double blue)
{
	//Convert float numbers to a r-g-b that can be written to a pixel
	tDraw.currRed = red * 255;
	tDraw.currGreen = green * 255;
	tDraw.currBlue = blue * 255;

}

//Specify x/y position in screen space of a vertex. Add it to image->values
void osuVertex2f(double x, double y)
{

	int w, h;
	osuGetFramebufferSize(&w, &h);
	//convert the 0 -> 1 coordinates into pixel coordinates.
	x *= w;
	y *= h;

	//If we haven't initialized our first vertex yet...do so
	if (tDraw.one.initialized == 0)
	{
		tDraw.one.initialized = 1;
		tDraw.one.myX = x;
		tDraw.minX = x;
		tDraw.maxX = x;
		tDraw.one.myY = y;
		tDraw.minY = y;
		tDraw.maxY = y;
		tDraw.one.red = tDraw.currRed;
		tDraw.one.green = tDraw.currGreen;
		tDraw.one.blue = tDraw.currBlue;
	}
	//If we haven't initialized our second vertex yet...do so

	else if (tDraw.two.initialized == 0)
	{

		tDraw.two.initialized = 1;
		tDraw.two.myX = x;
		tDraw.two.myY = y;
		tDraw.two.red = tDraw.currRed;
		tDraw.two.green = tDraw.currGreen;
		tDraw.two.blue = tDraw.currBlue;

		//Make sure our mins and maxes are current with this new vertex
		if (tDraw.minX > tDraw.two.myX)
			tDraw.minX = tDraw.two.myX;
		if (tDraw.maxX < tDraw.two.myX)
			tDraw.maxX = tDraw.two.myX;
		if (tDraw.minY > tDraw.two.myY)
			tDraw.minY = tDraw.two.myY;
		if (tDraw.maxY < tDraw.two.myY)
			tDraw.maxY = tDraw.two.myY;

	}
	//If we've initialized all of the other vertexes...do this one
	else if (tDraw.three.initialized == 0)
	{
		tDraw.three.initialized = 1;
		tDraw.three.myX = x;
		tDraw.three.myY = y;
		tDraw.three.red = tDraw.currRed;
		tDraw.three.green = tDraw.currGreen;
		tDraw.three.blue = tDraw.currBlue;

		//Make sure our mins and maxes are current with this new vertex
		if (tDraw.minX > tDraw.three.myX)
			tDraw.minX = tDraw.three.myX;
		if (tDraw.maxX < tDraw.three.myX)
			tDraw.maxX = tDraw.three.myX;
		if (tDraw.minY > tDraw.three.myY)
			tDraw.minY = tDraw.three.myY;
		if (tDraw.maxY < tDraw.three.myY)
			tDraw.maxY = tDraw.three.myY;


	}

}
//All vertices of the polygon have been given so draw it and write them to the framebuffer. 
void osuEnd()
{
	printf("Drawing is over?\n"); \
	lDraw = {};
	//We're drawing lines now, not triangles.

	/*Vec3 myN, myNQ, myNR, myNS;
	int myRed, myGreen, myBlue;
	float p1, p2, p3;
	float aC, bC, cC, pC;
	float a, b, c, p;
	float area, areaOne, areaTwo, areaThree;

	//Vectors of our triangle sides
	Vec3 one = Vec3(tDraw.one.myX, tDraw.one.myY, 0.);
	Vec3 two = Vec3(tDraw.two.myX, tDraw.two.myY, 0.);
	Vec3 three = Vec3(tDraw.three.myX, tDraw.three.myY, 0.);

	//Computing the Area of the entire triangle that we're drawing. 
	aC = (two - three).Length();
	bC = (one - two).Length();
	cC = (three - one).Length();
	pC = (aC + bC + cC) / 2.;
	area = sqrt(pC*(pC - aC)*(pC - bC)*(pC - cC));

	Vec3 currPos = Vec3(0., 0., 0.);
	//Loop through this triangles minimum/maximum width
	for (int i = (tDraw.minX); i < tDraw.maxX + 1; i++)
	{
		//Loop through it's minumum/maximum heigth.b
		for (int j = (tDraw.minY); j < (tDraw.maxY + 1); j++)
		{
			//Three dimensional point inside a triangle implmentation:
			//http://web.engr.oregonstate.edu/~mjb/cs491/Handouts/vectors.1pp.pdf
			//Initialize our point within this space
			currPos = Vec3(i, j, 0.);
			//Get the Normal vector of the triangle
			myN = (three - two).Cross(one - two);
			myNQ = (three - two).Cross(currPos - two);
			myNR = (one - three).Cross(currPos - three);
			myNS = (two - one).Cross(currPos - one);
			//do my cross products conclude that the points inside my triangle?			
			if ((myN.Dot(myNQ) > 0) && (myN.Dot(myNR) >= 0) && (myN.Dot(myNS) > 0))
			{
				//Interpolation--------------------------------	
				//First subtriangle area....
				a = (currPos - three).Length();
				b = (one - currPos).Length();
				c = (three - one).Length();
				p = (a + b + c) / 2.;
				areaOne = sqrt(p*(p - a)*(p - b)*(p - c));
				//Second subtriangle area.....
				a = (currPos - two).Length();
				b = (three - currPos).Length();
				c = ((two - three).Length());
				p = (a + b + c) / 2.;
				areaTwo = sqrt((p*(p - a)*(p - b)*(p - c)));
				//Third subtriangle area.....
				a = (currPos - two).Length();
				b = (one - currPos).Length();
				c = ((two - one).Length());
				p = (a + b + c) / 2.;
				areaThree = sqrt(p*(p - a)*(p - b)*(p - c));
				//Now Convert our areas to a proportional amount of the triangle
				p1 = areaTwo / area;
				p2 = areaOne / area;
				p3 = areaThree / area;
				//Apply these proportions to the individual pixel color..
				myRed = ((p1 * tDraw.one.red) + (p2 * tDraw.two.red) + (p3 * tDraw.three.red));
				myGreen = ((p1 * tDraw.one.green) + (p2 * tDraw.two.green) + (p3 * tDraw.three.green));
				myBlue = ((p1 * tDraw.one.blue) + (p2 * tDraw.two.blue) + (p3 * tDraw.three.blue));
				// End of interpolation ---------------------------------------------------------------
				//Write to our beloved pixel. 
				osuWritePixel(i, j, myRed, myGreen, myBlue);
			}
		}
	}*/
	
}



void osuVertex3f(double x, double y, double z)
{
	if (lDraw.one.intialized == 0)
	{
		lDraw.one.intialized = 1;
		lDraw.one.pos = Vec3((float)x,(float)y,(float)z);
	}
	else if (lDraw.two.intialized == 0)
	{
		int w, h;
		osuGetFramebufferSize(&w, &h);
		lDraw.two.intialized = 1;
		lDraw.two.pos = Vec3((float)x,(float)y,(float)z);
		Vec3 p1, p2;
		double x0, y0, x1, y1,z0,z1;
		Mat4 ModelViewMat;
		//If we need to perform a orthographic projection
		if ((ORTHO == TRUE) && (PROJECTION == FALSE))
		{
			ModelViewMat = myView * Current_Transform;
			
			p1 =orthoProj * ModelViewMat * lDraw.one.pos;
			p2 =orthoProj * ModelViewMat * lDraw.two.pos;

			x0 = (double)p1.x * w, y0 = (double)p1.y * h, z0 = (double)abs(p1.z * (FP-NP));
			x1 = (double)p2.x * w, y1 = (double)p2.y * h, z1 = (double)abs(p2.z * (FP - NP));

			/*if (near_far_clip(NP, FP, &x0, &y0, &z0, &x1, &y1, &z1) != 0)
			{
				draw_line(x0 , y0 , x1 , y1 );
			}*/
			draw_line(x0, y0, x1, y1);
			//x0 = p1.x ; y0 = p1.y; x1 = p2.x; y1 = p2.y;

		
		}
		//We need to perform a perspective projection
		else if ((PROJECTION == TRUE) && (ORTHO == FALSE))
		{
			Current_Transform.Print();
			ModelViewMat = myView * Current_Transform;


			p1 = persProj *ModelViewMat * lDraw.one.pos;
			p2 = persProj *ModelViewMat * lDraw.two.pos;

			x0 = (double)p1.x, y0 = (double)p1.y, z0 = (double)p1.z;
			x1 = (double)p2.x, y1 = (double)p2.y, z1 = (double)p2.z; 
			printf("Clipping line %8.2f %8.2f %8.2f %8.2f %8.2f %8.2f\n",x0,y0,z0,x1,y1,z1);

			if (near_far_clip(NP, FP, &x0, &y0, &z0, &x1, &y1, &z1) != 0)
			{
				printf("Drawing line %8.2f %8.2f\n", x0,x1);
				draw_line(x0, y0, x1, y1);
			}
		}
		//Something got messed up.
		else
			printf("Neither a project or Orthographic was given, or BOTH we're given concurrently.\n");
	}
	
}

void osuInitialize() 
{ 
	//Create an identity matrix and push it on the stack
	Mat4 transformMat = Mat4();
	Current_Transform = transformMat;
	transformMat.SetIdentity();
	printf("Pushing identity Matrix onto the matStack.\n");
	matStack.push(transformMat);

}


void osuPushMatrix() 
{ 
	Mat4 newTop = Mat4(matStack.front());
	Current_Transform = newTop;
	matStack.push(Current_Transform);
}

void osuPopMatrix() 
{ 
	if (matStack.size() > 1)
	{   //Ok you can do it.
		matStack.pop();
		Current_Transform = matStack.front();
	}
	else
	{
		printf("Pop: Can't perform action on Identity Matrix.\n");
	}
}

void osuLoadIdentityMatrix()
{
	//Set the current Transform to the identity matrix
	Current_Transform.SetIdentity();
}
void osuTranslate(double tx, double ty, double tz) 
{ 
	Mat4 t = Mat4();
	t.SetTranslate(tx, ty, tz);
	Current_Transform = Current_Transform * t;
}

void osuScale(double sx, double sy, double sz) 
{ 
	Mat4 s = Mat4();
	s.SetScale(sx, sy, sz);
	Current_Transform = Current_Transform * s;
}

void osuRotate(double angle, double ax, double ay, double az) { 
	

	Mat4 t, r;
	if (ax > 0.)
	{
		r.SetRotateX(angle);
		Current_Transform = Current_Transform * r;
	}
	if (ay > 0.)
	{
		r.SetRotateX(angle);
		Current_Transform = Current_Transform * r;
	}
	if (az > 0.)
	{
		r.SetRotateZ(angle);
		Current_Transform = Current_Transform * r;
	}
	/*t.SetTranslate(-ax, -ay, -az);
	Current_Transform = Current_Transform * t;
		//Rotate by x
		r.SetRotateX(angle);
		Current_Transform = Current_Transform * r;
		//Rotate by Y
		r.SetRotateY(angle);
		Current_Transform = Current_Transform * r;
		//Rotate by Z
		r.SetRotateZ(angle);
		Current_Transform = Current_Transform * r;
		//Undo Y rotation
		r.SetRotateY(-angle);
		Current_Transform = Current_Transform * r;
		//Undo X rotation
		r.SetRotateX(-angle);
		Current_Transform = Current_Transform * r;
		//Untranslate...
	t.SetTranslate(ax, ay, az);
	Current_Transform = Current_Transform * t;*/
		
}

void osuLookat(double from[3], double at[3], double up[3])
{
	//From = vector specifying direction from which the viewer would like to view the scene.
	//myView.SetTranslate(-from[0], -from[1], -from[2]);
	Vec3 fVec, aVec, uVec,u,v,n;
	
	fVec = Vec3(from[0], from[1], from[2]);
	uVec = Vec3(up[0], up[1], up[2]);
	aVec = Vec3(at[0], at[1], at[2]);;
	n = aVec.Unit();
	u = uVec.Unit();
	u = u.Cross(n);
	v = n.Cross(u);
	

	Mat4 ViewTranslation, ViewRotation;
	ViewTranslation.SetTranslate(-fVec.x, -fVec.y, -fVec.z);
	ViewRotation.SetCamera(u,v,n,fVec);
	printf("R");
	ViewRotation.Print();
	printf("T\n");
	ViewTranslation.Print();
	myView = ViewRotation * ViewTranslation; 
	myView.Print();
	//t.SetTranslate(-fVec.x, -fVec.y, -fVec.z);
}

void osuBegin(OSUDrawable mode)
{
	if (mode == OSU_TRIANGLE)
	{
		//We're going to draw a triangle, so intialize our data structure to hold it
		tDraw = {};
		//Also make sure to set a default color, incase the user forgets to give you one. 
		osuColor3f(1.0, 1.0, 1.0);

	}
	else if (mode == OSU_LINES)
	{
		printf("Time for vertexes\n");

		lDraw = {};
		double f[3] = {0.,0.0,-1.}, a[3] = {0,0,0. }, myUp[3] = { 0.,1.,0. };
		//double f[3] = {50.,0.,0.}, a[3] = {-20,-50,5.0 }, myUp[3] = { 0.,5.,0. };
		
		osuLookat(f, a, myUp);

	}
}
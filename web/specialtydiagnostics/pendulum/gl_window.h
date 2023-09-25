//////////////////////////////////////////////////////////////////////
// gl_window.h: interface for the CGL_Window class.
// derived from Fl_Gl_Window class in fltk
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GL_WINDOW_H__5A69663D_E174_43C2_8F0B_1068B54B0729__INCLUDED_)
#define AFX_GL_WINDOW_H__5A69663D_E174_43C2_8F0B_1068B54B0729__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <FL/Fl_Gl_Window.H>
#include <FL/Fl.H>
#include <FL/gl.h>
#include <GL/glu.h>
#include <iostream.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_PTS 40
#define MAXFLOAT ((float)3.40282346638528860e+38) /* taken from math.h */
#define MINFLOAT (-MAXFLOAT)

/* Data structures for polygonal data, models and camera */
typedef struct
{
    float x, y, z;             /* coordinate values */
} coord;


/* This struct holds a polygon. Each point is index of a coord.  */
typedef struct
{
    int     num_points;
    int     points[MAX_PTS];
} elem;


/* this struct holds everything necessary to define and place an object */
typedef struct 
{
    float   tx, ty, tz;
    float   sx, sy, sz;
    float   rx, ry, rz;
    int     num_coords;    /* How many points       */
    coord   *the_coords;   /* The array of points   */
    int     num_elems;     /* How many polygons     */
    elem    *the_elems;    /* The array of polygons */
    coord   min_pt, max_pt; /* Corners of the bounding box  */
    coord   center_pt;      /* Center point of object       */
} myobj;

class CGL_Window : public Fl_Gl_Window {
private:
	

	int handle(int);	//handle events 
				//(overload of Fl_Gl_Window function)
	void draw();		//overload of the drawing function
protected:
	void drawPicture(void); //draw your picture here
public: 
	//camera values
	double rx,ry,rz;		
	
	//animation values
	int animate_set;

	//pendulum value
	double angle, angle1;//angle of ball
	double accel, accel1;//acceleration of ball
	double gangle,gaccel;
	double m1, m2;
	double gra;
	double len, len1;
	double amplitude;
	int num_balls;
	double time; // used for the animation
	//rk4 values
	double rk4_h;

	myobj obj;
	void load(char *file);	//load an input file
	void quit_cb(void);     	
	void camera(double value, char type);
	void pend(double value, char type);
	CGL_Window(int,int,int,int,const char *l = 0);	//constructor
	virtual ~CGL_Window();				//destructor
	void draw_obj(void);
	double bottom_accel(double xpos,double ypos,double xpos1,double ypos1);
	double top_accel(double xpos,double ypos,double xpos1,double ypos1);
	void material_set(int type);
	void light();
	void position(double xpos,double ypos);
	void position1(double xpos,double ypos,double xpos1,double ypos1);
	void animate_go();
};

#endif 

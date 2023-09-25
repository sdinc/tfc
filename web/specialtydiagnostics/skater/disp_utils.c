/******************************************************************
routines relating to drawing things with opengl and glut- jw

******************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "GL/glut.h"
#include "disp_utils.h"
#include "xforms_utils.h"
#include "maze.h"


/* graphics viewport coordinates */
#define LEFT    0.0
#define RIGHT   50.0
#define BOTTOM  0.0
#define TOP     50.0
#define NEAR   -10
#define FAR    10

#define BUFSIZE 512

/****************** globals **************************/
ObjectHndl obj[5];
int fontList, win, winr, Al=1, l1=1, l2=1, l3=1, l4=1, lL=1, obj_selected=10;
/******************animating globals*******************/
int up=0, down=1, going=0, t=-40, fall=1, ft=0, start=0;
double  accel=0, decel=0, vel=1;

/*****************lights****************************/
int yellow_lit=0, cyan_lit=0, red_lit=0,white_lit=0, object_lit=0;

char message[] = "Jason Brody-Stewart";
/********************manuvers**********************/
int moves=1, rot_move=0, top=1;
/*kick_flip*/
int k_f=1, G_flip=1, G_tip=0, G_untip=1;
/*varial*/
int varial=1, G_v=1;
/*ollie grab*/
int ollie=1, G_o=1,G_b=1, G_unb=1, fix=1, G_fix=1;
/*flip*/
int flip=1, G_mb=1, G_unmb=1;
/*spin*/
int spin=1;

/*******************globals camera*******************************/
double rx=0, ry=90, rz, tx=25, ty=25, tz, sx=1, sy=1, sz=1, ex=0, ey=0, ez=0;
/*globals for the skate board*/
double drx=0, dry=0, drz=0, dtx=0, dty=0, dtz=2; 
/*globals for the body*/
double gtx=0, gty=0, gtz=0, grx=0, gry=0, grz=0, 
       brx=0,bry=0,brz=0,btx=0,bty=0,btz=0;
/*globals for his legs*/
double lf_hipx=-170, lf_hipy=-50, lf_hipz=0, lf_knee=70,
       rt_hipx=135, rt_hipy=-40, rt_hipz=0, rt_knee=45;
/*globals for the arm*/
double  lf_shoulderx=-135, lf_shouldery=0, lf_shoulderz=0, lf_elbow=-45,
        rt_shoulderx=135, rt_shouldery=0, rt_shoulderz=0, rt_elbow=-45;
void specialKey( int key, int x, int y );
GLenum modes=GL_RENDER;

/*******************materials***********************/
GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };

GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat high_specular[] = { .9, .9, .9, 1.0 };
GLfloat low_specular[] = { .1, .1, .1, 1.0 };

GLfloat no_shininess[] = { 0.0 };
GLfloat low_shininess[] = { 5.0 };
GLfloat high_shininess[] = { 100.0 };

GLfloat mat_emission[] = {0.3, 0.2, 0.2, 0.0};
GLfloat yellow_emission[] = {1,1,0,0};
GLfloat cyan_emission[] = {0,1,1,0};
GLfloat red_emission[] = {1,0,0,0};
GLfloat white_emission[] = {1,1,1,0};

GLfloat mat_diffuse[] = { 0.1, 0.5, 0.8, 1.0 };
GLfloat red_diffuse[]={1.0,0.0,0.0,1.0};
GLfloat blue_diffuse[]={0.0,0.0,1.0,1.0};
GLfloat green_diffuse[]={0.0,1.0,0.0,1.0};
GLfloat yellow_diffuse[]={1,1,0.0,1.0};
GLfloat black_diffuse[]={0,0,0,1};
GLfloat white_diffuse[]={.8,.8,.8,1};
GLfloat cyan_diffuse[]={0,1,1,1};
GLfloat brown_diffuse[]={.5,.5,0,1};
GLfloat grey_diffuse[]={.5,.5,.5,1};

GLfloat AmbientOn[]={.2,.2,.2,1};
GLfloat AmbientOff[]={0,0,0,1};
GLfloat mat_ambient[] = { .2, 0.2, 0.2, 1 };
GLfloat mat_ambient_color[] = { 0.8, 0.8, 0.2, 1.0 };

GLfloat tran_diffuse[]={.1,.1,1,.4};
GLfloat t_mat[]={0,0,0,0};

GLfloat Alight_position[]={1,1,1,0.0 },
          light1_position[]={0,0,0,1.0},
          light2_position[]={10,10,10,1.0},
	  light3_position[]={40,10,10,1.0},
	  light4_position[]={80,10,10,0},
	  spot_highlight[]={100},
	  down_direction[]={0,0,-1},
	  DLeft_direction[]={0,0,1},
	  cutoff[]={45.0};
void init_globals(void)
{
  up=0; down=1; going=0; t=-40; fall=1; ft=0;
  accel=0; decel=0; vel=1;

  /*****************lights****************************/
  yellow_lit=0; cyan_lit=0; red_lit=0;white_lit=0;object_lit=0;
  
  /********************manuvers**********************/
  moves=1; rot_move=0; top=1;
   /*kick_flip*/
   k_f=1; G_flip=1; G_tip=0; G_untip=1;
  /*varial*/
  varial=1; G_v=1;
  /*ollie grab*/
  ollie=1; G_o=1; G_b=1; G_unb=1; fix=1; G_fix=1;
  /*flip*/
  flip=1; G_mb=1; G_unmb=1;
  /*spin*/
  spin=1;
  
  /**************************************************/
  drx=0; ry=90; rz; tx=25; ty=25; tz=0; sx=1; sy=1; sz=1; ex=0; ey=0; ez=0;
  
  /*globals for the skate board*/
  drx=0; dry=0; drz=0; dtx=0; dty=0; dtz=2;
  
  /*globals for the body*/
  gtx=0; gty=0; gtz=0; grx=0; gry=0; grz=0; 
 brx=0;bry=0;brz=0;btx=0;bty=0;btz=0;

/*globals for his legs*/
 lf_hipx=-170; lf_hipy=-50; lf_hipz=0; lf_knee=70;
 rt_hipx=135; rt_hipy=-40; rt_hipz=0; rt_knee=45;
/*globals for the arm*/
 lf_shoulderx=-135; lf_shouldery=0; lf_shoulderz=0; lf_elbow=-45;
        rt_shoulderx=135; rt_shouldery=0; rt_shoulderz=0; rt_elbow=-45;
}
/**********************manuvers**************************************/
int spin_him(void)
{
  if(grz<360)
    {
      grz+=30;
      return 0;
    }
  else
    grz=0;
  return 1;
}
int unmake_ball(void)
{
  if(lf_elbow<-45)
    {
      lf_shoulderx+=8;
      lf_elbow+=8;
      rt_shoulderx-=8;
      rt_elbow+=8;
      down_legs();
      bry-=30; 
      return 0;
    }
  return 1;
}
int make_ball(void)
{
  if(lf_elbow>-90)
    {
      lf_shoulderx-=8;
      lf_elbow-=8;
      rt_shoulderx+=8;
      rt_elbow-=8;
      lift_legs();
      bry-=30;
      return 0;
    }
  return 1; 
}

int unmove_board(void)
{
  if(dtx>0)
  {
    dtx-=.5;
    dtz-=.5;
    dry+=5;
    lf_shoulderx+=1;
    lf_shouldery-=8;
    return 0;
  }
  return 1;
}

int move_board(void)
{
  if(dtx<4)
    {
      dtx+=.5;
      dtz+=.5;
      dry-=5;
      lf_shoulderx-=1;
      lf_shouldery+=8;
      return 0;
    }
  return 1;
}

/*ollie grab with a twist*/
int ollie_grab(void)
{
  lf_shoulderx-=5;
  lf_shouldery-=1;
  lf_elbow+=5;
  return 0;
}

int unollie_grab(void)
{
  lf_shoulderx+=5;
  lf_shouldery+=1;
  lf_elbow-=5;
  return 0;
}

/*varial*/
int varial_reg(void)
{
  if(drz<361)
    {
      drz+=50;
      return 0;
    }
  else{
     drz=0;
    return 1;
  }
}
/*tips the board amount sent in*/
int tip_board(int amount)
{

  if(drx<amount)
    drx+=10;
  else
    return 1;
  return 0;
}
/*untips the board the amount sent in*/
int untip_board(int amount)
{
  if(drx>amount)
    drx-=10;
  else
    return 1;
  return 0;
}

/*  spins the board lengthwize */
int kick_flip(void)
{
  if(dry<361)
    { 
      dry+=40;
      return 0;
    }
  else{
    dry=0;
    return 1;
  }
}
/*picks his legs up for tricks*/
int lift_legs(void)
{ 
  lf_hipy-=10;
  rt_hipy-=10;
  lf_knee+=10;
  rt_knee+=10;
  return 0;
 
}
 
/*sets his legs down*/
int down_legs(void)
{
  lf_hipy+=10;
  rt_hipy+=10;
  lf_knee-=10;
  rt_knee-=10;
  return 0;
}
/***********************************Lighting*************************/
/*intialize the lighting*/
void init_light(void)
{  
  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);
  glClearColor (0.0, 0.0, 0.0, 0.0);
  glShadeModel (GL_SMOOTH);
  glLightModelfv( GL_LIGHT_MODEL_AMBIENT, AmbientOff );

  /*ambient light*/
  glLightModelfv( GL_LIGHT_MODEL_AMBIENT, AmbientOn );

  /* Yellow spot*/
  glLightfv(GL_LIGHT1,GL_DIFFUSE, yellow_diffuse);
  glLightfv(GL_LIGHT1,GL_SPOT_CUTOFF,cutoff);
  glLightfv(GL_LIGHT1,GL_SPOT_EXPONENT,spot_highlight);
  
  /*Cyan positoional*/
  glLightfv(GL_LIGHT2,GL_DIFFUSE, cyan_diffuse);
  glLightfv(GL_LIGHT2,GL_SPOT_EXPONENT, spot_highlight);
   
  /*Red Light*/
  glLightfv(GL_LIGHT3,GL_DIFFUSE, red_diffuse);
  glLightfv(GL_LIGHT3,GL_SPOT_DIRECTION,DLeft_direction);
  glLightfv(GL_LIGHT3,GL_SPOT_EXPONENT, spot_highlight);
 
  /*White Diretional*/
  glLightfv(GL_LIGHT4,GL_DIFFUSE,white_diffuse);
  glLightfv(GL_LIGHT4,GL_SPOT_DIRECTION,down_direction);
  glLightfv(GL_LIGHT4,GL_POSITION,light4_position); 
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT1);
  glEnable(GL_LIGHT2);
  glEnable(GL_LIGHT3);
  glEnable(GL_LIGHT4);
  glEnable(GL_DEPTH_TEST);
}

/*turns lights on and off*/
void turn_light(char light)
{
  switch(light)
    {
      /*enable ambient light*/
    case 'A':
      Al++;
      if(Al%2==0)  
	glLightModelfv( GL_LIGHT_MODEL_AMBIENT, AmbientOff );
      else
	glLightModelfv( GL_LIGHT_MODEL_AMBIENT, AmbientOn );
      glutPostRedisplay();
      break;
    case '1':
      l1++;
      if(l1%2==0)
	{
	  glDisable(GL_LIGHT1);
	  yellow_lit=1;
	}
      else{
	glEnable(GL_LIGHT1);
	yellow_lit=0;
      }
      glutPostRedisplay();
      break;
    case '2':
      l2++;
      if(l2%2==0)
	{
	  glDisable(GL_LIGHT2);
	  cyan_lit=1;
	}
      else{
	glEnable(GL_LIGHT2);
	cyan_lit=0;
      }
      glutPostRedisplay();
      break;
    case '3':
      l3++;
      if(l3%2==0)
	{
	  glDisable(GL_LIGHT3);
	  red_lit=1;
	}
      else{
	glEnable(GL_LIGHT3);
	red_lit=0;
      }
      glutPostRedisplay();
      break;
    case '4':
      l4++;
      if(l4%2==0)
	{
	  glDisable(GL_LIGHT4);
	  white_lit=1;
	}
      else{
	glEnable(GL_LIGHT4);
	white_lit=0;
      }
      glutPostRedisplay();
      break;
    case 'L':
      lL++;
      if(lL%2==0)
	object_lit=1;
      else
	object_lit=0;
      glutPostRedisplay();
      break;
    }
}

/**********************************Slider Changes***************/
/*changes how you see the world*/ 
void change_stuff(char axis, char type, double value)
{
  switch (axis)
    {
    case 'x':
      switch(type)
	{
	case 'r': rx=value; break;
	case 't': tx=value; break;
	case 's': sx=value; break;
	case 'e': ex=value; break;
	}
      break;
    case 'y':
      switch(type)
	{
	case 'r': ry=value; break;
	case 't': ty=value; break;
	case 's': sy=value; break;
	case 'e': ey=value; break;
	}
      break;
    case 'z':
      switch(type)
	{
	case 'r': rz=value; break;
	case 't': tz=value; break;
	case 's': sz=value; break;
	case 'e': ez=value; break;
	}
      break;
    case 'l': object_lit=value; break;
    case 't': 
      switch(type)
	{
	case 'v': varial=0; G_tip=0; printf("varial\n"); break;
	case 'k': k_f=0; G_tip=0; printf("kickflip\n"); break;
	case 'f': flip=0;  G_mb=0; printf("flip\n"); break;
	case '3': spin=0; break;
	case 'o': ollie=0; G_tip=0; printf("ollie grab\n");
	}
      break;
    }
}   
/***********************************************************************/
/* initialize glut and go into endless glut loop */
void glut_init(int argc, char *argv[],int winsize[2])
{
glutInit( &argc, argv );  /* init once per program */
glutInitWindowSize( winsize[0],winsize[1] ); /* graphics window */

/* double buffering and using rgb colors */
glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE);

/* name of window */
glutCreateWindow(argv[0]);
 
/* what to do to reshape the window */
glutReshapeFunc( reshape );

/* what to do with key strokes */
glutKeyboardFunc( key );

/* what to do with non-ascii keys */
glutSpecialFunc(specialKey);

/* what to do when mouse clicks */
glutMouseFunc(mouse_click);

/* what to do when mouse moves */
glutMotionFunc(mouse_move);

/* what to do when need to display */
glutDisplayFunc( displayFunc );

/* what to do while you aren't doing anything */
/* in this case, the idle function is going to go looking for
   events coming in from the xforms interface */
glutIdleFunc( xforms_gcb );
   
/* set up fonts for text */
setup_fonts();

/* this isn't required here, but to clarify, this function causes
the windows display function to be called the next iteration through
glutMainLoop().  multiple calls to glutPostRedisplay() before 
the next iteration in glutMainLoop still only cause one redisplay. */
glutPostRedisplay();
}

/*************************************************************************/
/* template for handling key events for special (non-ascii) keys. */
void specialKey( int key, int x, int y )
{
switch (key) {
 case GLUT_KEY_UP: 
         break;
 case GLUT_KEY_DOWN: 
         break;
 case GLUT_KEY_LEFT: gtx-=5; grz-=5;
         break;
 case GLUT_KEY_RIGHT: gtx+=5; grz+=5;
         break;
   }
glutPostRedisplay();
}

/*************************************************************************/
/* what to do with particular key */
void key( unsigned char key, int x, int y )
{
switch (key)
  {
  case 27: /* escape key*/
    exit(0);
    break;
  case 'H':
    printf("that was an H\n");
    message[0] = 'H';
    break;    
  case 'i': /* initializes the world*/
    init_maze();    
    break;
  case 'k': k_f=0; G_tip=0; 
    break;
  case 'v': varial=0; G_tip=0;
    break;
  case 'o': ollie=0; G_tip=0; 
    break;
  case 'f': flip=0;  G_mb=0;
    break;
  case '3': spin=0; 
    break;
    
    
  }
glutPostRedisplay();
}

/*************************************************************************/
/* reshape the window */
void reshape( int width, int height )
{
set_projection(0, 0, width, height);
}

/**************************************************************************/
/* what to do when the mouse clicks */
/* button indicates which button (GLUT_LEFT,GLUT_MIDDLE,GLUT_RIGHT), 
state is either GLUT_UP or GLUT_DOWN, and x,y are the window-relative
coordinates when the mouse went down or up. */
void mouse_click(int button, int state, int x, int y)
{
  if(state==0)
    going++;
  printf("freeze\n");
  //pickSquares(button,state,x,y); 
}

/**************************************************************************/
/* what to do when a mouse button is down and the mouse is
  moving within the window.  */
/* x,y indicate the window-relative coordinates when a mouse button
d   is down */
void mouse_move(int x, int y)
{ 
  /* printf("mouse_move() %d %d\n",x,y);*/
}

/*************************************************************************/
/* what to display. you will want to create more subroutine calls from
here to accomplish all your drawing tasks.  this is a simple place
to start.  */
void displayFunc( void )
{
  /* you can talk to the MODELVIEW or PROJECTION matrices. for camera
     and world/object things, use MODELVIEW. */
  glMatrixMode( GL_MODELVIEW );
  /* all pushes need pops! */
  glPushMatrix();
  /* starts the MODELVIEW matrix as identity */
  
  glLoadIdentity();
  
  if((going%2)==1)
    {
      gluLookAt(0,0,20,gtx,gty,gtz, grx,0,0);    
    }

  else
    gluLookAt(180+ex,ey,ez-20, 0, 0, 0, 0, 0, 1);
   
  /* make background gray */
  glClearColor(.5,.5,.5,0.0);
  
  /* frame buffer (some of many possible settings) */
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  
  if((going%2)==1)
    {  
      glTranslated(gtx,gty,gtz);
      glRotated(rx,1,0,0);
      glRotated(ry,0,1,0);
      glRotated(rz,0,0,1);
      glTranslated(-gtx,-gty,-gtz);      
    }
  else{
    set_slider(0,0,0);
    glRotated(rx=0,1,0,0);
    glRotated(ry=0,0,1,0);
    glRotated(rz=0,0,0,1);
  }
  /*draws the lights*/
  //glLightfv(GL_LIGHT1,GL_POSITION, light1_position);
  glLightfv(GL_LIGHT1,GL_SPOT_DIRECTION,down_direction);
  glLightfv(GL_LIGHT2,GL_POSITION, light2_position);
  glLightfv(GL_LIGHT3,GL_POSITION, light3_position);
  glLightfv(GL_LIGHT4,GL_POSITION, light4_position);
  if(object_lit==1)  
    draw_light();
  redraw_maze();
   /*makes him move in a half pipe*/
  /*T is like a direction to step, 
    when t is added to the guy moves foward
    when t is subtracted to the guy moves back
    when rot_move equals zero he moves rotational(in the pipe)
    when rot_move equals one he moves staight(in the air off the ramp)
    only when he is in the air can he do tricks
  */
  /* checks for freeze conditions*/
  if((going%2)==0)
    {
      /*figures out where the guys should be on the ramp or in the air*/ 
      if(fall==1)
	pos_guy();
      else
	falling();
      /*performs the tricks*/
      if(moves==0)
	tricks();
      else{
	if(home()==0)
	  fall=0;
      }  
    }
  glutPostRedisplay();
  /* done drawing */
  glPopMatrix();
  /* force previously issued OpenGL commands to begin execution */
  glFlush(); 
  glutSwapBuffers();
}

/*************************************************************************/
/* how to set the projection and window characteristics. this is now
   for an orthographic projection (i.e., without perspective) in 3D */
/* separate from the reshape function because one might eventually want
   to change this without reshaping the window. */
void set_projection(int llx, int lly, int width, int height)
{
  /* the viewport is in integer pixels on the screen */
  glViewport( llx, lly, width, height );
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  /* define the 3D boundaries in the virtual world space that are
     mapped to the viewport.  these are GLdoubles */
 gluPerspective(60,1,1,1000); 
}

/*********************************************************************\
 * print a string to the specified roster position
\*********************************************************************/
void draw_string_at(char inMsg[], float inX, float inY)
{
  glRasterPos2f(inX, inY);
  glCallLists(strlen(inMsg), GL_BYTE, inMsg);
}
void mat_board(void)
{
  glMaterialfv(GL_FRONT, GL_AMBIENT, white_diffuse);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, blue_diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
  glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
}
void mat_wood(void)
{
  glMaterialfv(GL_FRONT, GL_AMBIENT, white_diffuse);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, brown_diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
  glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
}
void mat_metal(void)
{
  glMaterialfv(GL_FRONT, GL_AMBIENT, white_diffuse);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, grey_diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
  glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
}

void mat_tire(void)
{
  glMaterialfv(GL_FRONT, GL_AMBIENT, white_diffuse);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, black_diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
  glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
}

void mat_guy(void)
{
  glMaterialfv(GL_FRONT, GL_AMBIENT, white_diffuse);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, green_diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, low_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
  glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
}
/*draws halfPipe*/
void draw_ramp(void)
{
  int i,x,y,z,angle;
  glPushMatrix();
  /*draws the actual curved ramp*/
  mat_wood();
      for(i=0;i<181;i++)
	{
	  y=-(45.0*cos(i*3.14/180.0));
	  z=-(45.0*sin(i*3.14/180.0));
	  angle=i+-90;
	  glPushMatrix();
	  glTranslated(0,y,z);
	  glRotated(angle,1,0,0);
	  glScalef(200,5,.1);
	  glutSolidCube(1);
	  glPopMatrix();
	}
      /*draws the rails on the top of the pipe*/
      glPushMatrix();
      mat_metal();
      glTranslated(-100,44,2);
      glRotated(90,0,1,0);
      gluCylinder(gluNewQuadric(),1,1,200,10,10);
      glTranslated(0,-88,0);
      gluCylinder(gluNewQuadric(),1,1,200,10,10);
      glPopMatrix();
      /*draws the back of the ramp*/
      glPushMatrix();
      mat_wood();
      glTranslated(0,49,-17);
      glPushMatrix();
      glScalef(200,10,40);
      glutSolidCube(1);
      glPopMatrix();
      glTranslated(0,-98,0);
      glPushMatrix();
    
      glScalef(200,10,40);
      glutSolidCube(1);
      glPopMatrix();
      glPopMatrix();

  glPopMatrix();
}
/*draws skater*/
void draw_skater()
{  
  mat_guy();
  draw_guy();
  glPushMatrix();
  mat_board();
  draw_deck();
  glPopMatrix();
}

void draw_guy(void)
{ 
  //moves guy
  glTranslated(gtx,gty,gtz);
  glRotated(grx,1,0,0);
  glRotated(gry,0,1,0);
  glRotated(grz,0,0,1);
  //body
  glPushMatrix();
  glTranslated(0,5,10);
 
  glRotated(brx,1,0,0);
  glRotated(bry,0,1,0);
  glRotated(brz,0,0,1);
  glPushMatrix();
  
  glScalef(.5,1,1);
  gluCylinder(gluNewQuadric(),2,4,10,10,10);
  glPopMatrix();
  draw_lf_upper_leg();
  draw_rt_upper_leg();
  draw_lf_upper_arm();
  draw_rt_upper_arm(); 
  draw_neck();
  draw_head();
  glPopMatrix();
}
void draw_head(void)
{
  glPushMatrix();
  glTranslated(0,0,14);
  glutSolidSphere(3,10,10);
  glPopMatrix();

}
void draw_neck(void)
{
  glPushMatrix();
  glScalef(.5,1,1);
  glTranslated(0,0,10);
  gluCylinder(gluNewQuadric(),4,1,1,10,10);
  glPopMatrix();
}
void draw_lf_upper_arm(void)
{ 
  glPushMatrix();
  glTranslated(0,4,10);
  glRotated(lf_shoulderx,1,0,0);
  glRotated(lf_shouldery,0,1,0);
  glRotated(lf_shoulderz,0,0,1);

  gluCylinder(gluNewQuadric(),1,1,5,10,10);
  draw_lf_lower_arm();
  glPopMatrix();
}

void draw_lf_lower_arm(void)
{
  glPushMatrix();
  glTranslated(0,0,5);
  glRotated(lf_elbow,0,1,0);
  gluCylinder(gluNewQuadric(),1,1,5,10,10);
  glPopMatrix();
}

void draw_rt_upper_arm(void)
{
  glPushMatrix();
  glTranslated(0,-4,10);
  glRotated(rt_shoulderx,1,0,0);
  glRotated(rt_shouldery,0,1,0);
  glRotated(rt_shoulderz,0,0,1);
  gluCylinder(gluNewQuadric(),1,1,5,10,10);
  draw_rt_lower_arm();
  glPopMatrix();
}

void draw_rt_lower_arm(void)
{
  glPushMatrix();
  glTranslated(0,0,5);
  glRotated(rt_elbow,0,1,0);
  gluCylinder(gluNewQuadric(),1,1,5,10,10);
  glPopMatrix();
}
void draw_lf_upper_leg(void)
{
  glPushMatrix();
  glTranslated(0,1.5,0);
  glRotated(lf_hipx,1,0,0);
  glRotated(lf_hipy,0,1,0);
  glRotated(lf_hipz,0,0,1);
  gluCylinder(gluNewQuadric(),1,1,5,10,10);
  draw_lf_lower_leg();
  glPopMatrix();
}
void draw_lf_lower_leg(void)
{
  glPushMatrix();
  glTranslated(0,0,5);
  glRotated(lf_knee,0,1,0);
  gluCylinder(gluNewQuadric(),1,1,5,10,10);
  glPopMatrix();
}
void draw_rt_upper_leg(void)
{
  glPushMatrix(); 
  glTranslated(0,-1.5,0);
  glRotated(rt_hipx,1,0,0);
  glRotated(rt_hipy,0,1,0);
  glRotated(rt_hipz,0,0,1);
  glRotated(15,0,15,0);
  gluCylinder(gluNewQuadric(),1,1,5,10,10);
  draw_rt_lower_leg();
  glPopMatrix();
}

void draw_rt_lower_leg(void)
{
  glPushMatrix();
  glTranslated(0,0,5);
  glRotated(rt_knee,0,1,0);
  gluCylinder(gluNewQuadric(),1,1,5,10,10);
  glPopMatrix();
}

void draw_deck(void)
{
  //moves deck
  glTranslated(dtx,dty,dtz);
  glRotated(drx,1,0,0);
  glRotated(dry,0,1,0);
  glRotated(drz,0,0,1);
  //draws deck
  glPushMatrix();
  glTranslated(0,10,0);
  glRotated(90,1,0,0);
  glScalef(1,.1,1);
  gluCylinder(gluNewQuadric(),4,4,10,10,10);
  glPopMatrix();
  glPushMatrix();
  glTranslated(0,10,0);
  glRotated(-60,1,0,0);
  glScalef(1,.1,1);
  gluCylinder(gluNewQuadric(),4,4,3,10,10);
  glPopMatrix();
  glPushMatrix();
  glTranslated(0,0,0);
  glRotated(60,1,0,0);
  glScalef(1,.1,1);
  gluCylinder(gluNewQuadric(),4,4,3,10,10);
  glPopMatrix();
  glPushMatrix();
  glTranslated(-5,0,0);
  draw_truck();
  glTranslated(0,10,0);
  draw_truck();
  glPopMatrix();
}

void draw_truck(void)
{
  glPushMatrix();
  glTranslated(5,0,-2);
  glScalef(1,.3,3);
  glutSolidCone(2,.5,10,10);
  glPopMatrix();
  glPushMatrix();
  mat_tire();
  glTranslated(2,0,-2);
  glRotated(90,0,1,0);
  glScalef(1,1,2);
  glutSolidTorus(.5,1,10,10);
  glTranslated(0,0,3);
  glutSolidTorus(.5,1,10,10);
  glTranslated(0,0,-3);
  mat_metal();
  gluCylinder(gluNewQuadric(),.5,.5,3,10,10);
  glPopMatrix();
}

/*********************************************************************\
 * Procedure for drawing 
\*********************************************************************/
void draw(ObjectHndl shape)
{
  glPushMatrix();
  if(obj_selected==shape->type)
    {      
      shape->pos[0]=tx;
      shape->pos[1]=ty;
      shape->pos[2]=tz;
      shape->rot[0]=rx;
      shape->rot[1]=ry;
      shape->rot[2]=rz;
      shape->scale[0]=sx;
      shape->scale[1]=sy;
      shape->scale[2]=sz;
      glMaterialfv(GL_FRONT, GL_AMBIENT, white_diffuse);
      glMaterialfv(GL_FRONT, GL_DIFFUSE, white_diffuse);
      glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
      glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
      glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    }
  glTranslated(shape->pos[0], shape->pos[1],shape->pos[2]);
  glRotated(shape->rot[0],1,0,0);
  glRotated(shape->rot[1],0,1,0);
  glRotated(shape->rot[2],0,0,1);
  glScalef(shape->scale[0],shape->scale[1],shape->scale[2]);
  /*draws the actual object*/ 
  switch(shape->type)
    {
    case SPHERE:
      glPushName(SPHERE);
      if(SPHERE!=obj_selected)
	{
	  glMaterialfv(GL_FRONT, GL_AMBIENT, yellow_diffuse);
	  glMaterialfv(GL_FRONT, GL_DIFFUSE, yellow_diffuse);
	  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	  glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
	  glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	}
      glutSolidSphere(4,20,20);
      glPopName();
      break;
    case TORUS: 
      glPushName(TORUS);
      if(TORUS!=obj_selected)
	{
	  glMaterialfv(GL_FRONT, GL_AMBIENT, tran_diffuse);
	  glMaterialfv(GL_FRONT, GL_DIFFUSE, tran_diffuse);
	  glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
	  glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
	  glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	}
      glutSolidTorus(1,3,10,10);
      glPopName();
      break;
    case CUBE:
      glPushName(CUBE);
      if(CUBE!=obj_selected)
	{
	  glMaterialfv(GL_FRONT, GL_AMBIENT, red_diffuse);
	  glMaterialfv(GL_FRONT, GL_DIFFUSE, red_diffuse);
	  glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
	  glMaterialfv(GL_FRONT, GL_SHININESS, no_mat);
	  glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	}
      glutSolidCube(4);
      glPopName();
      break;
    case CONE:
      glPushName(CONE);
      if(CONE!=obj_selected)
	{
	  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_diffuse);
	  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	  glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
	  glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	}
      glutSolidCone(2,4,10,10); 
      glPopName();
      break; 
    case TEAPOT:
      glPushName(TEAPOT);
      if(TEAPOT!=obj_selected)
	{
	  glMaterialfv(GL_FRONT, GL_AMBIENT, green_diffuse);
	  glMaterialfv(GL_FRONT, GL_DIFFUSE, green_diffuse);
	  glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
	  glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
	  glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	}
      glutSolidTeapot(3); 
      glPopName();
      break;
    }
 
  glPopMatrix();
}
/* draws the lights so you know where they are. */
  
void draw_light(void)
{ 
  glPushMatrix();
  glColor3f(1.0,1.0,1.0);
  /*yellow light */
  
  if(yellow_lit==0)
    {
      glMaterialfv(GL_FRONT&GL_BACK, GL_EMISSION, yellow_emission);
      glMaterialfv(GL_FRONT, GL_AMBIENT, white_diffuse);
      glPushMatrix();
      glTranslated(light1_position[0], light1_position[1], light1_position[2]);
      glutWireSphere(1,10,10);
      glPopMatrix();
    }
  
  /*cyan light */
  if(cyan_lit==0)
    {
      glMaterialfv(GL_FRONT&GL_BACK, GL_EMISSION, cyan_emission);
      glMaterialfv(GL_FRONT, GL_AMBIENT, white_diffuse);
      glPushMatrix();
      glTranslated(light2_position[0], light2_position[1], light2_position[2]);
      glutWireSphere(1,10,10);
      glPopMatrix();
    }
  /*red light */
  if(red_lit==0)
    {
      glMaterialfv(GL_FRONT&GL_BACK, GL_EMISSION, red_emission);
      glMaterialfv(GL_FRONT, GL_AMBIENT, white_diffuse);
      glPushMatrix();
      glTranslated(light3_position[0], light3_position[1], light3_position[2]);
      glutWireSphere(1,10,10);
      glPopMatrix();
    }
  /*white directional*/
  if(white_lit==0)
    {
      glMaterialfv(GL_FRONT&GL_BACK, GL_EMISSION, white_emission);
      glMaterialfv(GL_FRONT, GL_AMBIENT, white_diffuse);
      glPushMatrix();
      glTranslated(light4_position[0], 
		   light4_position[1], 
		   light4_position[2]);
      glutWireSphere(1,10,10);
      glPopMatrix();
    }
  glPopMatrix();  
}

/*********************************************************************\
 * Procedure for drawing rectangle                 
\*********************************************************************/
void draw_pt(double x, double y, double z)
{
  glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, white_diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
  glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
  glPointSize(10);
  glBegin(GL_POINTS);
  glVertex3f(x,y,z);
  glEnd();
}

void draw_rectangle(double p1x, double p1y, double p1z, 
                    double p2x, double p2y, double p2z) 
{
  glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, white_diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
  glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
  glBegin(GL_QUADS);
  glVertex3f(p1x, p1y, p1z );
  glVertex3f(p2x, p1y, p2z );
  glVertex3f(p2x, p2y, p2z );
  glVertex3f(p1x, p2y, p1z );
  
  glEnd();
}

/*********************************************************************\
 * Procedure for drawing line                 
\*********************************************************************/
void draw_line(double p1x, double p1y, double p1z, 
                    double p2x, double p2y, double p2z)
{
  //printf("[%lf,%lf,%lf],[%lf,%lf,%lf,]\n", p1x,p1y,p1z,p2x,p2y,p2z);
  glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, black_diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
  glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
  //glNormal3i(0,0,1);
  
  glBegin(GL_LINES);
  glVertex3f(p1x, p1y, p1z);
  glVertex3f(p2x, p2y, p2z);
  glEnd();
}

/*********************************************************************\
 * Procedure for drawing midpoint of integer pixel               
\*********************************************************************/
void draw_midpt(float x, float y)
{
  glBegin(GL_POINTS);
  glVertex3f(x+0.5, y+0.5, 0.0);
  glEnd();
}

/*********************************************************************\
 * Procedure for setting the color            
\*********************************************************************/
void set_color(float r, float g, float b)
{
  glColor3f(r,g,b);
}

/*++++++++++++++
 * 	these next functions are specific to GLUT 
 *++++++++++++++*/

void setup_fonts(void)
{
	int i;	
	fontList = glGenLists(128);
	for (i = 0; i < 128; i++)
	{
		glNewList(fontList + i, GL_COMPILE);
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, i);
		glEndList();
	}
	glListBase(fontList);
}


/***************************************************************************/

void pos_guy(void)
{
  /*lauching off the ramp*/
  if(t>=180 && t<=220)
    { 
      /*at the top of launch changing the direction*/
      if(t>220)
	{ 
	  down=0;
	  up=1;
	}
      rot_move=1;
      moves=0;
      /*moves him in liner motion*/
      gtz=t-180;	
    }
  /*lauching off the ramp*/
  if(t<=0 && t>=-40)
    {
      /*at the top of launch changing the direction*/
      if(t<-40)
	{
	  up=0;
	  down=1;
	}
      rot_move=1;
      moves=0;
      /*moves him in liner motion*/
      gtz=-t;
    }
  /*changing the direction of motion*/
  if(t==180 || t==220)
    {
      if(up==0)
	top=1;
      else
	top=0;
    }
  if(t==-40 || t==0)
    {
      if(down==0)
	top=0;
      else
	top=1;
    }
  /*when guy on the ramp*/
  if(t>0 && t<180)
    {
      rot_move=0;
      moves=1;
    }
  
  if(t>90)
    {
      if(down==0)
	accel+=vel;
      if(up==0)
	accel-=vel;
    }
  if(t<90)
    {
      if(up==0)
	accel+=vel;
      if(down==0)
	accel-=vel;
    }
  t+=(accel);
  /*moves him in a circular motion*/
  if(rot_move==0)
    {
      gty=-(40*cos(t*3.14/180));
      gtz=-(40*sin(t*3.14/180));
      grx=t-90;
    }
 
}

void tricks(void)
{
  if(k_f==0)
    {
      if(G_tip==0)
	{ 
	  G_tip=tip_board(30);  
	  /*bend legs*/
	  lift_legs();
	  if(G_tip==1)
	    G_flip=0;
	}
      else
	{
	  if(G_flip==0)
	    { 
	      G_flip=kick_flip();
	      if(G_flip==1)
		G_untip=0;
	    }
	  if(G_untip==0)
	    { 
	      G_untip=untip_board(0);
	      down_legs();
	      if(G_untip==1)
		{
		  k_f=1;
		  moves=1;
		}
	    }
	}
    }
  if(varial==0)
    {
      if(G_tip==0)
	{ 
	  G_tip=tip_board(20);  
	  lift_legs();
	  if(G_tip==1)
	    G_v=0;
	}
      else{
	if(G_v==0)
	  {
	    G_v=varial_reg();
	    if(G_v==1)
	      G_untip=0;
	  }
	else{
	  if(G_untip==0)
	    { 
	      G_untip=untip_board(0);
	      down_legs();
	      if(G_untip==1)
		{
		  varial=1;
		  moves=1;
		}
	    }
	}
      }
    }
  if(ollie==0)
    {
      if(G_tip==0)
	{ 
	  G_tip=tip_board(40);  
	  lift_legs();
	  if(G_tip==1)
	    G_untip=0;
	}
      if(G_untip==0)
	{
	  G_untip=untip_board(30);
	  down_legs();
	  dry+=20;
	  ollie_grab();
	  if(G_untip==1)
	    G_b=0;
	}
      if(G_b==0)
	{
	  G_b=move_board();
	  if(G_b==1)
	    G_unb=0;
	}
      if(G_unb==0)
	{
	  G_unb=unmove_board();
	  if(G_unb==1)
	    G_fix=0;
	}
      if(G_fix==0)
	{
	  G_fix=untip_board(20);
	  down_legs();
	  dry-=20;
	  unollie_grab();
	  if(G_fix==1)
	    {
	      fix=0;
	    }
	}
      if(fix==0)
	{
	  fix=untip_board(0);
	  down_legs();
	  if(fix==1)
	   {
	     ollie=1;
	     moves=1;
	   }
	}
      
    }
  /*flips him*/
  if(flip==0)
    {
      if(G_mb==0)
	{
	  
	  G_mb=make_ball();
	  if(G_mb==1)
	    G_unmb=0;
	}
      if(G_unmb==0)
	{
	  G_unmb=unmake_ball();
	  if(G_unmb==1)
	    {
	      flip=1;
	      bry=0;
	      moves=1;
	    }
	}
    }
  
  if(spin==0)
    {
      spin=spin_him();
      if(spin==1)
	moves=1;
    }
}

/*checks to see if the guy is going to continue or start to fall*/
/* if the board rotation is not 0
   if the guy rotation is not 0
*/
int home(void)
{
  /*checks to see if the board is at the right rotaion*/
  if(drx!=0 || dry!=0 || drz!=0 )
    return 0;
  /*checks if he finished the 360*/
  if(grz!=0)
    return 0;
  /*check to see if he finshed his flip*/
  if(bry!=0)
    return 0;
  return 1;
}

/*animation sequence for the guy falling*/
int falling(void)
{
  ft++;
  /*stops guy for moving when done falling*/
  if(ft>20)
    {
      fall=1;
      ft=0;
      return 1;
    }  
  if(gtz>-40)
    {   
      if(accel<0)
	{  
	  gty-=5;
	  gtz-=5;
	  dtz+=5;
	  dty+=5;
	}
      else{
	gty+=5;
	gtz-=5;
	dtz+=5; 
	dty-=5;
      }
    }
  if(grz<90)
    grz+=5;
  return 0;
}

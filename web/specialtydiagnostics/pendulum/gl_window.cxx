// GL_Window.cxx: implementation of the CGL_Window class.
//
//////////////////////////////////////////////////////////////////////

#include "gl_window.h"
#include "gui.h"
#include "math.h"
#include <GL/glut.h>


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGL_Window::CGL_Window(int x, int y, int w, int h, const char *l)
: Fl_Gl_Window(x,y,w,h,l)
{
	animate_set=1;
	rx=ry=rz=0; 
	m1=m2=2;
	gra= 9.8;
	len=len1=10;
	time =1;
	amplitude=10;
	num_balls=2;
	obj.num_elems =0;
	rk4_h=.04;
	angle=60*(22.0/7.0)/180;
	angle1=40*(22.0/7.0)/180;
	accel=accel1=0;
}

CGL_Window::~CGL_Window()
{

}

/******************************************/
/*   Do your Gl work here		  */
/******************************************/
void CGL_Window::drawPicture(void)
{
	//currently draws 3 axes just for demonstration
	glLineWidth(2.0);

	// rotate object amount on sliders 

	// zoom
	glTranslatef(0,0,10);
	// rotate
	glRotated(rx,1,0,0);
	glRotated(ry,0,1,0);
	glRotated(rz,0,0,1);
   
	// draw axis
	/*glBegin(GL_LINES);
	 glColor3f(10.0, 0.0, 0.0);
	 glVertex3f(0.0, 0.0, 0.0);
	 glVertex3f(10.0, 0.0, 0.0);
 
	 glColor3f(0.0, 10.0, 0.0);
	 glVertex3f(0.0, 0.0, 0.0);
	 glVertex3f(0.0, 10.0, 0.0);
 
	 glColor3f(0.0, 0.0, 10.0);
	 glVertex3f (0.0, 0.0, 0.0);
	 glVertex3f(0.0, 0.0, 10.0);
	glEnd();
	*/
	// pendulm
	draw_obj();
	
}

void CGL_Window::draw()
{
	int width, height;
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	width=w(); height=h();
	glViewport(0, 0, width, height);
	gluPerspective(60, (float)width/height, 1, 360.);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0, 0, -50, 0, 0, 0, 0, -1, 0);
 
	light();
	material_set(0);

	//  clear stuff on the canvas
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();

		drawPicture();
	glPopMatrix();
}

int CGL_Window::handle(int event)
{
	static int num,x,y;
	switch(event){
	case FL_PUSH:
		num=Fl::event_button();
		x=Fl::event_x();
		y=Fl::event_y();
		//printf("pushed %d x %d y %d\n",num,x,y);
		return 1;
	case FL_DRAG:
		//... mouse moved while down event ...
		return 1;
	case FL_RELEASE:
		//... mouse up event ...
		return 1;
	case FL_FOCUS :
		return 1;
	case FL_UNFOCUS :
		//... Return 1 if you want keyboard events, 0 otherwise
		return 1;
	case FL_KEYBOARD:
		//... keypress, key is in Fl::event_key(), ascii in Fl::event_text()
		//... Return 1 if you understand/use the keyboard event, 0 otherwise...
		return 1;
	case FL_SHORTCUT:
		//... shortcut, key is in Fl::event_key(), ascii in Fl::event_text()
		//... Return 1 if you understand/use the shortcut event, 0 otherwise...
		return 1;
	default:
		// tell FLTK that I don't understand other events
		return 0;
  }
}
void CGL_Window::camera(double value, char type){
	switch(type){
	case 'x': rx=value; break;
	case 'y': ry=value; break;
	case 'z': rz=value; break;
	}
}

void CGL_Window::pend(double value, char type){
	switch(type){
	case 'g': gra=value; break;
	case 'l': len=value; break;
	case 'L': len1=value; break;
	case 'm': m1=value; break;
	case 'M': m2=value; break;
	case 'b': num_balls=(int)value; break;
	case 'h': rk4_h=value; break;
	case 'a': angle=value*((22.0/7)/180); accel=0; break;
	case 'A': angle1=value*((22.0/7)/180); accel=0;break;
	}
}
 
/*********************************************************************\
 * Call to display an_object
\*********************************************************************/
void  CGL_Window::draw_obj(void) {
	//draw frame
	material_set(1);
	/*if(angle>360)
		angle=0;
	if(angle1>360|<-360)
		angle1=0;
	*/		
	glutWireCube(30);
	glBegin(GL_LINES);
		glVertex3f(-15,-15,15);
		glVertex3f(15,-15,-15);
			
		glVertex3f(15,-15,15);
		glVertex3f(-15,-15,-15);
	glEnd();
	//angle1=angle+angle1;
	if(animate_set==0){
		if(num_balls==1)//one ball rk4
			position(angle,accel);
		else//two ball rk4
			position1(angle,accel,angle1,accel1);
		//gloabal swing which is ther average
		
		}
		
	glTranslatef(0,-15,0);
	glRotated(angle*180/3.1415927     ,0,0,1);			
	glRotated(180,1,0,0);
	glBegin(GL_LINES);
		glVertex3f(0,0,0);
		glVertex3f(0,-len,0);
	glEnd();
	glTranslatef(0,-len,0);
	glutSolidSphere(m1,26,16);
	
	if(num_balls!=1){
		  //angle1=angle+angle1 ;
		glRotated((angle1+angle)*180/3.1415927     ,0,0,1);			
		glBegin(GL_LINES);
			glVertex3f(0,0,0);
			glVertex3f(0,-len1,0);
		glEnd();
		glTranslatef(0,-len1,0);
		glutSolidSphere(m2,26,16);	
	}
	

}

void CGL_Window::position(double ang, double acc){
//	printf("\ninitial rk4 angle=%f accel=%f\n",ang,acc);	
	double k1,k2,k3,k4,j1,j2,j3,j4;
	k1=acc;
	j1=-gra/len *sin(ang);
	k2=(rk4_h/2)*j1+acc;
	j2=-gra/len*sin((rk4_h/2)*k1+ang);
	k3=(rk4_h/2)*j2+acc;
	j3=-gra/len*sin((rk4_h/2)*k2+ang);
	k4=(rk4_h*j3)+acc;
	j4=-gra/len*sin(k3*rk4_h+ang);
	
	angle= ang + (rk4_h/6)*(k1+(2*k2)+(2*k3)+k4) ;
	accel= acc + (rk4_h/6)*(j1+(2*j2)+(2*j3)+j4) ;
}

void CGL_Window::position1(double ang, double vel,double ang1,double vel1){
	printf("\ninitial rk4 angle=%f accel=%f angle1=%f accel1=%f\n",
			ang*180/3.1415927,vel,ang1*180/3.1415927,vel1);	
	double k1,k2,k3,k4,j1,j2,j3,j4,m1,m2 ,m3,m4,n1,n2,n3,n4;                 
	
	k1=vel;//velocity1
	j1=vel1;//velocity2
	n1=top_accel(ang,ang1,vel,vel1);//accel1
	m1=bottom_accel(ang,ang1,vel,vel1);//accel2
	
	k2=vel+n1*(rk4_h/2); 
	j2=vel1+m1*(rk4_h/2);
	n2 =top_accel(ang+k1*(rk4_h/2),
		          ang1+j1*(rk4_h/2),
				  vel+n1*(rk4_h/2),
				  vel1+m1*(rk4_h/2));
	m2 =bottom_accel(ang+k1*(rk4_h/2),
					ang1+j1*(rk4_h/2),
					vel+n1*(rk4_h/2),
					vel1+m1*(rk4_h/2));
	
	k3=vel+n2*(rk4_h/2);                    
	j3=vel1+m2*(rk4_h/2);                                         
	n3=top_accel(ang+k2*(rk4_h/2),
				 ang1+j2*(rk4_h/2),
				 vel+n2*(rk4_h/2),
				 vel1+m2*(rk4_h/2));
	m3=bottom_accel(ang +k2*(rk4_h/2),
					ang1+j2*(rk4_h/2),
					vel+n2*(rk4_h/2),
					vel1+m2*(rk4_h/2));
	
	k4=vel+n3*(rk4_h);
	j4=vel1+m3*(rk4_h);             

	n4=top_accel(ang+k3*(rk4_h),
				 ang1+j3*(rk4_h),
			     vel+n3*(rk4_h),
			     vel1+m3*(rk4_h));
	m4=bottom_accel(ang+k3*(rk4_h),
				    ang1+j3*(rk4_h),
					vel+n3*(rk4_h),
					vel1+m3*(rk4_h));

	angle=ang + (rk4_h/6)*(k1+(2*k2)+(2*k3)+k4);
	angle1=ang1+ (rk4_h/6)*(j1+(2*j2)+(2*j3)+j4);

	accel =vel  + (rk4_h/6)*(n1+(2*n2)+(2*n3)+n4);
	accel1=vel1 + (rk4_h/6)*(m1+(2*m2)+(2*m3)+m4);
	
  }  

double CGL_Window::top_accel(double ang,double ang1,double vel ,double vel1){
	printf(">> top args: %f, %f, %f, %f\n", ang, ang1, vel, vel1);
	
	double ret1 =-gra*(2*m1+m2)*sin(ang)-m2*gra*sin(ang-2*ang1)-2*sin(ang-ang1)*m2*(( vel1*vel1)*len1-(vel*vel)*len*cos(ang-ang1));              
	double ret2 =len*(2*m1+m2-m2*cos(2*(ang-ang1))); 
	  
	printf(">> top returns: %f, %f\n", ret1, ret2);
	return ret1/ret2;
	}

double CGL_Window::bottom_accel(double ang,double ang1,double vel ,double vel1){
 	//return( 
	double ret1=2*sin(ang-ang1)*((vel*vel)*len*(m1+m2)+gra*(m1+m2)*cos(ang)+(vel1*vel1)*len1*m2*cos(ang-ang1));              
        double ret2=len1*(2*m1+m2-m2*cos(2*(ang-ang1)));
	printf(">> bottom returns: %f, %f\n", ret1, ret2);
	return ret1/ret2;  
       }

void CGL_Window::material_set(int type){
	GLfloat matskin[] = {1.0000, 0.4900, 0.2500, 1};
	GLfloat matbone[] = {0.9608, 0.8706, 0.7020, 1};
	GLfloat nomat[]= {0,0,0,0};
	switch(type){
		case 0: // skin		  
		  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matskin);
		  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matskin);
		  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, nomat);
		  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 128.0);
		  glMaterialfv(GL_FRONT, GL_EMISSION, nomat);
		  break;

		case 1: // bone
		  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matbone);
		  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matbone);
		  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, nomat);
		  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 128.0);
		  glMaterialfv(GL_FRONT, GL_EMISSION, nomat);
		  break;	
		}

  }
void CGL_Window::light(){
	float light0ambient[] = {0.1f, 0.1f, 0.1f, 1.0};
	float light0specular[] = {2.0, 2.0, 2.0, 1.0};
	float light0diffuse[] = {0.2f, 0.2f, 0.2f, 1.0};
 	float light0position[] = {-1.5, 1.5, -3, 0}; 
	float light0direction[] = {0.0, 0.0, -1.0};
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0ambient);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light0position);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light0direction);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 180);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 2);
	glEnable(GL_LIGHT0);

}
void CGL_Window::animate_go(){
	if(animate_set==0)
		animate_set=1;
	else
		animate_set=0;

}
// memory clean up
void CGL_Window::quit_cb(void){
	exit(0);
}

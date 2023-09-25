#ifndef __disp__
#define __disp__
#include "maze.h"
#include "GL/glut.h"
/*************************************************************************/
/* function prototypes */
void init_globals(void);
int unmake_ball(void);
int make_ball(void);
int unmove_board(void);
int move_board(void);
int ollie_grab(void);
int unollie_grab(void);
int varial_reg(void);
int tip_board(int amount);
int untip_board(int amount);
int kick_flip(void);
int lift_legs(void);
int down_legs(void);

void init_light(void);
void turn_light(char light);
void change_stuff(char axis, char type, double value);
void initobj(ObjectHndl obs[]);
void glut_init(int argc,char *argv[],int winsize[2]);
void key( unsigned char key, int x, int y );
void reshape( int width, int height );
void displayFunc( void );
void mouse_click(int button, int state, int x, int y);
void mouse_move(int x, int y);
void displayFunc( void );
void set_projection(int llx, int lly, int width, int height);
void setup_fonts(void);
void draw_string_at(char inMsg[], float inX, float inY);
void mat_board(void);
void mat_wood(void);
void mat_metal(void);
void mat_tire(void);
void draw_skater();
void draw_guy(void);
void draw_head(void);
void draw_neck(void);
void draw_lf_upper_arm(void);
void draw_lf_lower_arm(void);
void draw_rt_upper_arm(void);
void draw_rt_lower_arm(void);
void draw_lf_upper_leg(void);
void draw_lf_lower_leg(void);
void draw_rt_upper_leg(void);
void draw_rt_lower_leg(void);
void draw_deck(void);
void draw_truck(void);
void draw(ObjectHndl shape);
void draw_light(void);

void draw_line(double p1x, double p1y, double p1z, 
	       double p2x, double p2y, double p2z);
void draw_pt(double x, double y, double z);
void draw_rectangle(double p1x, double p1y, double p1z, 
                    double p2x, double p2y, double p2z);
void draw_midpt(float x, float y);
void set_color(float r, float g, float b);
void pos_guy(void);
void tricks(void);
int home(void);
int falling(void);

#endif




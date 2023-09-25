/** Header file generated with fdesign on Thu Dec  5 11:58:17 2002.**/

#ifndef FD_final_h_
#define FD_final_h_

/** Callbacks, globals and object handlers **/
extern void start_skater_cb(FL_OBJECT *, long);
extern void exit_program_cb(FL_OBJECT *, long);
extern void eye_cb(FL_OBJECT *, long);
extern void Light_cb(FL_OBJECT *, long);
extern void Manuver_cb(FL_OBJECT *, long);
extern void freeze_cb(FL_OBJECT *, long);


/**** Forms and Objects ****/
typedef struct {
	FL_FORM *final;
	void *vdata;
	char *cdata;
	long  ldata;
	FL_OBJECT *xcamera;
	FL_OBJECT *ycamera;
	FL_OBJECT *zcamera;
	FL_OBJECT *frez_x;
	FL_OBJECT *frez_y;
	FL_OBJECT *frez_z;
} FD_final;

extern FD_final * create_form_final(void);

#endif /* FD_final_h_ */

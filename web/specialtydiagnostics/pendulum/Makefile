INC_DIRS = -I/usr/openwin/include -I/usr/local/glut-3.7/include -I/usr/local/include
LIB_DIRS = -L/usr/local/glut-3.7/lib/glut -L/usr/local/lib

LDLIBS = -lfltk  -lfltk_gl -lglut -lGL -lGLU -lm -lX11
CFLAGS = -g -ansi -Wall -Wno-deprecated

OBJECTS= main.o gui.o gl_window.o

all: prog4

prog4: $(OBJECTS)
	g++ $(OBJECTS) ${LIB_DIRS} ${LDLIBS} -o prog4


main.o: main.cxx gui.h
	g++ ${CFLAGS} -c main.cxx  ${INC_DIRS}

gui.o: gui.cxx gui.h
	g++ ${CFLAGS} -c gui.cxx  ${INC_DIRS}

gl_window.o: gl_window.cxx gl_window.h
	g++ ${CFLAGS} -c gl_window.cxx  ${INC_DIRS}

clean:
	-rm *.o *~ prog0 .*

clobber: clean
	-rm prog4 

clobber_all: clobber
	-rm gui.cxx
	-rm gui.h
submit:
	submit cmps161-ap.w04 prog0 * 

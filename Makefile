PROGRAM = zmijica
CC      = gcc
CFLAGS  = -g -Wall -I/usr/X11R6/include -I/usr/pkg/include
LDFLAGS = -L/usr/X11R6/lib -L/usr/pkg/lib
LDLIBS  = -lglut -lGLU -lGL -lm

$(PROGRAM):$(PROGRAM).c
	$(CC) -o $(PROGRAM) $(PROGRAM).c $(CFLAGS) $(LDFLAGS) $(LDLIBS)
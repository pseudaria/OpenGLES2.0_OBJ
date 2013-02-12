LIBDIR = -L/usr/X11R6/lib
CC = gcc
CFLAGS = $(COMPILERFLAGS)
LIBRARIES = -lX11 -lXi -lXmu -lglut -lGL -lGLU -lm

shinyjet : shinyjet.o vectormath.o
	$(CC) $(CFLAGS) -o $@ $(LIBDIR) $? $(LIBRARIES)

vectormath.o : ../../common/vectormath.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o

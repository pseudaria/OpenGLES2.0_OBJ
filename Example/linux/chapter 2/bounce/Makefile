LIBDIR = -L/usr/X11R6/lib
CC = gcc
CFLAGS = $(COMPILERFLAGS)
LIBRARIES = -lglut -lGL -lGLU -lm

bounce : bounce.o
	$(CC) $(CFLAGS) -o $@ $(LIBDIR) $? $(LIBRARIES)

clean:
	rm -f *.o

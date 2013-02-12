LIBDIR = -L/usr/X11R6/lib
CC = gcc
CFLAGS = $(COMPILERFLAGS)
LIBRARIES = -lX11 -lXi -lXmu -lglut -lGL -lGLU -lm

anisotropic : anisotropic.o loadtga.o
	$(CC) $(CFLAGS) -o $@ $(LIBDIR) $? $(LIBRARIES)

framemath.o : ../../common/framemath.c matrixmath.o
	$(CC) $(CFLAGS) -c $<

matrixmath.o : ../../common/matrixmath.c
	$(CC) $(CFLAGS) -c $<

vectormath.o : ../../common/vectormath.c
	$(CC) $(CFLAGS) -c $<

torus.o : ../../common/torus.c
	$(CC) $(CFLAGS) -c $<

sphere.o : ../../common/sphere.c
	$(CC) $(CFLAGS) -c $<

loadtga.o : ../../common/loadtga.c
	$(CC) $(CFLAGS) -c $<

writetga.o : ../../common/writetga.c
	$(CC) $(CFLAGS) -c $<

isextsupported.o : ../../common/isextsupported.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o

#INCLUDE =
LIBDIR = -L/usr/X11R6/lib
CC = gcc
CFLAGS = $(COMPILERFLAGS) #$(INCLUDE)
LIBRARIES = -lX11 -lXi -lXmu -lglut -lGL -lGLU -lm

block : block.o loadtga.o
	echo $?
	$(CC) $(CFLAGS) -o $@ $(LIBDIR) $? $(LIBRARIES)

loadtga.o : ../../common/loadtga.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o
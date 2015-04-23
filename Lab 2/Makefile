
CXXFLAGS = -g 
LDLIBS = -lGL -lglut -lGLEW -lpng -lGLU

all:	main

main:	main.o geo_sphere.o png_reader.o

main.o:	main.cpp geo_sphere.h

clean:
	rm -f *.o main

CC = cc
CFLAGS =
LD = cc
LDFLAGS = -L/usr/X11R6/lib -lglut -lGLU -lGL -lX11 -lm
PROGS = cube wcube ndcube glutshow
all: $(PROGS)

clean:
	rm -f $(PROGS) *.o *~

cube: cube.c
	$(CC) -o $@ $< $(LDFLAGS)

wcube: wcube.c
	$(CC) -o $@ $< $(LDFLAGS)

ndcube: ndcube.c
	$(CC) -o $@ $< $(LDFLAGS)

glutshow: glutshow.c
	$(CC) -o $@ $< $(LDFLAGS)

PROGRAM = main
CC      = gcc
CFLAGS  = -Wall 
LDLIBS  = -lglut -lGLU -lGL -lm

$(PROGRAM): main.o player.o street.o truck.o car.o collisions.o image.o grass.o points.o trees.o text.o
	$(CC) $(CFLAGS) -o $(PROGRAM) text.o trees.o points.o grass.o image.o collisions.o car.o truck.o player.o street.o main.o $(LDLIBS)

.PHONY: clean 

clean:
	-rm *.o $(PROGRAM) *core

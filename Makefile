PROGRAM = main
CC      = gcc
CFLAGS  = -Wall 
LDLIBS  = -lglut -lGLU -lGL -lm

$(PROGRAM): main.o igrac.o ulica.o kamion.o auto.o kolizije.o image.o trava.o poeni.o drvece.o tekst.o
	$(CC) $(CFLAGS) -o $(PROGRAM) tekst.o drvece.o poeni.o trava.o image.o kolizije.o auto.o kamion.o igrac.o ulica.o main.o $(LDLIBS)

.PHONY: clean 

clean:
	-rm *.o $(PROGRAM) *core

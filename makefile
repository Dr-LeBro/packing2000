CC = gcc
CCFLAGS = -g -Wall
OBJ = algo.o boite.o debug.o objets.o interfaceC.o interface.o
OBJ2 = Ofiles/algo.o Ofiles/boite.o Ofiles/debug.o Ofiles/objets.o Ofiles/interfaceC.o Ofiles/interface.o
PATHSRC = src/
PATHHEADER = headers/
DEPINT = Interface/
DEPGEN = Generator/
OUTO = -o Ofiles/$*.o

vpath
vpath %.h headers
vpath %.h headers/Interface 
vpath %.h headers/Generator

vpath %.c src
vpath %.c src/Interface 
vpath %.c src/Generator 

vpath %.o Ofiles

all: makedir xX_projet_Xx generator

xX_projet_Xx : main.c $(OBJ)
	$(CC) $(CCFLAGS) -o xX_projet_Xx $(PATHSRC)main.c $(OBJ2)

generator : generator.c
	$(CC) $(CCFLAGS) -o generator $(PATHSRC)$(DEPGEN)generator.c 

algo.o : algo.c algo.h boite.h objets.h interfaceC.h
	$(CC) $(CCFLAGS) -c $(PATHSRC)algo.c $(OUTO)

boite.o : boite.c boite.h
	$(CC) $(CCFLAGS) -c $(PATHSRC)boite.c $(OUTO)

objets.o : objets.c objets.h
	$(CC) $(CCFLAGS) -c $(PATHSRC)objets.c $(OUTO)

interface.o : interface.c interface.h interfaceC.h
	$(CC) $(CCFLAGS) -c $(PATHSRC)$(DEPINT)interface.c $(OUTO)

interfaceC.o : interfaceC.c interfaceC.h debug.h
	$(CC) $(CCFLAGS) -c $(PATHSRC)$(DEPINT)interfaceC.c $(OUTO)

debug.o : debug.c debug.h
	$(CC) $(CCFLAGS) -c $(PATHSRC)$(DEPINT)debug.c $(OUTO)

makedir :
	- mkdir Ofiles
clean :
	- rm xX_projet_Xx generator
	- rm -f -r Ofiles/







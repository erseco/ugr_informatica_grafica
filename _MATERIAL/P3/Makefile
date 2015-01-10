# fichero Makefile
#
# nombre del fichero ejecutable
#
TARGETS= practica3OO

# banderas para el compilador (C y C++). Se indican los directorios donde se puenden
# encontrar ficheros para incluir mediante la opcion -I
# la opcion -g sirve para permitir la depuraci�n
#
CFLAGS=    -g -DXWINDOWS -DSHM -I/usr/include -I.
CXXFLAGS=  -g -DXWINDOWS -DSHM -I/usr/include -I.

# banderas pra el enlazador
# Se indica directorios donde encontrar las funciontecas con -L. Usando -l seguido del
# nombre se indica la funcionteca que se desea enlazar.
#
LDFLAGS=  -lGLU -lGL -lglut

# definicion del compilador
#
CC = g++

# orden que sera ejecutada por defecto
#
default : $(TARGETS)

# regla de ejecucion
#
practica3 : robotSkeleton.o
	$(CC) -o $@ $(CXXFLAGS) robotSkeleton.o $(LDFLAGS)

practica3OO : OOrobotSkeleton.o Robot.o
	$(CC) -o $@ $(CXXFLAGS) OOrobotSkeleton.o Robot.o $(LDFLAGS)
	
Robot.o: Robot.cpp
	@echo Creando $@... con $^
	$(CC) $(CXXFLAGS) -Wall -g -ansi -I. -c Robot.cpp -o Robot.o $(LDFLAGS)
#
#
clean:
	rm -f *.o
	rm -f $(TARGETS)

#
#
redo:
	touch *.cc
	make

#
#
superclean:
	rm -f *.o
	rm *~
	rm -f $(TARGETS)

#
#
tgz:
	rm -f *.o
	rm -f *~
	rm -f *.*~
	rm -f $(TARGETS)
	tar -zcvf $(TARGETS).tgz *


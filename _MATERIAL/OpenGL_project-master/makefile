# fichero Makefile
#
# nombre del fichero ejecutable
#
TARGETS= practica4

# banderas para el compilador (C y C++). Se indican los directorios donde se puenden
# encontrar ficheros para incluir mediante la opcion -I
# la opcion -g sirve para permitir la depuración
#
CFLAGS=    -g -DXWINDOWS -DSHM -I/usr/include -I.
CXXFLAGS=  -g -DXWINDOWS -DSHM -I/usr/include -I.

# banderas pra el enlazador
# Se indica directorios donde encontrar las funciontecas con -L. Usando -l seguido del
# nombre se indica la funcionteca que se desea enlazar.
#
# LDFLAGS=  -lGLU -lGL -lglut -ljpeg

# banderas para el enlazador
# Se indica directorios donde encontrar las funciontecas con -L. Usando -l seguido del
# nombre se indica la funcionteca que se desea enlazar.
OS := $(shell uname)
ifeq ($(OS),Darwin) #flags para MAC OS X
LDFLAGS=  -framework OpenGL -framework GLUT -L/usr/local/Cellar/jpeg/8d/lib
else  #flags para linux
LDFLAGS=  -lGLU -lGL -lglut -ljpeg
endif

# definicion del compilador
#
CC = g++

# orden que sera ejecutada por defecto
#
default : $(TARGETS)

# regla de ejecucion
#
$(TARGETS) :
	$(CC) -o $@ $(CXXFLAGS) practica.cc user_code.cc file_ply_stl.cc jpg_imagen.cpp jpg_memsrc.cpp jpg_readwrite.cpp $(LDFLAGS)

#	$(CC) -o $@ $(SRC)/$@.cc $(CXXFLAGS) $(SRC)/file_ply_stl.cc $(SRC)/model.cpp $(SRC)/model_revolution.cpp $(SRC)/model_lanzadera.cpp $(SRC)/model_robot.cpp $(SRC)/model_ply.cpp $(SRC)/model_cube.cpp $(SRC)/model_pyramid.cpp $(LDFLAGS)


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
	rm *~
	rm -f $(TARGETS)
	tar -zcvf $(TARGETS).tgz *


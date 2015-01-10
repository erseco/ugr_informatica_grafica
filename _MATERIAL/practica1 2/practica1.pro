HEADERS = \
  user_code.h
  
SOURCES = \
  user_code.cc \
  practica1.cc

LIBS += -L/casa/dmartin/codigo/funciontecas/freeglut/lib \
    -lglut

CONFIG += console
QT += opengl


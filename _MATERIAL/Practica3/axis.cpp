/* 
 * File:   axis.cpp
 * Author: jesus
 * 
 * Created on 19 de octubre de 2014, 15:49
 */

#include "axis.h"

axis::axis() {
    AXIS_SIZE = 5000;
}

axis::axis(int s) {
    AXIS_SIZE = s;
}

axis::axis(const axis& orig) {
    
}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************
void axis::draw_axis() {
    glBegin(GL_LINES);
    // eje X, color rojo
    glColor3f(1, 0, 0);
    glVertex3f(-AXIS_SIZE, 0, 0);
    glVertex3f(AXIS_SIZE, 0, 0);
    // eje Y, color verde
    glColor3f(0, 1, 0);
    glVertex3f(0, -AXIS_SIZE, 0);
    glVertex3f(0, AXIS_SIZE, 0);
    // eje Z, color azul
    glColor3f(0, 0, 1);
    glVertex3f(0, 0, -AXIS_SIZE);
    glVertex3f(0, 0, AXIS_SIZE);
    glEnd();
}

axis::~axis() {
}


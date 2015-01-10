/* 
 * File:   robot.cpp
 * Author: jesus
 * 
 * Created on 29 de noviembre de 2014, 13:19
 */

#include "robot.h"

robot::robot() {
    posicion = 0;
}

robot::robot(const robot& orig) {
}

void robot::draw(int gla,int gra,int grl, int gll) {
    drawHead();
    drawEyes();
    drawBody();
    drawLeftArm(gla);
    drawRightArm(gra);
    drawRightLeg(grl);
    drawLeftLeg(gll);
}

void robot::drawHead() {
    glPushMatrix();
    glColor3f(0, 1, 0);
    glTranslatef(0, 1.15, 0);
    glutSolidSphere(0.4f, 20, 20);
    glPopMatrix();
    glColor3f(0, 0, 1);
    glPushMatrix();
    glTranslatef(0, 1.25, 0);
    glRotatef(-90, 1.0f, 0.0f, 0.0f);
    glutSolidCone(0.4, 1, 20, 20);
    glPopMatrix();

}

void robot::drawEyes() {
    glPushMatrix();
    glTranslatef(-0.2, 1.1, 0.30);
    glutSolidSphere(0.05, 20, 20);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.2, 1.1, 0.30);
    glutSolidSphere(0.05, 20, 20);
    glPopMatrix();
}

void robot::drawBody() {
    glColor3f(1, 0, 0);
    glutSolidCube(1.5);
}

void robot::drawLeftArm(int grados) {
    GLUquadricObj * t = gluNewQuadric();
    gluQuadricDrawStyle(t, GLU_FILL);
    glPushMatrix();
    glColor3f(1, 1, 0);
    glTranslatef(-1, 0.75, 0);
   // glRotatef(grados, 1, 0, 0);
    glRotatef(90, 1, 0, 0);
    gluCylinder(t, 0.2, 0.2, 0.5, 10, 10);
    glPopMatrix();
    glPushMatrix();
    glColor3f(1, 1, 0);
    glTranslatef(-1, 0.24, 0);
    glRotatef(grados, 1, 0, 0);
    gluCylinder(t, 0.2, 0.2, 0.5, 10, 10);
    glPopMatrix();
}

void robot::drawRightArm(int grados) {
    GLUquadricObj * t = gluNewQuadric();
    gluQuadricDrawStyle(t, GLU_FILL);
    glPushMatrix();
    glColor3f(1, 1, 0);
    glTranslatef(1, 0.75, 0);
//    glRotatef(grados, 1, 0, 0);
    glRotatef(90, 1, 0, 0);
    gluCylinder(t, 0.2, 0.2, 0.5, 10, 10);
    glPopMatrix();
    glPushMatrix();
    glColor3f(1, 1, 0);
    glTranslatef(1, 0.24, 0);
    glRotatef(grados, 1, 0, 0);
    gluCylinder(t, 0.2, 0.2, 0.5, 10, 10);
    glPopMatrix();
}

void robot::drawRightLeg(int grados) {
    GLUquadricObj * t = gluNewQuadric();
    gluQuadricDrawStyle(t, GLU_FILL);
    glPushMatrix();
    glColor3f(1, 1, 0);
    glTranslatef(-0.5, -0.75, 0);
//    glRotatef(grados, 1, 0, 0);
    glRotatef(90, 1, 0, 0);
    gluCylinder(t, 0.2, 0.2, 1, 10, 10);
    glPopMatrix();
    glPushMatrix();
    glColor3f(1, 0, 1);
    glTranslatef(-0.5, -1.76, 0);
    glRotatef(grados, 1, 0, 0);
    gluCylinder(t, 0.2, 0.2, 1, 10, 10);
    glPopMatrix();
}

void robot::drawLeftLeg(int grados) {
    GLUquadricObj * t = gluNewQuadric();
    gluQuadricDrawStyle(t, GLU_FILL);
    glPushMatrix();
    glColor3f(1, 1, 0);
    glTranslatef(0.5, -0.75, 0);
//    glRotatef(grados, 1, 0, 0);
    glRotatef(90, 1, 0, 0);
    gluCylinder(t, 0.2, 0.2, 1, 10, 10);
    glPopMatrix();
    glPushMatrix();
    glColor3f(1, 0, 1);
    glTranslatef(0.5, -1.76, 0);
    glRotatef(grados, 1, 0, 0);
    gluCylinder(t, 0.2, 0.2, 1, 10, 10);
    glPopMatrix();
}

robot::~robot() {
}


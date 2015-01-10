/* 
 * File:   robot.h
 * Author: jesus
 *
 * Created on 29 de noviembre de 2014, 13:19
 */

#ifndef ROBOT_H
#define	ROBOT_H
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

class robot{
public:
    robot();
    robot(const robot& orig);
    void draw(int gla,int gra,int grl, int gll);
    void drawHead();
    void drawEyes();
    void drawBody();
    void drawRightArm(int grados);
    void drawLeftArm(int grados);
    void drawRightLeg(int grados);
    void drawLeftLeg(int grados);
    virtual ~robot();
private:
float posicion;

};

#endif	/* ROBOT_H */


/* 
 * File:   axis.h
 * Author: jesus
 *
 * Created on 19 de octubre de 2014, 15:49
 */

#ifndef AXIS_H
#define	AXIS_H
#include <GL/gl.h>

class axis {
public:
    axis();
    axis(const axis& orig);
    axis(int s);
    void draw_axis();
    void setSize(int s);
    virtual ~axis();
private:
    int AXIS_SIZE;
};

#endif	/* AXIS_H */


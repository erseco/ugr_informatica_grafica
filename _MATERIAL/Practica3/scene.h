/* 
 * File:   scene.h
 * Author: jesus
 *
 * Created on 21 de octubre de 2014, 16:54
 */

#ifndef SCENE_H
#define	SCENE_H
#include "axis.h"
#include <GL/gl.h>
#include <GL/glut.h>
#include <ctype.h>
using namespace std;
class scene {
public:
    scene();
    scene(int UI_x,int UI_y,int UI_width,int UI_height,int m);
    scene(const scene& orig);
    void clear_window();
    void change_projection();
    void change_observer();
    void draw_scene();
    void change_window_size(int Ancho1, int Alto1);
    void normal_keys(unsigned char Tecla1, int x, int y);
    void special_keys(int Tecla1, int x, int y);
    void initialize();
    int getModo();
    int getgra();
    int getgla();
    int getgrl();
    int getgll();
    virtual ~scene();
private:
    // variables que definen la posicion de la camara en coordenadas polares
    GLfloat Observer_distance;
    GLfloat Observer_angle_x;
    GLfloat Observer_angle_y;

    // variables que controlan la ventana y la transformacion de perspectiva
    GLfloat Window_width, Window_height, Front_plane, Back_plane;
    axis ejes;
    int modo;
    int UI_window_pos_x, UI_window_pos_y, UI_window_width, UI_window_height;
    int gra,gla,grl,gll;
};

#endif	/* SCENE_H */


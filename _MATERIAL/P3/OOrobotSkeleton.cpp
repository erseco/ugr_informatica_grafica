/* Program: robotSkeleton.cpp (Chapter 10)
 *
 * Draw a Hierarchical Robot using cylinders (quadrics).
 * Traverse tree to display. Cylinders are displayed filled.
 * Keyboard interaction should enable joints to rotate.
 * Light/material properties are set.
 *
 * The user can rotate the scene by dragging the mouse with the
 * left button pressed down; translate the scene using the arrow
 * keys; and zoom in and out using the keys Home and End.
 */

#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <time.h>

#include "Robot.h"

using namespace std;

/* Variables to control the spped of rotation/translation/zoom */
#define DEGREES_PER_PIXEL	0.6f
#define UNITS_PER_PIXEL		0.1f
#define ZOOM_FACTOR		0.04f

const int AXIS_SIZE = 5000;

//Robot myRobot(1,2,1,2,1,2,1,2,1,2);
Robot myRobot;

/* Structure to define the state of the mouse */
typedef struct {
  bool leftButton;
  bool rightButton;
  int x;
  int y;
} MouseState;

MouseState mouseState = { false, false, 0, 0 };

/* Scene rotation angles to alter interactively */
float xRotate = 0, yRotate = 0;

/* Camera position and orientation -- used by gluLookAt */
GLfloat eye[] = { 0, 0, 20 };
GLfloat at[] = { 0, 0, 0 };

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void draw_axis() {
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

/*
 *  This function is called whenever the display needs
 *  to be redrawn. First called when program starts.
 */

void Display(void) {
  /* draw to the back buffer */
  glDrawBuffer(GL_BACK);

  /* clear the display */
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  //draw_axis();

  /* (Re)position the camera */
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(eye[0], eye[1], eye[2], at[0], at[1], at[2], 0, 1, 0);

  /* Rotate the scene in the x and y directions */
  glRotatef(xRotate, 0, 1, 0);
  glRotatef(yRotate, 1, 0, 0);

  myRobot.DrawRobot(0, 0, 0, myRobot.getTheta()[myRobot.LUA],
                    myRobot.getTheta()[myRobot.LLA],
                    myRobot.getTheta()[myRobot.RUA],
                    myRobot.getTheta()[myRobot.RLA],
                    myRobot.getTheta()[myRobot.LUL],
                    myRobot.getTheta()[myRobot.LLL],
                    myRobot.getTheta()[myRobot.RUL],
                    myRobot.getTheta()[myRobot.RLL]);


  /* Before returning, flush the graphics buffer
   * so all graphics appear in the window */
  glFlush();
  glutSwapBuffers();
}

/*
 * A keyboard event occurs when the user presses a key:
 * '+' should cause joint angles to increase by 5 degrees
 * (within reasonable bounds)
 * '-' should cause joint angles to decrease by 5 degrees
 */
void Keyboard(unsigned char key, int x, int y) {
  switch (key) {
    case 'q':
      myRobot.move_lua_up();
      break;
    case 'w':
      myRobot.move_lua_down();
      break;
    case 'e':
      myRobot.move_lla_up();
      break;
    case 'r':
      myRobot.move_lla_down();
      break;
    case 'a':
      myRobot.move_rua_up();
      break;
    case 's':
      myRobot.move_rua_down();
      break;
    case 'd':
      myRobot.move_rla_up();
      break;
    case 'f':
      myRobot.move_rla_down();
      break;
    case 't':
      myRobot.move_lul_up();
      break;
    case 'y':
      myRobot.move_lul_down();
      break;
    case 'u':
      myRobot.move_lll_up();
      break;
    case 'i':
      myRobot.move_lll_down();
      break;
    case 'g':
      myRobot.move_rul_up();
      break;
    case 'h':
      myRobot.move_rul_down();
      break;
    case 'j':
      myRobot.move_rll_up();
      break;
    case 'k':
      myRobot.move_rll_down();
      break;
    case 'b':
      myRobot.toggleDance();
      break;
    case 'p':
      exit(0);
  }
  glutPostRedisplay();
}

/*
 * A special keyboard event occurs when the user presses a
 * special key (arrows, F? keys). Arrows cause the scene to
 * move in the direction indicated; this is accomplished by
 * moving camera position (and maintaining the orientation).
 * HOME and END keys should cause the scene to zoom in and
 * out; this is accomplished by moving the camera along the
 * vector between the eye and the lookat point.
 */
void SpecialKey(int key, int x, int y) {
  switch (key) {
    case GLUT_KEY_LEFT:
      /* as camera moves to the right, the image moves to the left */
      eye[0] = eye[0] + UNITS_PER_PIXEL;
      at[0] = at[0] + UNITS_PER_PIXEL;
      break;
    case GLUT_KEY_RIGHT:
      eye[0] = eye[0] - UNITS_PER_PIXEL;
      at[0] = at[0] - UNITS_PER_PIXEL;
      break;
    case GLUT_KEY_UP:
      eye[1] = eye[1] - UNITS_PER_PIXEL;
      at[1] = at[1] - UNITS_PER_PIXEL;
      break;
    case GLUT_KEY_DOWN:
      eye[1] = eye[1] + UNITS_PER_PIXEL;
      at[1] = at[1] + UNITS_PER_PIXEL;
      break;
    case GLUT_KEY_END: /* zoom out */
      eye[0] = (1 + ZOOM_FACTOR) * eye[0] - at[0] * ZOOM_FACTOR;
      eye[1] = (1 + ZOOM_FACTOR) * eye[1] - at[1] * ZOOM_FACTOR;
      eye[2] = (1 + ZOOM_FACTOR) * eye[2] - at[2] * ZOOM_FACTOR;
      break;
    case GLUT_KEY_HOME: /* zoom in */
      eye[0] = (1 - ZOOM_FACTOR) * eye[0] + at[0] * ZOOM_FACTOR;
      eye[1] = (1 - ZOOM_FACTOR) * eye[1] + at[1] * ZOOM_FACTOR;
      eye[2] = (1 - ZOOM_FACTOR) * eye[2] + at[2] * ZOOM_FACTOR;
      break;
  }
  glutPostRedisplay();
}

void Mouse(int button, int state, int x, int y) {
  // update the button state
  if (button == GLUT_LEFT_BUTTON) {
    if (state == GLUT_DOWN)
      mouseState.leftButton = true;
    else
      mouseState.leftButton = false;
  }
  if (button == GLUT_RIGHT_BUTTON) {
    if (state == GLUT_DOWN)
      mouseState.rightButton = true;
    else
      mouseState.rightButton = false;
  }

  // update the mouse position, so we can track the mouse move
  mouseState.x = x;
  mouseState.y = y;
}

void MouseMove(int x, int y) {
  /* Calculate the displacement in movement */
  int xDelta = mouseState.x - x;
  int yDelta = mouseState.y - y;

  /* Commit the mouse position */
  mouseState.x = x;
  mouseState.y = y;

  /* If left button is down, rotate when mouse is moved */
  if (mouseState.leftButton) {
    xRotate -= xDelta * DEGREES_PER_PIXEL;
    yRotate -= yDelta * DEGREES_PER_PIXEL;
  }
  glutPostRedisplay();
}

/*
 *  Invokes OpenGL commands that set the lighting and
 *  material properties and then enables light 0.
 */
void EnableLighting(void) {
  /* Control material properties */
  GLfloat mat_specular[] = { 0.7, 0.0, 0.0, 1.0 };
  GLfloat mat_diffuse[] = { 0.5, 0.0, 0.0, 1.0 };
  GLfloat mat_ambient[] = { 0.5, 0.0, 0.0, 1.0 };
  GLfloat mat_shininess = { 7.0 };

  /* Control lighting properties */
  GLfloat light_ambient[] = { .5, .0, .0, 1.0 };
  GLfloat light_diffuse[] = { .5, .0, .0, 1.0 };
  GLfloat light_specular[] = { .7, .0, .0, 1.0 };
  GLfloat light_position[] = { 100.0, 80.0, 120.0, 1.0 };

  /* set up ambient, diffuse, and specular components for light 0 */
  glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);

  /* define material properties for front face of all polygons */
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
  glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);

  glEnable(GL_SMOOTH);     // enable smooth shading
  glEnable(GL_LIGHTING);   // enable lighting
  glEnable(GL_LIGHT0);     // enable light 0
}

void myInit() {
  /* Set color used when clearing the window to white */
  glClearColor(1.0, 1.0, 1.0, 1.0);

  /* Set up perspective projection */
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0f, 1.0f, 10.0f, -10.0f);

  /* Initialize the camera position */
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(eye[0], eye[1], eye[2], at[0], at[1], at[2], 0, 1, 0);

  /* Enable hidden--surface--removal */
  glEnable(GL_DEPTH_TEST);

  /* Set up the lights */
  EnableLighting();

}
void Idle(int d) {
  if (d) {
    myRobot.getTheta()[myRobot.LUA] += 3 * myRobot.getDireccion()[myRobot.LUA];
    myRobot.getTheta()[myRobot.LLA] += 3 * myRobot.getDireccion()[myRobot.LLA];
    myRobot.getTheta()[myRobot.RUA] += 3 * myRobot.getDireccion()[myRobot.RUA];
    myRobot.getTheta()[myRobot.RLA] += 3 * myRobot.getDireccion()[myRobot.RLA];
    myRobot.getTheta()[myRobot.LUL] += 3 * myRobot.getDireccion()[myRobot.LUL];
    myRobot.getTheta()[myRobot.LLL] += 3 * myRobot.getDireccion()[myRobot.LLL];
    myRobot.getTheta()[myRobot.RUL] += 3 * myRobot.getDireccion()[myRobot.RUL];
    myRobot.getTheta()[myRobot.RLL] += 3 * myRobot.getDireccion()[myRobot.RLL];
    if (myRobot.getTheta()[myRobot.LUA] > 60 || myRobot.getTheta()[myRobot.LUA] < -60)
      myRobot.getDireccion()[myRobot.LUA] *= -1;
    if (myRobot.getTheta()[myRobot.LLA] > 30 || myRobot.getTheta()[myRobot.LLA] < -30)
      myRobot.getDireccion()[myRobot.LLA] *= -1;
    if (myRobot.getTheta()[myRobot.RUA] > 60 || myRobot.getTheta()[myRobot.RUA] < -60)
      myRobot.getDireccion()[myRobot.RUA] *= -1;
    if (myRobot.getTheta()[myRobot.RLA] > 30 || myRobot.getTheta()[myRobot.RLA] < -30)
      myRobot.getDireccion()[myRobot.RLA] *= -1;
    if (myRobot.getTheta()[myRobot.LUL] > 90 || myRobot.getTheta()[myRobot.LUL] < -90)
      myRobot.getDireccion()[myRobot.LUL] *= -1;
    if (myRobot.getTheta()[myRobot.LLL] > 45 || myRobot.getTheta()[myRobot.LLL] < -45)
      myRobot.getDireccion()[myRobot.LLL] *= -1;
    if (myRobot.getTheta()[myRobot.RUL] > 90 || myRobot.getTheta()[myRobot.RUL] < -90)
      myRobot.getDireccion()[myRobot.RUL] *= -1;
    if (myRobot.getTheta()[myRobot.RLL] > 45 || myRobot.getTheta()[myRobot.RLL] < -45)
      myRobot.getDireccion()[myRobot.RLL] *= -1;
    glutPostRedisplay();
  }
  glutTimerFunc(10, Idle, myRobot.getDance());
}
int main(int argc, char **argv) {
  srand(time(NULL));
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(500, 500);
  glutCreateWindow("Hierarchical Robot");

  /* register callback functions */
  glutDisplayFunc(Display);
  glutKeyboardFunc(Keyboard);
  glutSpecialFunc(SpecialKey);
  glutMouseFunc(Mouse);
  glutMotionFunc(MouseMove);

  /* set window attributes */
  myInit();
  glutTimerFunc(10, Idle, 0);
  /* start event processing */
  glutMainLoop();
}

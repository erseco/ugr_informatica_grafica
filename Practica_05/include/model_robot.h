/******************************************************************************
 *
 * IG - Informática Gráfica
 * Grado en Ingeniería Informática
 *
 * 2014 - Ernesto Serrano <erseco@correo.ugr.es>
 * ---------------------------------------------
 *
 *  Cabeceras del codigo del modelo, funciona tanto en linux como en mac
 *
 ******************************************************************************/
#ifndef _MODEL_ROBOT_
#define _MODEL_ROBOT_

#ifdef __MACH__ // Incluimos las librerías necesarias para que funcione en OSX
  #include <GLUT/glut.h>
#else
  #include <GL/glut.h>
#endif

#include <model.h>

class Model_Robot : public Model {

 public:

  Model_Robot();
  Model_Robot(GLfloat lowerArmHeight, GLfloat lowerArmRadius, GLfloat lowerLegHeight,
        GLfloat lowerLegRadius, GLfloat torsoHeight, GLfloat torsoRadius,
        GLfloat upperArmHeight, GLfloat upperArmRadius, GLfloat upperLegHeight,
        GLfloat upperLegRadius);

  /* Enumeration of body parts */
  enum {
    TORSO = 0,
    LUA,
    LLA,
    RUA,
    RLA,
    LUL,
    LLL,
    RUL,
    RLL,
    DANCE,
    QUIT
  };

  void move_lua_up();
  void move_lua_down();
  void move_lla_up();
  void move_lla_down();
  void move_rua_up();
  void move_rua_down();
  void move_rla_up();
  void move_rla_down();
  void move_lul_up();
  void move_lul_down();
  void move_lll_up();
  void move_lll_down();
  void move_rul_up();
  void move_rul_down();
  void move_rll_up();
  void move_rll_down();

  /* Allocate quadrics with filled drawing style */
  void InitQuadrics();

  void head();
  void torso();
  void left_upper_arm();
  void left_lower_arm();
  void right_upper_arm();
  void right_lower_arm();
  void left_upper_leg();
  void left_lower_leg();
  void right_upper_leg();
  void right_lower_leg();

  void toggleDance();

  void Idle(int d);
  void genDirec();
  double randRange(double min, double max);

  const GLfloat* getCenter() const;
  short int* getDireccion();
  const GLfloat getHeadHeight() const;
  const GLfloat getHeadRadius() const;
  const GLfloat getLowerArmHeight() const;
  const GLfloat getLowerArmRadius() const;
  const GLfloat getLowerLegHeight() const;
  const GLfloat getLowerLegRadius() const;
  GLUquadricObj* getT() const;
  void setT(GLUquadricObj* t);
  const bool getDance() const;
  GLfloat* getTheta();
  const GLfloat getTorsoHeight() const;
  const GLfloat getTorsoRadius() const;
  const GLfloat getUpperArmHeight() const;
  const GLfloat getUpperArmRadius() const;
  const GLfloat getUpperLegHeight() const;
  const GLfloat getUpperLegRadius() const;

  bool isDance() const;
  void setDance(bool dance = false);
  void setTheta(int);
  void setHeadHeight(GLfloat headHeight);
  void setHeadRadius(GLfloat headRadius);
  void setLowerArmHeight(GLfloat lowerArmHeight);
  void setLowerArmRadius(GLfloat lowerArmRadius);
  void setLowerLegHeight(GLfloat lowerLegHeight);
  void setLowerLegRadius(GLfloat lowerLegRadius);
  void setTorsoHeight(GLfloat torsoHeight);
  void setTorsoRadius(GLfloat torsoRadius);
  void setUpperArmHeight(GLfloat upperArmHeight);
  void setUpperArmRadius(GLfloat upperArmRadius);
  void setUpperLegHeight(GLfloat upperLegHeight);
  void setUpperLegRadius(GLfloat upperLegRadius);

  void draw(DrawMode mode = SOLID);
  void process_key(unsigned char Tecla);

 private:

  /* Variables to control the size of the robot */
  GLfloat head_height;
  GLfloat head_radius;

  GLfloat torso_height;
  GLfloat torso_radius;

  GLfloat upper_arm_height;
  GLfloat lower_arm_height;
  GLfloat upper_arm_radius;
  GLfloat lower_arm_radius;

  GLfloat upper_leg_height;
  GLfloat lower_leg_height;
  GLfloat upper_leg_radius;
  GLfloat lower_leg_radius;

  GLUquadricObj *t, *h, /* torso and head */
  *lua, *lla, *rua, *rla, /* arms */
  *lul, *lll, *rul, *rll; /* legs */
  /*
   * lua - left upper arm
   * lla - left lower arm
   * rua - right upper arm
   * rla - right lower arm
   * lul - left upper leg
   * lll - left lower leg
   * rul - right upper leg
   * rll - right lower leg
   */

  /* initial joint angles */
  GLfloat theta[QUIT];
  short int direccion[QUIT];
  /* torso position */
  GLfloat center[3];
  /* joint angle to alter interactively */
  //static GLint angle = 0; /* initially, TORSO */
  /* Dance mode or not? */
  bool dance;

};

#endif /* ROBOT_H_ */
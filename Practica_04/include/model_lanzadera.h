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
#ifndef _MODEL_LANZADERA_
#define _MODEL_LANZADERA_

#ifdef __MACH__ // Incluimos las librerías necesarias para que funcione en OSX
  #include <GLUT/glut.h>
#else
  #include <GL/glut.h>
#endif

#include <model.h>

class Model_Lanzadera : public Model
{

public:

  Model_Lanzadera();

  void plataforma(DrawMode mode);
  void base_cohete(DrawMode mode);
  void rueda();
  void cabina();
  void cohete();

  void draw(DrawMode mode = SOLID);
  void process_key(unsigned char Tecla);

private:


  GLfloat cohete_angulo;
  GLfloat base_cohete_angulo;
  GLfloat plataforma_angulo;

  GLUquadricObj *t;


  void move_cohete_up(){cohete_angulo -= 5;};
  void move_cohete_down(){cohete_angulo += 5;};
  void move_cohete_derecha(){base_cohete_angulo += 5;};
  void move_cohete_izquierda(){base_cohete_angulo -= 5;};
  void move_plataforma_adelante(){plataforma_angulo += 0.05;};
  void move_plataforma_atras(){plataforma_angulo -= 0.05;};


};

#endif /* ROBOT_H_ */
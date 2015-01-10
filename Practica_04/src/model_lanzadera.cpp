/******************************************************************************
 *
 * IG - Informática Gráfica
 * Grado en Ingeniería Informática
 *
 * 2014 - Ernesto Serrano <erseco@correo.ugr.es>
 * ---------------------------------------------
 *
 *  Codigo del usuario
 *
 ******************************************************************************/

#include <model_lanzadera.h>



Model_Lanzadera::Model_Lanzadera() {


  setColor(0,0.5,0,1);

  t = gluNewQuadric();

  cohete_angulo = 0.0;
  base_cohete_angulo = 0.0;
  plataforma_angulo = 0.0;

}


void Model_Lanzadera::process_key(unsigned char Tecla)
{
    // Al pulsar la tecla activamos / desactivamos el pintado de las normales

  switch (Tecla)
  {
    case 'N':
      move_cohete_derecha();
      break;
    case 'n':
      move_cohete_izquierda();
      break;
    case 'M':
      move_cohete_up();
      break;
    case 'm':
      move_cohete_down();
      break;
    case 'K':
      move_plataforma_adelante();
      break;
    case 'k':
      move_plataforma_atras();
      break;

  }
}

void Model_Lanzadera::plataforma(DrawMode mode) {
  glPushMatrix();
  glScalef(0.1, 0.1, 0.1);

  glRotatef(90.0, 1.0, 0.0, 0.0);

  glScalef(4, 15, 0.5);

  if (mode == Model::POINTS || mode == Model::LINES)
    glutWireCube(1);
  else
    glutSolidCube(1);

  glPopMatrix();
}

void Model_Lanzadera::cabina() {
  glPushMatrix();

  glColor3f(0.0, 0.5, 0.0); // Verde oscuro

  glScalef(0.1, 0.1, 0.1);

  glScalef(2, 2, 3);

  // Tapas
  glRectf(-0.75f,0.75f, 0.75f, -0.75f); // Delantera

  glPushMatrix(); // Trasera

    glTranslatef(0.0, 0.0, 1.0);
    glRectf(-0.75f,0.75f, 0.75f, -0.75f);

  glPopMatrix(); // Fin Trasera
  // Fin tapas

  glRotatef(45.0, 0.0, 0.0, 1.0);
  gluCylinder(t, 1.0, 1.0, 1, 4, 1);

  glPopMatrix();
}

void Model_Lanzadera::base_cohete(DrawMode mode) {
  glPushMatrix();

  glColor3f(0.0, 0.5, 0.0); // Verde oscuro

  glScalef(0.1, 0.1, 0.1);

  if (mode == Model::POINTS || mode == Model::LINES)
    glutWireCube(1);
  else
    glutSolidCube(1);

  glPopMatrix();
}

void Model_Lanzadera::cohete() {
    glPushMatrix();

    glColor3f(0.752941, 0.752941, 0.752941); // Gris

    glScalef(0.05, 0.05, 0.05);
    glRotatef(180.0, 1.0, 0.0, 0.0);

  gluCylinder(t, 1.0, 1.0, 20, 20, 6);
  glPopMatrix();
}


void Model_Lanzadera::rueda() {

  glPushMatrix();
    glColor3f(0, 0, 0); // Negro
    glRotatef(90, 0, 1, 0);

    glScalef(0.1, 0.1, 0.1);

  // t, base, grosor, altura, lados, subdivisiones

  gluCylinder(t, 1.0, 1.0, 0.3, 100, 2);

  gluCylinder(t, 0, 1.0, 0, 100, 2);

  glPopMatrix();
}

void Model_Lanzadera::draw(DrawMode mode)
{

    switch (mode)
    {
        case Model::POINTS:
            gluQuadricDrawStyle(t, GLU_POINT);
            glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
            break;
        case Model::LINES:
            gluQuadricDrawStyle(t, GLU_LINE);
            glPolygonMode(GL_FRONT_AND_BACK,GL_LINES);
            break;
        default: // SOLID & CHESS
            gluQuadricDrawStyle(t, GLU_FILL);
            glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

            // Para probar que se pintan los triangulos correctamente
            // glPolygonMode(GL_FRONT,GL_FILL); // Los frontales los pintamos
            // glPolygonMode(GL_BACK,GL_LINE); // Los traseros solo las lineas

            break;
    }

    // Lo primero, movemos el modelo al centro establecido mediante setCenter()
    glTranslatef(x, y, z);

    glPushMatrix(); // Inicio plataforma
      glTranslatef(0.0, 0.0, plataforma_angulo);
      plataforma(mode);
      glPushMatrix(); // Rueda delantera izquierda
          glTranslatef(-0.23, 0.0, -0.5); // El 0.23 es porque hay que agregarle el ancho de la rueda
          rueda();
      glPopMatrix();
      glPushMatrix(); // Rueda trasera izquierda
          glTranslatef(-0.23, 0.0, 0.5);
          rueda();
      glPopMatrix();
      glPushMatrix(); // Rueda delantera derecha
          glTranslatef(0.2, 0.0, -0.5);
          rueda();
      glPopMatrix();
      glPushMatrix(); // Rueda trasera derecha
          glTranslatef(0.2, 0.0, 0.5);
          rueda();
      glPopMatrix();

    glPushMatrix(); // Cabina
        glTranslatef(0.0, 0.15, -0.7);
        cabina();
    glPopMatrix(); // Fin cabina

    glPushMatrix(); // Base del cohete

      glTranslatef(0.0, 0.1, 0.65);
      glRotatef(base_cohete_angulo, 0, -200, 0);
      base_cohete(mode);

      glPushMatrix(); // Cohete
          glRotatef(cohete_angulo, 1, 0, 0);
          cohete(); // Cohete
      glPopMatrix();
    glPopMatrix(); // Fin base cohete

  glPopMatrix(); // Fin plataforma


}




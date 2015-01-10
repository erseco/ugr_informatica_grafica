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

#include <model_robot.h>



Model_Robot::Model_Robot() {
  genDirec();
  InitQuadrics();
  this->dance = false;
  this->center[0] = 0;
  this->center[1] = 0;
  this->center[2] = 0;
  for (int i = 0; i < QUIT; i++)
    this->theta[i] = 0;

  head_height = 3.0;
  head_radius = 1.0;

  torso_height = 5.0;
  torso_radius = 1.0;

  upper_arm_height = 3.0;
  lower_arm_height = 2.0;
  upper_arm_radius = 0.5;
  lower_arm_radius = 0.5;

  upper_leg_height = 3.0;
  lower_leg_height = 2.0;
  upper_leg_radius = 0.5;
  lower_leg_radius = 0.5;
}

  void Model_Robot::process_key(unsigned char Tecla1)
  {

  switch (Tecla1) {
    case 'q':
      move_lua_up();
      break;
    case 'w':
      move_lua_down();
      break;
    case 'e':
      move_lla_up();
      break;
    case 'r':
      move_lla_down();
      break;
    case 'a':
      move_rua_up();
      break;
    case 's':
      move_rua_down();
      break;
    case 'd':
      move_rla_up();
      break;
    case 'f':
      move_rla_down();
      break;
    case 't':
      move_lul_up();
      break;
    case 'y':
      move_lul_down();
      break;
    case 'u':
      move_lll_up();
      break;
    case 'i':
      move_lll_down();
      break;
    case 'g':
      move_rul_up();
      break;
    case 'h':
      move_rul_down();
      break;
    case 'j':
      move_rll_up();
      break;
    case 'k':
      move_rll_down();
      break;
  }

}

/* Allocate quadrics with filled drawing style */
void Model_Robot::InitQuadrics() {
  t = gluNewQuadric();
  gluQuadricDrawStyle(t, GLU_FILL);
  lua = gluNewQuadric();
  gluQuadricDrawStyle(lua, GLU_FILL);
  h = gluNewQuadric();
  gluQuadricDrawStyle(h, GLU_FILL);
  lla = gluNewQuadric();
  gluQuadricDrawStyle(lla, GLU_FILL);
  rua = gluNewQuadric();
  gluQuadricDrawStyle(rua, GLU_FILL);
  lul = gluNewQuadric();
  gluQuadricDrawStyle(lul, GLU_FILL);
  lll = gluNewQuadric();
  gluQuadricDrawStyle(lll, GLU_FILL);
  rul = gluNewQuadric();
  gluQuadricDrawStyle(rul, GLU_FILL);
  rll = gluNewQuadric();
  gluQuadricDrawStyle(rll, GLU_FILL);
}

void Model_Robot::Model_Robot::head() {
  glPushMatrix();
  // glScalef(head_radius, head_height / 2, head_radius);
  // gluSphere(h, 1.0, 10, 10);
  glPopMatrix();
}

void Model_Robot::torso() {
  glPushMatrix();
  glRotatef(90.0, 1.0, 0.0, 0.0);
  gluCylinder(t, torso_radius, torso_radius, torso_height, 10, 10);
  glPopMatrix();
}

void Model_Robot::left_upper_arm() {
  glPushMatrix();
  glRotatef(90, 0, 1, 0);
  gluCylinder(lua, upper_arm_radius, upper_arm_radius, upper_arm_height, 10,
              10);
  glPopMatrix();
}

void Model_Robot::left_lower_arm() {
  glPushMatrix();
  glRotatef(90, 0, 1, 0);
  gluCylinder(lla, lower_arm_radius, lower_arm_radius, lower_arm_height, 10,
              10);
  glPopMatrix();
}

void Model_Robot::right_upper_arm() {
  glPushMatrix();
  glRotatef(-90, 0, 1, 0);
  gluCylinder(rua, upper_arm_radius, upper_arm_radius, upper_arm_height, 10,
              10);
  glPopMatrix();
}

void Model_Robot::right_lower_arm() {
  glPushMatrix();
  glRotatef(-90, 0, 1, 0);
  gluCylinder(lla, lower_arm_radius, lower_arm_radius, lower_arm_height, 10,
              10);
  glPopMatrix();
}

void Model_Robot::left_upper_leg() {
  glPushMatrix();
  glRotatef(90, 1, 0, 0);
  gluCylinder(lul, upper_leg_radius, upper_leg_radius, upper_leg_height, 10,
              10);
  glPopMatrix();
}

void Model_Robot::left_lower_leg() {
  glPushMatrix();
  glRotatef(90, 1, 0, 0);
  gluCylinder(lll, lower_leg_radius, lower_leg_radius, lower_leg_height, 10,
              10);
  glPopMatrix();
}

void Model_Robot::right_upper_leg() {
  glPushMatrix();
  glRotatef(90, 1, 0, 0);
  gluCylinder(rul, upper_leg_radius, upper_leg_radius, upper_leg_height, 10,
              10);
  glPopMatrix();
}

void Model_Robot::right_lower_leg() {
  glPushMatrix();
  glRotatef(90, 1, 0, 0);
  gluCylinder(rll, lower_leg_radius, lower_leg_radius, lower_leg_height, 10,
              10);
  glPopMatrix();
}

void Model_Robot::draw(Model::DrawMode mode)
{

float lua = theta[LUA];
float lla = theta[LLA];
float rua = theta[RUA];
float rla = theta[RLA];
float lul = theta[LUL];
float lll = theta[LLL];
float rul = theta[RUL];
float rll = theta[RLL];


  torso();
  glPushMatrix();
    glTranslatef(0, head_height / 2, 0);
    head();
  glPopMatrix();
  glPushMatrix();
    glTranslatef(torso_radius, 0, 0);
    glRotatef(lua, 0, 0, 1);
    left_upper_arm();
    glTranslatef(upper_arm_height, 0, 0);
    glRotatef(lla, 0, 0, 1);
    left_lower_arm();
  glPopMatrix();
  glPushMatrix();
    glTranslatef(-torso_radius, 0, 0);
    glRotatef(rua, 0, 0, 1);
    right_upper_arm();
    glTranslatef(-upper_arm_height, 0, 0);
    glRotatef(rla, 0, 0, 1);
    right_lower_arm();
  glPopMatrix();
  glPushMatrix();
    glTranslatef(torso_radius, -torso_height, 0);
    glRotatef(lul, 1, 0, 0);
    left_upper_leg();
    glTranslatef(0, -upper_leg_height, 0);
    glRotatef(lll, 1, 0, 0);
    left_lower_leg();
  glPopMatrix();
  glPushMatrix();
    glTranslatef(-torso_radius, -torso_height, 0);
    glRotatef(rul, 1, 0, 0);
    right_upper_leg();
    glTranslatef(0, -upper_leg_height, 0);
    glRotatef(rll, 1, 0, 0);
    right_lower_leg();
  glPopMatrix();
}

void Model_Robot::move_lua_up() {
  theta[LUA] += 5;
}

void Model_Robot::move_lua_down() {
  theta[LUA] -= 5;
}

void Model_Robot::move_lla_up() {
  theta[LLA] += 5;
}

void Model_Robot::move_lla_down() {
  theta[LLA] -= 5;
}

void Model_Robot::move_rua_up() {
  theta[RUA] += 5;
}

void Model_Robot::move_rua_down() {
  theta[RUA] -= 5;
}

void Model_Robot::move_rla_up() {
  theta[RLA] += 5;
}

void Model_Robot::move_rla_down() {
  theta[RLA] -= 5;
}

void Model_Robot::move_lul_up() {
  theta[LUL] += 5;
}

void Model_Robot::move_lul_down() {
  theta[LUL] -= 5;
}

void Model_Robot::move_lll_up() {
  theta[LLL] += 5;
}

void Model_Robot::move_lll_down() {
  theta[LLL] -= 5;
}

void Model_Robot::move_rul_up() {
  theta[RUL] += 5;
}

void Model_Robot::move_rul_down() {
  theta[RUL] -= 5;
}

void Model_Robot::move_rll_up() {
  theta[RLL] += 5;
}

void Model_Robot::move_rll_down() {
  theta[RLL] -= 5;
}

double Model_Robot::randRange(double min, double max) {
  return rand() * (max - min) / RAND_MAX + min;
}

/**
 * Generar direcciones aleatorias
 */
void Model_Robot::genDirec() {
  for (int i = 0; i < QUIT; i++) {
    int s = randRange(-2, 2);
    while (s == 0)
      s = randRange(-2, 2);
    this->direccion[i] = s;
  }
}

bool Model_Robot::isDance() const {
  return dance;
}

short int* Model_Robot::getDireccion() {
  return direccion;
}

const GLfloat Model_Robot::getHeadHeight() const {
  return head_height;
}

const GLfloat Model_Robot::getHeadRadius() const {
  return head_radius;
}

const GLfloat Model_Robot::getLowerArmHeight() const {
  return lower_arm_height;
}

const GLfloat Model_Robot::getLowerArmRadius() const {
  return lower_arm_radius;
}

const GLfloat Model_Robot::getLowerLegHeight() const {
  return lower_leg_height;
}

const GLfloat Model_Robot::getLowerLegRadius() const {
  return lower_leg_radius;
}

GLUquadricObj* Model_Robot::getT() const {
  return t;
}

void Model_Robot::setT(GLUquadricObj* t) {
  this->t = t;
}

GLfloat* Model_Robot::getTheta() {
  return theta;
}

const GLfloat Model_Robot::getTorsoHeight() const {
  return torso_height;
}

const GLfloat Model_Robot::getTorsoRadius() const {
  return torso_radius;
}

const GLfloat Model_Robot::getUpperArmHeight() const {
  return upper_arm_height;
}

const GLfloat Model_Robot::getUpperArmRadius() const {
  return upper_arm_radius;
}

const GLfloat Model_Robot::getUpperLegHeight() const {
  return upper_leg_height;
}

const GLfloat Model_Robot::getUpperLegRadius() const {
  return upper_leg_radius;
}

const bool Model_Robot::getDance() const {
  return this->dance;
}


void Model_Robot::toggleDance() {
  this->dance = !this->dance;
}

void Model_Robot::setHeadHeight(GLfloat headHeight) {
  head_height = headHeight;
}

void Model_Robot::setHeadRadius(GLfloat headRadius) {
  head_radius = headRadius;
}

void Model_Robot::setLowerArmHeight(GLfloat lowerArmHeight) {
  lower_arm_height = lowerArmHeight;
}

void Model_Robot::setLowerArmRadius(GLfloat lowerArmRadius) {
  lower_arm_radius = lowerArmRadius;
}

void Model_Robot::setLowerLegHeight(GLfloat lowerLegHeight) {
  lower_leg_height = lowerLegHeight;
}

void Model_Robot::setLowerLegRadius(GLfloat lowerLegRadius) {
  lower_leg_radius = lowerLegRadius;
}

void Model_Robot::setTorsoHeight(GLfloat torsoHeight) {
  torso_height = torsoHeight;
}

void Model_Robot::setTorsoRadius(GLfloat torsoRadius) {
  torso_radius = torsoRadius;
}

void Model_Robot::setUpperArmHeight(GLfloat upperArmHeight) {
  upper_arm_height = upperArmHeight;
}

void Model_Robot::setUpperArmRadius(GLfloat upperArmRadius) {
  upper_arm_radius = upperArmRadius;
}

void Model_Robot::setUpperLegHeight(GLfloat upperLegHeight) {
  upper_leg_height = upperLegHeight;
}

void Model_Robot::setUpperLegRadius(GLfloat upperLegRadius) {
  upper_leg_radius = upperLegRadius;
}


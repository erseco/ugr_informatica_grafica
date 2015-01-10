/*
 * Robot.cpp
 *
 *  Created on: Dec 10, 2013
 *      Author: Alejandro Alcalde
 */
#include "Robot.h"

Robot::Robot() {
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

Robot::Robot(GLfloat lowerArmHeight, GLfloat lowerArmRadius,
             GLfloat lowerLegHeight, GLfloat lowerLegRadius,
             GLfloat torsoHeight, GLfloat torsoRadius, GLfloat upperArmHeight,
             GLfloat upperArmRadius, GLfloat upperLegHeight,
             GLfloat upperLegRadius) {
  genDirec();
  InitQuadrics();
  this->dance = false;
  this->center[0] = 0;
  this->center[1] = 0;
  this->center[2] = 0;
  for (int i = 0; i < QUIT; i++)
    this->theta[i] = 0;

  setHeadHeight(3.0);
  setHeadRadius(1.0);
  setLowerArmHeight(lowerArmHeight);
  setLowerArmRadius(lowerArmRadius);
  setLowerLegHeight(lowerLegHeight);
  setLowerLegRadius(lowerLegRadius);
  setTorsoHeight(torsoHeight);
  setTorsoRadius(torsoRadius);
  setUpperArmHeight(upperArmHeight);
  setUpperArmRadius(upperArmRadius);
  setUpperLegHeight(upperLegHeight);
  setUpperLegRadius(upperLegRadius);
}
/* Allocate quadrics with filled drawing style */
void Robot::InitQuadrics() {
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

void Robot::Robot::head() {
  glPushMatrix();
  glScalef(head_radius, head_height / 2, head_radius);
  gluSphere(h, 1.0, 10, 10);
  glPopMatrix();
}

void Robot::torso() {
  glPushMatrix();
  glRotatef(90.0, 1.0, 0.0, 0.0);
  gluCylinder(t, torso_radius, torso_radius, torso_height, 10, 10);
  glPopMatrix();
}

void Robot::left_upper_arm() {
  glPushMatrix();
  glRotatef(90, 0, 1, 0);
  gluCylinder(lua, upper_arm_radius, upper_arm_radius, upper_arm_height, 10,
              10);
  glPopMatrix();
}

void Robot::left_lower_arm() {
  glPushMatrix();
  glRotatef(90, 0, 1, 0);
  gluCylinder(lla, lower_arm_radius, lower_arm_radius, lower_arm_height, 10,
              10);
  glPopMatrix();
}

void Robot::right_upper_arm() {
  glPushMatrix();
  glRotatef(-90, 0, 1, 0);
  gluCylinder(rua, upper_arm_radius, upper_arm_radius, upper_arm_height, 10,
              10);
  glPopMatrix();
}

void Robot::right_lower_arm() {
  glPushMatrix();
  glRotatef(-90, 0, 1, 0);
  gluCylinder(lla, lower_arm_radius, lower_arm_radius, lower_arm_height, 10,
              10);
  glPopMatrix();
}

void Robot::left_upper_leg() {
  glPushMatrix();
  glRotatef(90, 1, 0, 0);
  gluCylinder(lul, upper_leg_radius, upper_leg_radius, upper_leg_height, 10,
              10);
  glPopMatrix();
}

void Robot::left_lower_leg() {
  glPushMatrix();
  glRotatef(90, 1, 0, 0);
  gluCylinder(lll, lower_leg_radius, lower_leg_radius, lower_leg_height, 10,
              10);
  glPopMatrix();
}

void Robot::right_upper_leg() {
  glPushMatrix();
  glRotatef(90, 1, 0, 0);
  gluCylinder(rul, upper_leg_radius, upper_leg_radius, upper_leg_height, 10,
              10);
  glPopMatrix();
}

void Robot::right_lower_leg() {
  glPushMatrix();
  glRotatef(90, 1, 0, 0);
  gluCylinder(rll, lower_leg_radius, lower_leg_radius, lower_leg_height, 10,
              10);
  glPopMatrix();
}

void Robot::DrawRobot(float x, float y, float z, float lua, float lla,
                      float rua, float rla, float lul, float lll, float rul,
                      float rll) {
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

void Robot::move_lua_up() {
  theta[LUA] += 5;
}

void Robot::move_lua_down() {
  theta[LUA] -= 5;
}

void Robot::move_lla_up() {
  theta[LLA] += 5;
}

void Robot::move_lla_down() {
  theta[LLA] -= 5;
}

void Robot::move_rua_up() {
  theta[RUA] += 5;
}

void Robot::move_rua_down() {
  theta[RUA] -= 5;
}

void Robot::move_rla_up() {
  theta[RLA] += 5;
}

void Robot::move_rla_down() {
  theta[RLA] -= 5;
}

void Robot::move_lul_up() {
  theta[LUL] += 5;
}

void Robot::move_lul_down() {
  theta[LUL] -= 5;
}

void Robot::move_lll_up() {
  theta[LLL] += 5;
}

void Robot::move_lll_down() {
  theta[LLL] -= 5;
}

void Robot::move_rul_up() {
  theta[RUL] += 5;
}

void Robot::move_rul_down() {
  theta[RUL] -= 5;
}

void Robot::move_rll_up() {
  theta[RLL] += 5;
}

void Robot::move_rll_down() {
  theta[RLL] -= 5;
}

double Robot::randRange(double min, double max) {
  return rand() * (max - min) / RAND_MAX + min;
}

/**
 * Generar direcciones aleatorias
 */
void Robot::genDirec() {
  for (int i = 0; i < QUIT; i++) {
    int s = randRange(-2, 2);
    while (s == 0)
      s = randRange(-2, 2);
    this->direccion[i] = s;
  }
}

bool Robot::isDance() const {
  return dance;
}

short int* Robot::getDireccion() {
  return direccion;
}

const GLfloat Robot::getHeadHeight() const {
  return head_height;
}

const GLfloat Robot::getHeadRadius() const {
  return head_radius;
}

const GLfloat Robot::getLowerArmHeight() const {
  return lower_arm_height;
}

const GLfloat Robot::getLowerArmRadius() const {
  return lower_arm_radius;
}

const GLfloat Robot::getLowerLegHeight() const {
  return lower_leg_height;
}

const GLfloat Robot::getLowerLegRadius() const {
  return lower_leg_radius;
}

GLUquadricObj* Robot::getT() const {
  return t;
}

void Robot::setT(GLUquadricObj* t) {
  this->t = t;
}

GLfloat* Robot::getTheta() {
  return theta;
}

const GLfloat Robot::getTorsoHeight() const {
  return torso_height;
}

const GLfloat Robot::getTorsoRadius() const {
  return torso_radius;
}

const GLfloat Robot::getUpperArmHeight() const {
  return upper_arm_height;
}

const GLfloat Robot::getUpperArmRadius() const {
  return upper_arm_radius;
}

const GLfloat Robot::getUpperLegHeight() const {
  return upper_leg_height;
}

const GLfloat Robot::getUpperLegRadius() const {
  return upper_leg_radius;
}

const bool Robot::getDance() const {
  return this->dance;
}

void Robot::toggleDance() {
  this->dance = !this->dance;
}

void Robot::setHeadHeight(GLfloat headHeight) {
  head_height = headHeight;
}

void Robot::setHeadRadius(GLfloat headRadius) {
  head_radius = headRadius;
}

void Robot::setLowerArmHeight(GLfloat lowerArmHeight) {
  lower_arm_height = lowerArmHeight;
}

void Robot::setLowerArmRadius(GLfloat lowerArmRadius) {
  lower_arm_radius = lowerArmRadius;
}

void Robot::setLowerLegHeight(GLfloat lowerLegHeight) {
  lower_leg_height = lowerLegHeight;
}

void Robot::setLowerLegRadius(GLfloat lowerLegRadius) {
  lower_leg_radius = lowerLegRadius;
}

void Robot::setTorsoHeight(GLfloat torsoHeight) {
  torso_height = torsoHeight;
}

void Robot::setTorsoRadius(GLfloat torsoRadius) {
  torso_radius = torsoRadius;
}

void Robot::setUpperArmHeight(GLfloat upperArmHeight) {
  upper_arm_height = upperArmHeight;
}

void Robot::setUpperArmRadius(GLfloat upperArmRadius) {
  upper_arm_radius = upperArmRadius;
}

void Robot::setUpperLegHeight(GLfloat upperLegHeight) {
  upper_leg_height = upperLegHeight;
}

void Robot::setUpperLegRadius(GLfloat upperLegRadius) {
  upper_leg_radius = upperLegRadius;
}

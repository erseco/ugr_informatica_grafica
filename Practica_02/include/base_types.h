/******************************************************************************
 *
 * IG - Informática Gráfica
 * Grado en Ingeniería Informática
 *
 * 2014 - Ernesto Serrano <erseco@correo.ugr.es>
 * ---------------------------------------------
 *
 *  Cabeceras del codigo del usuario, funciona tanto en linux como en mac
 *
 ******************************************************************************/
#ifndef _BASE_TYPES_
#define _BASE_TYPES_

#ifdef __MACH__ // Incluimos las librerías necesarias para que funcione en OSX
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif
#include <stdlib.h> // pulls in declaration of malloc, free
#include <vector>

#include <vertex.h>

using namespace std;

struct Point3D
{
private:
	float x, y, z;

struct Triangle
{
private:
	int cara0, cara1, cara2;

};

#endif
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
#ifndef _COLOR_
#define _COLOR_

#ifdef __MACH__ // Incluimos las librerías necesarias para que funcione en OSX
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif
#include <stdlib.h> // pulls in declaration of malloc, free
#include <vector>

#include <vertex.h>
#include "file_ply_stl.hpp"

using namespace std;

struct Color
{
private:
	float r, g, b, alpha;
	vector<_vertex3f> vertices;
	vector<_vertex3i> caras;
public:
	void colorear(void) const
	{
		glColor4f(r,g,b,alpha);
	}
};

#endif
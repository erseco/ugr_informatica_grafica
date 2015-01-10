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
#ifndef _MODEL_
#define _MODEL_

#ifdef __MACH__ // Incluimos las librerías necesarias para que funcione en OSX
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif
#include <stdlib.h> // pulls in declaration of malloc, free
#include <vector>

#include <vertex.h>

#include <color.h>

using namespace std;

class Model
{

protected:

	vector<_vertex3f> vertices;
	vector<_vertex3i> caras;

	Color colorActual;

public:

	Model();

	enum DrawMode {
		POINTS, LINES, SOLID, CHESS
	};

	void draw(DrawMode mode = SOLID) const;

};

#endif

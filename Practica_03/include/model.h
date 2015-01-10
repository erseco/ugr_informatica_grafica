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
#include <math.h> // Librerias matemáticas

#include <vertex.h>

using namespace std;

class Model
{

protected:

	vector<_vertex3f> _vertices;
	vector<_vertex3i> _caras;

	void setVertices(vector<_vertex3f> vertex);
    void setFaces(vector<_vertex3i> faces);

public:

	Model()
	{
		x = 0;
		y = 0;
		z = 0;
	}

	// Posicion central del objeto
	float x, y, z;
	void setCenter(float pX, float pY, float pZ)
	{
		x = pX;
		y = pY;
		z = pZ;
	};

	// Obtiene los vertices, se usa porque en determinados casos nos
	// pasamos los vertices de un modelo a otro (cargamos un ply y lo pasamos a uno de revolucion)
	vector<_vertex3f> getVertices(){ return _vertices; };

	enum DrawMode {
		POINTS, LINES, SOLID, CHESS
	};

	// Esta funcion pinta el modelo, como es virtual, es sobrecargable
	virtual void draw(DrawMode mode = SOLID);

	// Esta funcion procesa una letra en el modelo, sirve para extender el procesado
	// de teclas, de ahí que sea virtual
	virtual void process_key(unsigned char Tecla) {};

};

#endif

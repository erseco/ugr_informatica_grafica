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

#include <color.h>

using namespace std;

class Model
{

private:

	float degreesToRadians(float degreeValue);
	_vertex3f rotateX(_vertex3f p, float alpha);
	_vertex3f rotateY(_vertex3f p, float alpha);
	_vertex3f rotateZ(_vertex3f p, float alpha);


    void free();
    void reserve(int n_vertex, int n_faces);

protected:

	vector<_vertex3f> _vertices;
	vector<_vertex3i> _caras;

	vector<_vertex3f> _normales_caras;
	vector<_vertex3f> _normales_vertices;

	Color colorActual;

    void setVertices(vector<_vertex3f> vertex);
    void setFaces(vector<_vertex3i> faces);
    void setNormalesCaras(vector<_vertex3f> normals);
    void setNormalesVertices(vector<_vertex3f> normals);

public:

	vector<_vertex3f> getVertices(){ return _vertices; };

	Model();

	enum DrawMode {
		POINTS, LINES, SOLID, CHESS
	};

	void draw(DrawMode mode = SOLID) const;

	void drawNormales() const;

	void generarPorPerfil(vector<_vertex3f> pefil, int steps);

	void generarNormales();

};

#endif

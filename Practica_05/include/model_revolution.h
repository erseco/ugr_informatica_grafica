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
#ifndef _MODEL_REVOLUTION_
#define _MODEL_REVOLUTION_

#include <model.h>

class Model_Revolution : public Model
{
private:

	vector<_vertex3f> _normales_caras;


    void setNormalesCaras(vector<_vertex3f> normals);
    void setNormalesVertices(vector<_vertex3f> normals);

	float degreesToRadians(float degreeValue);
	_vertex3f rotateX(_vertex3f p, float alpha);
	_vertex3f rotateY(_vertex3f p, float alpha);
	_vertex3f rotateZ(_vertex3f p, float alpha);

	bool varDrawNormales;
	void drawNormales() const;


	void generarPorPerfil(vector<_vertex3f> perfil, int steps);

	void generarNormales();
	void generarNormalesCaras();
	void generarNormalesVertices();

	void calcular_coord_textura(int N, int M);
	double distancia(_vertex3f a, _vertex3f b);

public:

	Model_Revolution(vector<_vertex3f> pefil, int steps);

	void draw(DrawMode mode = SOLID);

	void process_key(unsigned char Tecla);

};

#endif


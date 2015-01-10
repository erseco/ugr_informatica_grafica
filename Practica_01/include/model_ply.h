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
#ifndef _MODEL_PLY_
#define _MODEL_PLY_

#include <model.h>
#include <file_ply_stl.hpp>

class Model_Ply : public Model
{

protected:

public:
	Model_Ply();
	Model_Ply(float size, char * file);
};

#endif


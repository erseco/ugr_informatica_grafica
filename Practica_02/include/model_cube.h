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
#ifndef _MODEL_CUBE_
#define _MODEL_CUBE_

#include <model.h>

class Model_Cube : public Model
{

protected:

public:
	Model_Cube();
	Model_Cube(float size);
};

#endif

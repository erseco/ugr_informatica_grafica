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

#include <model_cube.h>

Model_Cube::Model_Cube()
{

}

// cubo //////////////////////////////////////////////////////////////
//    v6----- v5
//   /|      /|
//  v1------v0|
//  | |     | |
//  | |v7---|-|v4
//  |/      |/
//  v2------v3
Model_Cube::Model_Cube(float size)
{

	// Vertices
	vertices.push_back(_vertex3f(-size,	-size, 	size));
	vertices.push_back(_vertex3f(size,	-size, 	size));
	vertices.push_back(_vertex3f(size, 	size, 	size));
	vertices.push_back(_vertex3f(-size, 	size, 	size));

    vertices.push_back(_vertex3f(-size,	-size,	 -size));
    vertices.push_back(_vertex3f(size,	-size,	 -size));
    vertices.push_back(_vertex3f(size,	 size,	 -size));
    vertices.push_back(_vertex3f(-size,	 size,	 -size));

    // Caras
    caras.push_back(_vertex3i(0, 1, 4));
    caras.push_back(_vertex3i(1, 5, 4));
    caras.push_back(_vertex3i(1, 2, 5));
    caras.push_back(_vertex3i(2, 6, 5));
    caras.push_back(_vertex3i(2, 3, 6));
    caras.push_back(_vertex3i(3, 7, 6));
    caras.push_back(_vertex3i(3, 0, 7));
    caras.push_back(_vertex3i(0, 4, 7));
    caras.push_back(_vertex3i(4, 5, 7));
    caras.push_back(_vertex3i(5, 6, 7));
    caras.push_back(_vertex3i(3, 2, 0));
    caras.push_back(_vertex3i(2, 1, 0));


}
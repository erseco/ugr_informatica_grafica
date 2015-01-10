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

#include <model_pyramid.h>

 Model_Pyramid::Model_Pyramid()
 {

 }

// piramide /////////////////////////////////////////////
//     /\.
//    / |\/.
//   /  | \/ .
//  /   |  \/./
// /____|___\/
Model_Pyramid::Model_Pyramid(float size)
{
    vector<_vertex3f> vertices;
    vector<_vertex3i> caras;

	// Vertices
	vertices.push_back(_vertex3f(-size,	-size, 	size));
	vertices.push_back(_vertex3f(size,	-size, 	size));
	vertices.push_back(_vertex3f(size, 	size, 	size));
	vertices.push_back(_vertex3f(-size, 	size, 	size));
	vertices.push_back(_vertex3f(0,	0,	 size*3)); // punta de la piramide

	// Caras
	caras.push_back(_vertex3i(1, 0, 3));
	caras.push_back(_vertex3i(1, 3, 2));
	caras.push_back(_vertex3i(0, 1, 4));
	caras.push_back(_vertex3i(0, 4, 3));
	caras.push_back(_vertex3i(3, 4, 2));
	caras.push_back(_vertex3i(1, 2, 4));

	setVertices(vertices);
    setFaces(caras);

}
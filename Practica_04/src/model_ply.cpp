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

#include <model_ply.h>

Model_Ply::Model_Ply(char * file)
{

    setColor(0,0,1,1);

	vector<float> vec_vertices;
    vector<int> vec_caras;

    vector<_vertex3f> vertices;
    vector<_vertex3i> caras;

    // Obtenemos los vértices del fichero .ply
    ply::read(file, vec_vertices, vec_caras);

    for (int j = 0; j < vec_vertices.size(); j+=3)
    {
        _vertex3f vert;
        vert.x = vec_vertices[j] ;
        vert.y = vec_vertices[j+1] ;
        vert.z = vec_vertices[j+2] ;

        vertices.push_back(vert);

    }

    for (int j = 0; j < vec_caras.size(); j+=3)
    {

        _vertex3i triangulo;
        triangulo._0 = vec_caras[j] ;
        triangulo._1 = vec_caras[j+1] ;
        triangulo._2 = vec_caras[j+2] ;

        caras.push_back(triangulo);

    }

    setVertices(vertices);
    setFaces(caras);

}
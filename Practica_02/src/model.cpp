/******************************************************************************
 *
 * IG - Informática Gráfica
 * Grado en Ingeniería Informática
 *
 * 2014 - Ernesto Serrano <erseco@correo.ugr.es>
 * ---------------------------------------------
 *
 *  Codigo del Modelo
 *
 ******************************************************************************/

#include <model.h>

Model::Model()
{

}

void Model::free()
{
    _vertices.clear();
    _caras.clear();
    _normales_caras.clear();
    _normales_vertices.clear();
}

void Model::reserve(int n_vertex, int n_faces)
{

}

void Model::setVertices(vector<_vertex3f> vertex)
{
    _vertices = vertex;
}

void Model::setFaces(vector<_vertex3i> faces)
{
    _caras = faces;
}

void Model::setNormalesCaras(vector<_vertex3f> normals)
{
    _normales_caras = normals;
}

void Model::setNormalesVertices(vector<_vertex3f> normals)
{
    _normales_vertices = normals;
}

void Model::draw(Model::DrawMode mode) const
{
    GLenum draw_mode;
    switch (mode)
    {
        case Model::POINTS:
            draw_mode = GL_POINTS;
            break;
        case Model::LINES:
            draw_mode = GL_LINES;
            break;
        default: // SOLID & CHESS
            draw_mode = GL_TRIANGLES;

            // Para probar que se pintan los triangulos correctamente
            // glPolygonMode(GL_FRONT,GL_FILL); // Los frontales los pintamos
            // glPolygonMode(GL_BACK,GL_LINE); // Los traseros solo las lineas

            break;
    }

    glPointSize(2);


    // NOTA: Esto es lo que nos ha preguntado en el examen para mostrar un vector
    // directamente como puntos, comentamos la parte de abajo y los mostramos así
    // notese que se trabaja con punteros
    // glColor3f(0, 1, 0);
    // glEnableClientState(GL_VERTEX_ARRAY);
    // glVertexPointer(3, GL_FLOAT, sizeof(vector<Model>), &vertices[0]);
    // glDrawArrays(GL_POINTS, 0, vertices.size());
    // glDisableClientState(GL_VERTEX_ARRAY);

    glBegin(draw_mode);

        for (int i= 0; i < _caras.size(); i++)
        {
            // Cambio de color para el ajedrez
            if (mode == Model::CHESS && i %2 == 0)
             glColor3f(1, 0, 0);
            else
             glColor3f(0, 1, 0);

            int Vertex_1,Vertex_2,Vertex_3;

            Vertex_1 = _caras[i]._0;
            Vertex_2 = _caras[i]._1;
            Vertex_3 = _caras[i]._2;

            glVertex3f(_vertices[Vertex_1].x, _vertices[Vertex_1].y, _vertices[Vertex_1].z);
            glVertex3f(_vertices[Vertex_2].x, _vertices[Vertex_2].y, _vertices[Vertex_2].z);
            glVertex3f(_vertices[Vertex_3].x, _vertices[Vertex_3].y, _vertices[Vertex_3].z);
        }

    glEnd();

}


void Model::drawNormales() const
{

    float t = 0.2;

    glPointSize(2);
    glColor3f(0, 0, 1);


    glBegin(GL_LINES);

        for (int i= 0; i < _vertices.size(); i++)
        {
            _vertex3f _1 = _vertices[i];
            _vertex3f _2;

            _2.x = _1.x + t * _normales_vertices[i].x;
            _2.y = _1.y + t * _normales_vertices[i].y;
            _2.z = _1.z + t * _normales_vertices[i].z;

            glVertex3f(_1.x, _1.y, _1.z);
            glVertex3f(_2.x, _2.y, _2.z);
        }

    glEnd();

}


GLenum getGLDrawMode(Model::DrawMode mode)
{
    GLenum draw_mode;

    switch (mode)
    {
        case Model::POINTS:
            draw_mode = GL_POINTS;
            break;
        case Model::LINES:
            draw_mode = GL_LINES;
            break;
        default: // SOLID & CHESS
            draw_mode = GL_TRIANGLES;
            break;
    }

    return draw_mode;
}

void Model::generarPorPerfil(vector<_vertex3f> perfil, int steps)
{
    double angle;
    vector<_vertex3i> caras;
    vector<_vertex3f> vertices(perfil);

    angle = (2.0*M_PI) / steps;

    // Generamos la parte principal

    for (int step = 0; step < steps; step++)
    {
        vector<_vertex3f> siguientePerfil(perfil.size());
        // Generamos los puntos rodaso
        for (unsigned int k = 0; k < perfil.size(); k++)
            siguientePerfil[k] = rotateY(perfil[k], angle);

        // Añadimos los vertices al final del vector
        vertices.insert(vertices.end(), siguientePerfil.begin(), siguientePerfil.end() );

        // Generamos las caras
        unsigned int inicioPerfil, finPerfil;
        inicioPerfil = step * perfil.size();
        finPerfil = inicioPerfil + perfil.size();

        for (unsigned int i = inicioPerfil+1, k = finPerfil+1; i < finPerfil; i++, k++)
        {
            caras.push_back(_vertex3i(i-1, k-1, k));
            caras.push_back(_vertex3i(i-1, k,   i));
        }

        perfil = siguientePerfil;

    }

    // Generamos las tapas

    // Generamos la tapa de abajo
    if (vertices.front().x)
    {
        // Agregamos el punto central, aunque no es necesario porque solo pintamos las caras
        _vertex3f puntoCentral(0.0, vertices.front().y, 0.0);
        vertices.push_back(puntoCentral);

        for (int step = 0; step < steps; step++)
        {
            int perfilactual = step * perfil.size();
            int siguientePerfil = perfilactual + perfil.size();
            caras.push_back(_vertex3i(vertices.size()-1, siguientePerfil, perfilactual));

        }

    }

    // Generamos la tapa de arriba
    if (vertices[perfil.size() - 1].x)
    {

        // Agregamos el punto central, aunque no es necesario porque solo pintamos las caras
        _vertex3f puntoCentral(0.0, vertices[perfil.size() - 1].y, 0.0);
        vertices.push_back(puntoCentral);

        for (int step = 0; step < steps; step++)
        {
            int perfilactual = (step+1) * perfil.size() -1;
            int siguientePerfil = perfilactual + perfil.size();
            caras.push_back(_vertex3i(vertices.size()-1, perfilactual,siguientePerfil)); // Hay que ponerlos al revés que en la otra tapa para que calcule bien las normales

        }

    }

    // free();
    // reserve(vertices.size(), caras.size());
    setVertices(vertices);
    setFaces(caras);

}

void Model::generarNormales()
{
    vector<_vertex3f> normales_caras;

    for(int i = 0; i < _caras.size(); i++)
    {

        _vertex3f A, B, C;
        A = _vertices[_caras[i]._0];
        B = _vertices[_caras[i]._1];
        C = _vertices[_caras[i]._2];

        _vertex3f ab, bc, normal;

        ab.x = B.x - A.x;
        ab.y = B.y - A.y;
        ab.z = B.z - A.z;

        bc.x = C.x - B.x;
        bc.y = C.y - B.y;
        bc.z = C.z - B.z;

        // Calculamos el producto vectorial (https://es.wikipedia.org/wiki/Producto_vectorial)
        normal.x = ab.y * bc.z - ab.z * bc.y;
        normal.y = ab.z * bc.x - ab.x * bc.z;
        normal.z = ab.x * bc.y - ab.y * bc.x;

        // Antonio para normalizar
        float modulo=sqrt(normal.x*normal.x+normal.y*normal.y+normal.z*normal.z);
        normal.x=normal.x/modulo;
        normal.y=normal.y/modulo;
        normal.z=normal.z/modulo;
        // Fin Antonio

        normales_caras.push_back(normal);

    }

    setNormalesCaras(normales_caras);



    vector<_vertex3f> normales_vertices;


    // Recorremos los vertices
    for(int i = 0; i < _vertices.size(); i++)
    {

        _vertex3f verticeactual = _vertices[i];
        _vertex3f normal(0,0,0);

        // Recorremos las caras
        for(int h = 0; h < _caras.size(); h++)
        {
            // Comprobamos si el vertice esta en otra cara (por la posicion)
            if (_caras[h]._0 == i || _caras[h]._1 == i || _caras[h]._2 == i)
            {
                normal = _vertex3f(normal.x + normales_caras[h].x, normal.y + normales_caras[h].y, normal.z + normales_caras[h].z);
            }

        }

        // Antonio para normalizar
        float modulo=sqrt(normal.x*normal.x+normal.y*normal.y+normal.z*normal.z);
        normal.x=normal.x/modulo;
        normal.y=normal.y/modulo;
        normal.z=normal.z/modulo;
        // Fin Antonio

        // La agregago al vector
        normales_vertices.push_back(normal);
    }

    setNormalesVertices(normales_vertices);

}

float Model::degreesToRadians(float degreeValue)
{
    return degreeValue * M_PI / 180.0;
}

_vertex3f Model::rotateX(_vertex3f p, float alpha)
{
    _vertex3f point;

    point.x = p.x;
    point.y = cos(alpha) * p.y - sin(alpha) * p.z;
    point.z = sin(alpha) * p.y + cos(alpha) * p.z;

    return point;
}

_vertex3f Model::rotateY(_vertex3f p, float alpha)
{
    _vertex3f point;

    point.x = cos(alpha) * p.x + sin(alpha) * p.z;
    point.y = p.y;
    point.z = -sin(alpha) * p.x + cos(alpha) * p.z;

    return point;
}

_vertex3f Model::rotateZ(_vertex3f p, float alpha)
{
    _vertex3f point;

    point.x = cos(alpha) * p.x - sin(alpha) * p.y;
    point.y = sin(alpha) * p.x + cos(alpha) * p.y;
    point.z = p.z;

    return point;
}
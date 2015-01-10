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

void Model::setVertices(vector<_vertex3f> vertex)
{
    _vertices = vertex;
}

void Model::setFaces(vector<_vertex3i> faces)
{
    _caras = faces;
}

void Model::draw(Model::DrawMode mode)
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
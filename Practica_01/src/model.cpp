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
            break;
    }

    int Vertex_1,Vertex_2,Vertex_3;

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

        for (int i= 0; i < caras.size(); i++)
        {
         // Cambio de color para el ajedrez
         if (mode == CHESS && i %2 == 0)
             glColor3f(1, 0, 0);
         else
             glColor3f(0, 1, 0);

         Vertex_1 = caras[i]._0;
         Vertex_2 = caras[i]._1;
         Vertex_3 = caras[i]._2;

         glVertex3f(vertices[Vertex_1].x, vertices[Vertex_1].y, vertices[Vertex_1].z);
         glVertex3f(vertices[Vertex_2].x, vertices[Vertex_2].y, vertices[Vertex_2].z);
         glVertex3f(vertices[Vertex_3].x, vertices[Vertex_3].y, vertices[Vertex_3].z);

        }

    glEnd();

}

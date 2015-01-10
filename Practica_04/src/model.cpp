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


void Model::loadImage(const string & nombreArchivoJPG)
{
    imagen = new jpg::Imagen(nombreArchivoJPG);


    // // usar con:
    // int tamx = imagen->tamX(); // num. columnas (unsigned)
    // int tamy = imagen->tamY(); // num. filas (unsigned)
    // unsigned char * texels = imagen->leerPixels(); // puntero texels (unsigned char *)


}

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


    if (imagen != NULL)
    {
        // Carga la imagen
        glTexImage2D(GL_TEXTURE_2D, 0, 3, imagen->tamX(), imagen->tamY(), 0, GL_RGB, GL_UNSIGNED_BYTE, imagen->leerPixels());

        glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
        glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
        glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
        glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

        glEnable(GL_TEXTURE_2D);
        glDisable(GL_COLOR_MATERIAL);
    }
    else
    {
        glEnable(GL_COLOR_MATERIAL);
        glDisable(GL_TEXTURE_2D);
    }


    glBegin(draw_mode);

        // if (zoom > 0)
        //     glScalef(2.0f, 2.0f, 2.0f);


        for (int i= 0; i < _caras.size(); i++)
        {

            // Cambio de color para el ajedrez
            if (mode == Model::CHESS && i %2 == 0 && _texturas.size() == 0)
                glColor3f(1, 0, 0); // Rojo
            else
                // Color normal (blanco cuando textura)
                glColor3f(_color.x, _color.y, _color.z);

            int Vertex_1,Vertex_2,Vertex_3;

            Vertex_1 = _caras[i]._0;
            Vertex_2 = _caras[i]._1;
            Vertex_3 = _caras[i]._2;

            if (_texturas.size() > 0)
                glTexCoord2f(_texturas[Vertex_1].x, _texturas[Vertex_1].y);

            if (_normales_vertices.size() > 0)
                glNormal3f(_normales_vertices[Vertex_1].x, _normales_vertices[Vertex_1].y, _normales_vertices[Vertex_1].z);


            glVertex3f(_vertices[Vertex_1].x, _vertices[Vertex_1].y, _vertices[Vertex_1].z);

            if (_texturas.size() > 0)
                 glTexCoord2f(_texturas[Vertex_2].x, _texturas[Vertex_2].y);

            if (_normales_vertices.size() > 0)
                glNormal3f(_normales_vertices[Vertex_2].x, _normales_vertices[Vertex_2].y, _normales_vertices[Vertex_2].z);

            glVertex3f(_vertices[Vertex_2].x, _vertices[Vertex_2].y, _vertices[Vertex_2].z);

            if (_texturas.size() > 0)
                glTexCoord2f(_texturas[Vertex_3].x, _texturas[Vertex_3].y);

            if (_normales_vertices.size() > 0)
                glNormal3f(_normales_vertices[Vertex_3].x, _normales_vertices[Vertex_3].y, _normales_vertices[Vertex_3].z);

            glVertex3f(_vertices[Vertex_3].x, _vertices[Vertex_3].y, _vertices[Vertex_3].z);
        }

    glEnd();

    glDisable(GL_TEXTURE_2D);

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
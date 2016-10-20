/******************************************************************************
 *
 * IG - Informática Gráfica
 * Grado en Ingeniería Informática
 *
 * 2014 - Ernesto Serrano <erseco@correo.ugr.es>
 * ---------------------------------------------
 *
 *  Codigo del Model_Revolutiono
 *
 ******************************************************************************/

#include <model_revolution.h>

Model_Revolution::Model_Revolution(vector<_vertex3f> perfil, int steps)
{

    setColor(0,1,0,1);

    // Bandera de si queremos pintar o no las normales
    varDrawNormales = false;
    generarPorPerfil(perfil, steps);
    generarNormales();
}

void Model_Revolution::process_key(unsigned char Tecla)
{
    // Al pulsar la tecla activamos / desactivamos el pintado de las normales
    if (Tecla == 'n')
        varDrawNormales = !varDrawNormales;
}

void Model_Revolution::setNormalesCaras(vector<_vertex3f> normals)
{
    _normales_caras = normals;
}

void Model_Revolution::setNormalesVertices(vector<_vertex3f> normals)
{
    _normales_vertices = normals;
}

void Model_Revolution::draw(DrawMode mode)
{
    // Lo primero, movemos el modelo al centro establecido mediante setCenter()
    glPushMatrix();
    glTranslatef(x, y, z);

    // Llamamos al método la clase base
    Model::draw(mode);

    // En caso de que hayamos activado la tecla de mostrar las normales
    // las pintamos
    if (varDrawNormales)
        drawNormales();

    glPopMatrix();

}


void Model_Revolution::drawNormales() const
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

void Model_Revolution::generarPorPerfil(vector<_vertex3f> perfil, int steps)
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

    setVertices(vertices);
    setFaces(caras);

    // Calcular coordenadas de textura
    calcular_coord_textura(steps, perfil.size());

}

//***************************************************************************************
// Funcion para generar y almacenar los coord. de textura (malla generada por revolucion)
//***************************************************************************************

// Donde N es el numero de rotaciones
void Model_Revolution::calcular_coord_textura(int N, int M)
{

    int n_vertices = _vertices.size();

    double d[M];    //vector de distancias
    d[0] = 0;

    for(unsigned int k=1; k<M; k++)
        d[k] = d[k-1] + distancia(_vertices[k-1], _vertices[k]);

    for(unsigned int i=0; i<=N; i++)
    {
        float si = (float)i/(N-1);
        for(unsigned int j=0; j<M; j++)
        {
            float tj = d[j]/d[M-1];

            _texturas.push_back(_vertex2f(si, tj));

        }
    }
}

double Model_Revolution::distancia(_vertex3f a, _vertex3f b)
{
    double x = pow((b.x-a.x), 2);
    double y = pow((b.y-a.y), 2);
    double z = pow((b.z-a.z), 2);

    return sqrt((double)(x+y+z));
}

void Model_Revolution::generarNormales()
{
    generarNormalesCaras();
    generarNormalesVertices();

}


void Model_Revolution::generarNormalesCaras()
{

    // Calculamos las normales de las caras
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

}

void Model_Revolution::generarNormalesVertices()
{

    // Generamos las normales de los vertices

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
                normal = _vertex3f(normal.x + _normales_caras[h].x,
                                    normal.y + _normales_caras[h].y,
                                    normal.z + _normales_caras[h].z);
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

float Model_Revolution::degreesToRadians(float degreeValue)
{
    return degreeValue * M_PI / 180.0;
}

_vertex3f Model_Revolution::rotateX(_vertex3f p, float alpha)
{
    _vertex3f point;

    point.x = p.x;
    point.y = cos(alpha) * p.y - sin(alpha) * p.z;
    point.z = sin(alpha) * p.y + cos(alpha) * p.z;

    return point;
}

_vertex3f Model_Revolution::rotateY(_vertex3f p, float alpha)
{
    _vertex3f point;

    point.x = cos(alpha) * p.x + sin(alpha) * p.z;
    point.y = p.y;
    point.z = -sin(alpha) * p.x + cos(alpha) * p.z;

    return point;
}

_vertex3f Model_Revolution::rotateZ(_vertex3f p, float alpha)
{
    _vertex3f point;

    point.x = cos(alpha) * p.x - sin(alpha) * p.y;
    point.y = sin(alpha) * p.x + cos(alpha) * p.y;
    point.z = p.z;

    return point;
}
